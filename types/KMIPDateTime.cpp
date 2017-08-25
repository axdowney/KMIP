#include "KMIPDateTime.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

#include "strtk.hpp"
#include "datetime_utils.hpp"

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

bool KMIPDateTime::setValueFromXML(const std::string &sValue) {
    dt_utils::datetime udt;
    udt.clear();
    dt_utils::datetime_format19 fmt19(udt);
    dt_utils::datetime_format10 fmt10(udt);
    bool bOK = strtk::string_to_type_converter(sValue, fmt19)
        || strtk::string_to_type_converter(sValue, fmt10);
    if (bOK) {
        struct tm tmValue;
        tmValue.tm_year = udt.year - 1900;
        tmValue.tm_mon = udt.month - 1;
        tmValue.tm_mday = udt.day;
        tmValue.tm_hour = udt.hour;
        tmValue.tm_min = udt.minute;
        tmValue.tm_sec = udt.second;
        time_t t = timegm(&tmValue);
        t -= udt.tzd * 60;
        dtValue.setTime(t);
    }

    return bOK;
}

std::string KMIPDateTime::getXMLValue() const {
    return dtValue.toString("%FT%T+00:00");
}

bool KMIPDateTime::operator==(const KMIPField &kfRight) const {
    const KMIPDateTime *pkdt = dynamic_cast<const KMIPDateTime *>(&kfRight);
    return pkdt && operator==(*pkdt);
}

bool KMIPDateTime::operator==(const KMIPDateTime &kfRight) const {
    return this->KMIPField::operator==(kfRight)
        && getValue() == kfRight.getValue();
}

