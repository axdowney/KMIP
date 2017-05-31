#include "KMIPDateTime.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

KMIPDateTime::KMIPDateTime(int iTag, const DateTime &dtValue) : KMIPField(iTag, kmip::TypeDateTime) {
    setValue(dtValue);
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

