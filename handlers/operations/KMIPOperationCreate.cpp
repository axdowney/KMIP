/* Copyright (C) 2017 Alexander Downey */
#include </usr/include/openssl/aes.h>
#include <openssl/des.h>
#include <cstdlib>
#include <crypto++/aes.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/des.h>
#include "KMIPOperationCreate.h"
#include "KMIPAttribute.h"
#include "KMIPKey.h"
#include "KMIPEnumeration.h"
#include "KMIPKeyBlock.h"
#include "HexUtils.h"

KMIPOperationCreate::KMIPOperationCreate() : KMIPOperationHandler(KMIPOperation::Create) {}

bool KMIPOperationCreate::handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const {
    bool bOK = spkd && spkbi;
    KMIPStructSP spkst;
    std::list<std::shared_ptr<KMIPAttribute> > listAttributes;
    if (bOK) {
        spkst = spkbi->getRequestPayload();
        if (!spkst) {
            bOK = false;
            kms.addFailure(spkbi, KMIPResultReason::InvalidMessage, "Request Payload not found.");
        }
    }

    if (spkst) {
        bOK = spkd->gatherAttributes(spkst->getChild<KMIPTemplateAttribute>(kmip::TagTemplateAttribute), listAttributes);
        if (!bOK) {
            kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Incorrect attribute value(s) specified.");
        }
    }

    /* Get Required Attributes */
    if (bOK) {
        std::map<std::string, std::list<std::shared_ptr<KMIPAttribute> > > mapAttributes;
        for (auto spka : listAttributes) {
            if (spka) {
                mapAttributes[spka->getName()].push_back(spka);
            }
        }

        int32_t iAlg = KMIPCryptographicAlgorithm::Unknown;
        int iLength = -1;
        int iByteLength = -1;
        auto mapIter = mapAttributes.find(KMIPUtils::getTagName(kmip::TagCryptographicAlgorithm));
        if (mapIter != mapAttributes.end() && mapIter->second.size() == 1 && mapIter->second.front().get()) {
            std::shared_ptr<KMIPAttribute> spka = mapIter->second.front();
            iAlg = spka->getValue<KMIPEnumeration>(0);
            if (!KMIPCryptographicAlgorithm::isSymmetric(iAlg)) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Invalid Cryptographic Algorithm");
            }
        } else {
            bOK = false;
            kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Cryptographic Algorithm");
        }

        if (bOK) {
            auto mapIter = mapAttributes.find(KMIPUtils::getTagName(kmip::TagCryptographicLength));
            if (mapIter != mapAttributes.end() && mapIter->second.size() == 1 && mapIter->second.front().get()) {
                std::shared_ptr<KMIPAttribute> spka = mapIter->second.front();
                iLength = spka->getValue<KMIPInteger>(0);
                iByteLength = static_cast<double>(iLength) / 8 + 0.5;
                bOK = iByteLength > 0;
                if (!bOK) {
                    kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Invalid Cryptographic Length");
                }
            } else {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Cryptographic Length");
            }
        }

        if (bOK) {
            if (iAlg == KMIPCryptographicAlgorithm::DES) {
                bOK = (iByteLength == CryptoPP::DES::MIN_KEYLENGTH || iByteLength == CryptoPP::DES::MAX_KEYLENGTH - 1);
            } else if (iAlg == KMIPCryptographicAlgorithm::DES3) {
                if (iByteLength == CryptoPP::DES_EDE3::MIN_KEYLENGTH || iByteLength == CryptoPP::DES_EDE3::MAX_KEYLENGTH - 3) {
                    iByteLength = CryptoPP::DES_EDE3::MIN_KEYLENGTH;
                } else if (iByteLength == CryptoPP::DES_EDE2::MIN_KEYLENGTH || iByteLength == CryptoPP::DES_EDE2::MAX_KEYLENGTH - 2) {
                    iByteLength = CryptoPP::DES_EDE2::MIN_KEYLENGTH;
                } else {
                    bOK = false;
                }
            } else {
                bOK = iByteLength >= getCryptoPPAlg(iAlg, MIN_KEYLENGTH) && iByteLength <= getCryptoPPAlg(iAlg, MAX_KEYLENGTH)
                    && (KMIPCryptographicAlgorithm::isFixedLength(iAlg) || (iByteLength % getCryptoPPAlgVariableLength(iAlg, KEYLENGTH_MULTIPLE)) == 0);
            }

            if (!bOK) {
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Invalid Cryptographic Length");
            }
        }

        if (bOK) {
            CryptoPP::AutoSeededRandomPool rnd;
            CryptoPP::SecByteBlock key(0x00, iByteLength);
            rnd.GenerateBlock(key, key.size());
            CryptoPP::DES_EDE3::DEFAULT_KEYLENGTH;

            std::string sKey((char *) (unsigned char *) key, key.size());
            sKey = HexUtils::hexEncode(sKey);

            std::shared_ptr<KMIPSymmetricKey> spkey(new KMIPSymmetricKey);
            std::shared_ptr<KMIPKeyBlock> spkb(new KMIPKeyBlock);
            std::shared_ptr<KMIPKeyValue> spkv(new KMIPKeyValue);
            spkv->setKeyMaterialString(sKey);
            spkb->setKeyFormatType(KMIPKeyFormatType::Raw);
            spkb->setKeyValue(spkv);
            spkb->setCryptographicAlgorithm(iAlg);
            spkb->setCryptographicLength(iLength);
            spkey->setKeyBlock(spkb);
            for (auto attr : listAttributes) {
                bOK = spkey->isAttributeAddable(attr.get(), KMIPOperation::Create, true)
                    && spkey->addAttribute(attr.get());
                if (!bOK) {
                    kms.addFailure(spkbi, KMIPResultReason::InvalidField,
                            std::string("Could not add attribute ") + attr->getName() + " " + std::to_string(attr->getIndex()));
                }
            }

            std::string sID;
            if (bOK) {
                sID = spkd->getNextID(KMIPObjectType::SymmetricKey);
                spkey->setUniqueID(sID);
                if (spkd->addObject(spkey) <= 0) {
                    bOK = false;
                    kms.addFailure(spkbi, KMIPResultReason::GeneralFailure, "Could not add object");
                }
            }

            if (bOK) {
                KMIPStructSP spkst(new KMIPStruct(kmip::TagResponsePayload));
                spkst->setOrderedEnumeration(kmip::TagObjectType, KMIPObjectType::SymmetricKey);
                spkst->setOrderedTextString(kmip::TagUniqueIdentifier, sID);
                kms.addSuccess(spkbi, spkst);
            }
        }
    }

    return bOK;
}
