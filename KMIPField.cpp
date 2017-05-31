#include "KMIPField.h"
#include "KMIPDefs.h"
KMIPField::KMIPField(int iTag, int iType) {
    this->iTag = iTag;
    this->iType = iType;
    iLength = KMIPField::kiInvalidLength;
}

int KMIPField::getTag() const {
    return iTag;
}

int KMIPField::getType() const {
    return iType;
}

int KMIPField::getLength() const {
    return iLength;
}

void KMIPField::setLength(kmipsize_t iLength) {
    this->iLength = iLength;
}

kmipsize_t KMIPField::calculateLength() const {
    int iRet = kiInvalidLength;
    switch (getType()) {
        case kmip::TypeInteger:
        case kmip::TypeEnumeration:
        case kmip::TypeInterval:
            iRet = kmip::kiIntegerSize;
            break;
        case kmip::TypeLongInteger:
        case kmip::TypeBoolean:
        case kmip::TypeDateTime:
            iRet = kmip::kiLongIntegerSize;
            break;
        default:
            break;

    }

    return iRet;
}

kmipsize_t KMIPField::setCalculatedLength() {
    setLength(calculateLength());
    return getLength();
}

std::string KMIPField::getValueString() const {
    return "";
}

bool KMIPField::setValueFromTTLV(const std::string &sValue) {
    return false;
}

std::string KMIPField::getTTLVValue() const {
    return "";
}
