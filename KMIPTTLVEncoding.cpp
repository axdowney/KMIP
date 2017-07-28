#include "KMIPTTLVEncoding.h"
#include "KMIPDefs.h"
#include "KMIPUtils.h"
#include "KMIPStruct.h"

KMIPFieldUP KMIPTTLVEncoding::decodeKMIP(std::string sField, std::string &sExtra) const {
    sExtra = "";
    KMIPFieldUP upkf;
    if (sField.size() >= kmip::kiMinFieldSize) {
        std::string sTag = sField.substr(0, kmip::kiTagSize);
        std::string sType = sField.substr(kmip::kiTagSize, kmip::kiTypeSize);
        std::string sLength = sField.substr(kmip::kiTagSize + kmip::kiTypeSize, kmip::kiLengthSize);
        std::string sValue = sField.substr(kmip::kiMinFieldSize);
        int iTag = binaryToInt(sTag);
        int iType = binaryToInt(sType);
        upkf = KMIPUtils::createField(iTag, iType);
        if (upkf) {
            unsigned long int iLength = binaryToInt(sLength);
            unsigned long int iTotalLength = KMIPUtils::getTotalLength(iLength);
            sExtra = sValue.substr(iTotalLength);
            sValue = sValue.substr(0, iLength);
            upkf->setLength(iLength);
            if (iType == kmip::TypeStructure) {
                KMIPStruct *pkst = dynamic_cast<KMIPStruct *>(upkf.get());
                if (!decodeKMIPStruct(pkst, sValue)) {
                    upkf.reset();
                }
            } else {
                if (!decodeKMIPSingleField(upkf.get(), sValue)) {
                    upkf.reset();
                }
            }
        }
    }

    return upkf;
}

bool KMIPTTLVEncoding::decodeKMIPSingleField(KMIPField *pkf, const std::string &sValue) const {
    return pkf && pkf->getType() != kmip::TypeStructure && pkf->setValueFromTTLV(sValue);
}

bool KMIPTTLVEncoding::decodeKMIPStruct(KMIPStruct *pkst, const std::string &sFields) const {
    bool bOK = pkst;
    if (bOK) {
        std::string sExtra(sFields);
        while (!sExtra.empty()) {
            KMIPFieldUP upkf = decodeKMIP(sExtra, sExtra);
            if (upkf) {
                pkst->addField(KMIPFieldSP(upkf.release()));
            } else {
                bOK = false;
                break;
            }
        }
    }

    return bOK;
}

std::string KMIPTTLVEncoding::encodeKMIP(KMIPField *pkf) const {
    std::string sRet;
    if (pkf) {
        sRet = KMIPTTLVEncoding::encodeTagTypeLength(pkf->getTag(), pkf->getType(), pkf->calculateLength())
            + pkf->getTTLVValue();
    }

    return sRet;
}

unsigned long int KMIPTTLVEncoding::binaryToInt(const std::string &s) {
    unsigned long int uliRet = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        uliRet = (uliRet << 8) + (unsigned char) s[i];
    }

    return uliRet;
}

std::string KMIPTTLVEncoding::intToBinary(unsigned long int iNumber, unsigned int iBytes) {
    std::string sRet(iBytes, '\000');
    unsigned long int iFlags = 0x0FF;
    for (int i = 0; i < iBytes; ++i) {
        sRet[iBytes - i - 1] = static_cast<char>(((iNumber & iFlags) >> (i * 8)));
        iFlags = iFlags << 8;
    }

    return sRet;
}


std::string KMIPTTLVEncoding::getBuffer(unsigned int iLength) {
    return std::string(iLength, '\000');
}

std::string KMIPTTLVEncoding::encodeTagTypeLength(int iTag, int iType, kmipsize_t iLength) {
        return intToBinary(iTag, kmip::kiTagSize) + intToBinary(iType, kmip::kiTypeSize)
            + intToBinary(iLength, kmip::kiLengthSize);
}
