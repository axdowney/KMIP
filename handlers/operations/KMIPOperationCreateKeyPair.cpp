/* Copyright (C) 2017 Alexander Downey */
#include </usr/include/openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/dsa.h>
#include <openssl/dh.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/ecdh.h>
#include <cstdlib>
#include <crypto++/aes.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/des.h>
#include "KMIPOperationCreateKeyPair.h"
#include "KMIPAttribute.h"
#include "KMIPAttributeRule.h"
#include "KMIPKey.h"
#include "KMIPEnumeration.h"
#include "KMIPKeyBlock.h"
#include "HexUtils.h"
#include "KMIPTemplateAttribute.h"
#include "KMIPAttributeStructs.h"

KMIPOperationCreateKeyPair::KMIPOperationCreateKeyPair() : KMIPOperationHandler(KMIPOperation::CreateKeyPair) {}

bool KMIPOperationCreateKeyPair::handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const {
    bool bOK = spkd && spkbi;
    KMIPStructSP spkst;
    std::list<std::shared_ptr<KMIPAttribute> > listAttributesCommon;
    std::list<std::shared_ptr<KMIPAttribute> > listAttributesPrivate;
    std::list<std::shared_ptr<KMIPAttribute> > listAttributesPublic;
    if (bOK) {
        spkst = spkbi->getRequestPayload();
        if (!spkst) {
            bOK = false;
            kms.addFailure(spkbi, KMIPResultReason::InvalidMessage, "Request Payload not found.");
        }
    }

    if (spkst) {
        spkd->gatherAttributes(spkst->getChild<KMIPCommonTemplateAttribute>(kmip::TagCommonTemplateAttribute), listAttributesCommon);
        spkd->gatherAttributes(spkst->getChild<KMIPPublicKeyTemplateAttribute>(kmip::TagPublicKeyTemplateAttribute), listAttributesPublic);
        spkd->gatherAttributes(spkst->getChild<KMIPPrivateKeyTemplateAttribute>(kmip::TagPrivateKeyTemplateAttribute), listAttributesPrivate);
    }

    /* Get Required Attributes */
    if (bOK) {
        std::map<std::string, std::list<std::shared_ptr<KMIPAttribute> > > mapAttributesPublic;
        std::map<std::string, std::list<std::shared_ptr<KMIPAttribute> > > mapAttributesPrivate;
        for (auto spka : listAttributesCommon) {
            if (spka) {
                mapAttributesPublic[spka->getName()].push_back(spka);
                mapAttributesPrivate[spka->getName()].push_back(spka);
            }
        }

        for (auto spka : listAttributesPublic) {
            if (spka) {
                auto attrRule = spka->getRuleFromName();
                if (attrRule->isMultiInstance() || mapAttributesPublic[spka->getName()].empty()) {
                    mapAttributesPublic[spka->getName()].push_back(spka);
                } else {
                    mapAttributesPublic[spka->getName()].front() = spka;
                }
            }
        }

        for (auto spka : listAttributesPrivate) {
            if (spka) {
                auto attrRule = spka->getRuleFromName();
                if (attrRule->isMultiInstance() || mapAttributesPrivate[spka->getName()].empty()) {
                    mapAttributesPrivate[spka->getName()].push_back(spka);
                } else {
                    mapAttributesPrivate[spka->getName()].front() = spka;
                }
            }
        }

        int32_t iAlg = KMIPCryptographicAlgorithm::Unknown;
        int iLength = -1;
        int iByteLength = -1;
        int iQLength = -1;
        uint32_t iCurve = 0;
        KMIPFieldSP spkf;
        KMIPStructSP spkst;
        auto mapIter = mapAttributesPublic.find(KMIPUtils::getTagName(kmip::TagCryptographicAlgorithm));
        if (mapIter != mapAttributesPublic.end() && mapIter->second.size() == 1 && mapIter->second.front().get()) {
            std::shared_ptr<KMIPAttribute> spka = mapIter->second.front();
            iAlg = spka->getValue<KMIPEnumeration>(0);
            if (!KMIPCryptographicAlgorithm::isAsymmetric(iAlg)) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Invalid Cryptographic Algorithm");
            }
        } else {
            bOK = false;
            kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Public Cryptographic Algorithm");
        }

        if (bOK) {
            mapIter = mapAttributesPrivate.find(KMIPUtils::getTagName(kmip::TagCryptographicAlgorithm));
            if (mapIter == mapAttributesPrivate.end() || mapIter->second.empty() || !mapIter->second.front()) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Private Cryptographic Algorithm");
            } else if (iAlg != mapIter->second.front()->getValue<KMIPEnumeration>(0)) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Public Private Cryptographic Algorithm Disagreement");
            }
        }

        if (bOK) {
            auto mapIter = mapAttributesPublic.find(KMIPUtils::getTagName(kmip::TagCryptographicLength));
            if (mapIter != mapAttributesPublic.end() && mapIter->second.size() == 1 && mapIter->second.front().get()) {
                std::shared_ptr<KMIPAttribute> spka = mapIter->second.front();
                iLength = spka->getValue<KMIPInteger>(0);
                iByteLength = static_cast<double>(iLength) / 8 + 0.5;
                bOK = iByteLength > 0;
                if (!bOK) {
                    kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Invalid Cryptographic Length");
                }
            } else {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Public Cryptographic Length");
            }
        }

        if (bOK) {
            mapIter = mapAttributesPrivate.find(KMIPUtils::getTagName(kmip::TagCryptographicLength));
            if (mapIter == mapAttributesPrivate.end() || mapIter->second.empty() || !mapIter->second.front()) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Private Cryptographic Length");
            } else if (iLength != mapIter->second.front()->getValue<KMIPInteger>(0)) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Public Private Cryptographic Length Disagreement");
            }
        }

        if (bOK) {
            mapIter = mapAttributesPublic.find(KMIPUtils::getTagName(kmip::TagCryptographicDomainParameters));
            if (mapIter != mapAttributesPublic.end() && !mapIter->second.empty() && mapIter->second.front()) {
                std::shared_ptr<KMIPAttribute> spka = mapIter->second.front();
                spkf = spka->getValue();
                spkst = std::dynamic_pointer_cast<KMIPStruct>(spkf);
                if (spkst) {
                    iQLength = spkst->getChildValue<KMIPInteger>(kmip::TagQlength, iQLength);
                    iCurve = spkst->getChildValue<KMIPEnumeration>(kmip::TagRecommendedCurve, iCurve);
                }
            }

            mapIter = mapAttributesPrivate.find(KMIPUtils::getTagName(kmip::TagCryptographicDomainParameters));
            if (mapIter == mapAttributesPrivate.end() || mapIter->second.empty() || !mapIter->second.front()) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Missing Private Cryptographic Algorithm");
            } else if (iAlg != mapIter->second.front()->getValue<KMIPEnumeration>(0)) {
                bOK = false;
                kms.addFailure(spkbi, KMIPResultReason::InvalidField, "Public Private Cryptographic Algorithm Disagreement");
            }
        }

        if (bOK) {
            std::string sPubKey;
            std::string sPrivKey;
            generateKeyPair(iAlg, iLength, sPrivKey, sPubKey, iQLength, iCurve);
            sPrivKey = HexUtils::hexEncode(sPrivKey);
            sPubKey = HexUtils::hexEncode(sPubKey);

            std::shared_ptr<KMIPPrivateKey> spPrivKey(new KMIPPrivateKey);
            std::shared_ptr<KMIPKeyBlock> spkb(new KMIPKeyBlock);
            std::shared_ptr<KMIPKeyValue> spkv(new KMIPKeyValue);
            spkv->setKeyMaterialString(sPrivKey);
            spkb->setKeyFormatType(KMIPKeyFormatType::PKCS_8);
            spkb->setKeyValue(spkv);
            spkb->setCryptographicAlgorithm(iAlg);
            spkb->setCryptographicLength(iLength);
            spPrivKey->setKeyBlock(spkb);

            std::shared_ptr<KMIPPublicKey> spPubKey(new KMIPPublicKey);
            spkb.reset(new KMIPKeyBlock);
            spkv.reset(new KMIPKeyValue);
            spkv->setKeyMaterialString(sPrivKey);
            spkb->setKeyFormatType(KMIPKeyFormatType::PKCS_8);
            spkb->setKeyValue(spkv);
            spkb->setCryptographicAlgorithm(iAlg);
            spkb->setCryptographicLength(iLength);
            spPubKey->setKeyBlock(spkb);



            for (auto attr : listAttributesPrivate) {
                bOK = spPrivKey->isAttributeAddable(attr.get(), KMIPOperation::CreateKeyPair, true)
                    && spPrivKey->addAttribute(attr.get());
                if (!bOK) {
                    kms.addFailure(spkbi, KMIPResultReason::InvalidField,
                            std::string("Could not add attribute ") + attr->getName() + " " + std::to_string(attr->getIndex()));
                }
            }


            for (auto attr : listAttributesPublic) {
                bOK = spPubKey->isAttributeAddable(attr.get(), KMIPOperation::CreateKeyPair, true)
                    && spPubKey->addAttribute(attr.get());
                if (!bOK) {
                    kms.addFailure(spkbi, KMIPResultReason::InvalidField,
                            std::string("Could not add attribute ") + attr->getName() + " " + std::to_string(attr->getIndex()));
                }
            }

            std::string sPublicID;
            std::string sPrivateID;
            if (bOK) {
                sPublicID = spkd->getNextID(KMIPObjectType::PublicKey);
                spPubKey->setUniqueID(sPublicID);
                if (spkd->addObject(spPubKey) <= 0) {
                    bOK = false;
                    kms.addFailure(spkbi, KMIPResultReason::GeneralFailure, "Could not add object");
                }
            }

            if (bOK) {
                sPrivateID = spkd->getNextID(KMIPObjectType::PrivateKey);
                spPubKey->setUniqueID(sPrivateID);
                if (spkd->addObject(spPrivKey) <= 0) {
                    bOK = false;
                    kms.addFailure(spkbi, KMIPResultReason::GeneralFailure, "Could not add object");
                }
            }

            if (bOK) {
                KMIPStructSP spkst(new KMIPStruct(kmip::TagResponsePayload));
                spkst->setOrderedTextString(kmip::TagPrivateKeyUniqueIdentifier, sPrivateID);
                spkst->setOrderedTextString(kmip::TagPublicKeyUniqueIdentifier, sPublicID);
                kms.addSuccess(spkbi, spkst);
                kms.setPlaceHolderID(sPrivateID);
            }
        }
    }

    return bOK;
}

bool KMIPOperationCreateKeyPair::generateKeyPair(int iAlg, int iBits, std::string &sPriv, std::string &sPub, int iQLength, int iCurve) {
    bool bOK;
    switch (iAlg) {
        case KMIPCryptographicAlgorithm::RSA:
            {
                RSA *rsa = RSA_new();
                BIGNUM *bn = BN_new();
                bOK = BN_set_word(bn, RSA_F4) &&
                    RSA_generate_key_ex(rsa, iBits, bn, 0);
                if (bOK) {
                    int iPub = i2d_RSAPublicKey(rsa,nullptr);
                    unsigned char *pucPub = new unsigned char[iPub];
                    i2d_RSAPublicKey(rsa, &pucPub);
                    sPub = std::string((char *) pucPub, iPub);
                    delete [] pucPub;

                    int iPriv = i2d_RSAPrivateKey(rsa,nullptr);
                    unsigned char *pucPriv = new unsigned char[iPriv];
                    i2d_RSAPublicKey(rsa, &pucPriv);
                    sPriv = std::string((char *) pucPriv, iPriv);
                    delete [] pucPriv;
                }

                RSA_free(rsa);
                BN_free(bn);
            }
            break;
        case KMIPCryptographicAlgorithm::DSA:
            {
                DSA *dsa = DSA_new();
                bOK = DSA_generate_parameters_ex(dsa, iBits, nullptr, 0, nullptr, nullptr, nullptr) &&
                    DSA_generate_key(dsa);
                if (bOK) {
                    int iPub = i2d_DSAPublicKey(dsa,nullptr);
                    unsigned char *pucPub = new unsigned char[iPub];
                    i2d_DSAPublicKey(dsa, &pucPub);
                    sPub = std::string((char *) pucPub, iPub);
                    delete [] pucPub;

                    int iPriv = i2d_DSAPrivateKey(dsa,nullptr);
                    unsigned char *pucPriv = new unsigned char[iPriv];
                    i2d_DSAPublicKey(dsa, &pucPriv);
                    sPriv = std::string((char *) pucPriv, iPriv);
                    delete [] pucPriv;
                }

                DSA_free(dsa);
            }
            break;
        case KMIPCryptographicAlgorithm::DH:
            {
                DH *dh = DH_new();
                bOK = DH_generate_parameters_ex(dh, iBits, 5, nullptr) &&
                    DH_generate_key(dh);

                if (bOK) {
                    int iPub = BN_num_bytes(dh->pub_key);
                    unsigned char *pucPub = new unsigned char[iPub];
                    BN_bn2bin(dh->pub_key, pucPub);
                    sPub = std::string((char *) pucPub, iPub);
                    delete [] pucPub;

                    int iPriv = BN_num_bytes(dh->priv_key);
                    unsigned char *pucPriv = new unsigned char[iPriv];
                    BN_bn2bin(dh->priv_key, pucPub);
                    sPriv = std::string((char *) pucPriv, iPriv);
                    delete [] pucPriv;
                }

                DH_free(dh);
            }
            break;
        case KMIPCryptographicAlgorithm::EC:
            break;
        case KMIPCryptographicAlgorithm::ECDSA:
            {
                EC_KEY            *myecc  = NULL;
                EVP_PKEY          *pkey   = NULL;
                int               eccgrp;

            }
        case KMIPCryptographicAlgorithm::ECDH:
        case KMIPCryptographicAlgorithm::ECMQV:
            break;
        default:
            break;
    }
    return bOK;
}
