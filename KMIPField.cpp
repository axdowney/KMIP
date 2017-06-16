#include "KMIPField.h"
#include "KMIPDefs.h"
#include "KMIPUtils.h"

KMIPField::KMIPField(int iTag, int iType) {
    this->iTag = iTag;
    this->iType = iType;
    iLength = KMIPField::kiInvalidLength;
    bAttributeValue = false;
}

int KMIPField::getTag() const {
    return bAttributeValue ? kmip::TagAttributeValue : iTag;
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

int KMIPField::getTrueTag() const {
    return iTag;
}

bool KMIPField::isAttributeValueForced() const {
    return bAttributeValue;
}

bool KMIPField::forceAttributeValue(bool bForce) {
    return bAttributeValue = bForce;
}

std::string KMIPField::getValueString() const {
    return "";
}

bool KMIPField::isValid() const {
    return true;
}


KMIPFieldSP KMIPField::cloneShared() const {
    return KMIPFieldSP(clone());
}

KMIPFieldUP KMIPField::cloneUnique() const {
    return KMIPFieldUP(clone());
}

KMIPField *KMIPField::clone() const {
    KMIPField *pkf = KMIPUtils::createField(getTrueTag(), getType()).release();
    if (pkf) {
        pkf->forceAttributeValue(isAttributeValueForced());
    }

    return pkf;
}

bool KMIPField::setValueFromTTLV(const std::string &sValue) {
    return false;
}

std::string KMIPField::getTTLVValue() const {
    return "";
}
