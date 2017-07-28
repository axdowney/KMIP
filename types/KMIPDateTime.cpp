#include "KMIPDateTime.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

KMIPDateTime::KMIPDateTime(int iTag, const DateTime &dtValue) : KMIPField(iTag, kmip::TypeDateTime) {
    setValue(dtValue);
}

KMIPField *KMIPDateTime::clone() const {
    KMIPDateTime *pkdt = clone2<KMIPDateTime, KMIPField>();
    if (pkdt) {
        pkdt->setValue(getValue());
    }

    return pkdt;
}

const DateTime &KMIPDateTime::getValue() const {
    return dtValue;
}

void KMIPDateTime::setValue(const DateTime &dtValue) {
    this->dtValue = dtValue;
}

std::string KMIPDateTime::getValueString() const {
    return dtValue.toString("%FT%T");
}

bool KMIPDateTime::setValueFromTTLV(const std::string &sValue) {
    dtValue.setTime(static_cast<time_t>(KMIPTTLVEncoding::binaryToInt(sValue)));
    return true;
}

std::string KMIPDateTime::getTTLVValue() const {
    int iBytes = calculateLength();
    std::string sRet = KMIPTTLVEncoding::intToBinary(getValue().toTime(), iBytes);
    return sRet + KMIPTTLVEncoding::getBuffer(KMIPUtils::getTotalLength(getType()) - iBytes);
}

std::string KMIPDateTime::getTTLVValueTrim() const {
    int iBytes = calculateLength();
    return KMIPTTLVEncoding::intToBinary(getValue().toTime(), iBytes);
}

bool KMIPDateTime::operator==(const KMIPField &kfRight) const {
    const KMIPDateTime *pkdt = dynamic_cast<const KMIPDateTime *>(&kfRight);
    return pkdt && operator==(*pkdt);
}

bool KMIPDateTime::operator==(const KMIPDateTime &kfRight) const {
    return this->KMIPField::operator==(kfRight)
        && getValue() == kfRight.getValue();
}

