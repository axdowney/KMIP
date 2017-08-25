/* Copyright (C) 2017 Alexander Downey */
#include "KMIPBitMask.h"
#include <sstream>
#include "StringUtils.h"

KMIPBitMask::KMIPBitMask(int iTag, int iVal, int iFullMask) : KMIPInteger(iTag, iVal) {
    this->iFullMask = iFullMask;
}

bool KMIPBitMask::isValid() const {
    return !(getValue() & ~getFullMask());
}

int KMIPBitMask::getFullMask() const {
    return iFullMask;
}

std::vector<int> KMIPBitMask::splitFlags() const {
    std::vector<int> vecRet;
    int iMask = getFullMask();
    int iBit = 1;
    int iNum = 0;
    while (iMask != 0) {
        if (iMask & 1) {
            vecRet.push_back(iBit);
        }
        iMask = iMask >> 1;
        iBit = iBit << 1;
    }

    return vecRet;
}

std::string KMIPBitMask::getFlagName(int iFlag) const {
    return "";
}

int KMIPBitMask::getFlagFromName(std::string sFlag) const {
    return 0;
}

std::vector<std::string> KMIPBitMask::getFlagNames(int iFlags, bool bHexInvalidBits) const {
    std::vector<std::string> vecRet;
    int iLeftOverBits = iFlags;
    std::vector<int> vecFlags = splitFlags();
    for (int iFlag : vecFlags) {
        if ((iFlags & iFlag) != 0) {
            std::string sRet = getFlagName(iFlag);
            if (!sRet.empty()) {
                iLeftOverBits &= ~iFlag;
                vecRet.push_back(sRet);
            }
        }
    }

    if (bHexInvalidBits && iLeftOverBits != 0) {
        std::stringstream ss;
        ss << std::showbase << std::hex << iLeftOverBits;
        vecRet.push_back(ss.str());
    }

    return vecRet;
}

std::string KMIPBitMask::getFlagsString(int iFlags, bool bHexInvalidBits) const {
    std::string sRet;
    std::vector<std::string> vecFlags = getFlagNames(iFlags, bHexInvalidBits);
    StringUtils::combine(sRet, "  ", vecFlags);
    return sRet;
}

int KMIPBitMask::getFlagsFromString(const std::string &sFlags, bool bAllowNumber) const {
    int iFlags = 0;
    std::vector<std::string> vecFlags;
    StringUtils::split(sFlags, " ", vecFlags);
    for (size_t i = 0; i < vecFlags.size(); i++) {
        int iFlag = getFlagFromName(vecFlags[i]);
        if (iFlag == 0 && bAllowNumber) {
            try {
                iFlag = std::stoi(vecFlags[i], nullptr, 0);
            } catch (std::invalid_argument) {
                iFlag = 0;
            }
        }

        iFlags += iFlag;
    }

    return iFlags;
}

bool KMIPBitMask::setValueFromXML(const std::string &sValue) {
    setValue(getFlagsFromString(sValue, true));
    return isValid();
}

std::string KMIPBitMask::getXMLValue() const {
    return getFlagsString(getValue(), true);
}

KMIPCryptographicUsageMask::KMIPCryptographicUsageMask(int iVal) : KMIPBitMask(kmip::TagCryptographicUsageMask, iVal, KMIPCryptographicUsageMask::FullMask) {}

std::string KMIPCryptographicUsageMask::getFlagName(int iFlag) const {
    return this->VALUEToString(static_cast<VALUE>(iFlag));
}

int KMIPCryptographicUsageMask::getFlagFromName(std::string sFlag) const {
    return VALUEFromString(sFlag);
}

IMPLEMENT_ENUM_TO_STRING(KMIPCryptographicUsageMask, VALUE, None, "", CRYPTOGRAPHIC_USAGE_MASK_LIST);

KMIPStorageStatusMask::KMIPStorageStatusMask(int iVal) : KMIPBitMask(kmip::TagStorageStatusMask, iVal, KMIPStorageStatusMask::FullMask) {}

std::string KMIPStorageStatusMask::getFlagName(int iFlag) const {
    return this->VALUEToString(static_cast<VALUE>(iFlag));
}

int KMIPStorageStatusMask::getFlagFromName(std::string sFlag) const {
    return VALUEFromString(sFlag);
}

IMPLEMENT_ENUM_TO_STRING(KMIPStorageStatusMask, VALUE, None, "", STORAGE_STATUS_MASK_LIST);
