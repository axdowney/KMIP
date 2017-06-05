/* Copyright (C) 2017 Alexander Downey */
#include "KMIPBitMask.h"

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
}

std::string KMIPBitMask::getFlagName(int iFlag) const {
    return "";
}


KMIPCryptographicUsageMask::KMIPCryptographicUsageMask(int iVal) : KMIPBitMask(kmip::TagCryptographicUsageMask, iVal, KMIPCryptographicUsageMask::FullMask) {}

std::string KMIPCryptographicUsageMask::getFlagName(int iFlag) const {
    return this->VALUEToString(static_cast<VALUE>(iFlag));
}

IMPLEMENT_ENUM_TO_STRING(KMIPCryptographicUsageMask, VALUE, None, "", CRYPTOGRAPHIC_USAGE_MASK_LIST);

KMIPStorageStatusMask::KMIPStorageStatusMask(int iVal) : KMIPBitMask(kmip::TagStorageStatusMask, iVal, KMIPStorageStatusMask::FullMask) {}

std::string KMIPStorageStatusMask::getFlagName(int iFlag) const {
    return this->VALUEToString(static_cast<VALUE>(iFlag));
}

IMPLEMENT_ENUM_TO_STRING(KMIPStorageStatusMask, VALUE, None, "", STORAGE_STATUS_MASK_LIST);
