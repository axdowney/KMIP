#include "KMIPString.h"
#include "HexUtils.h"
#include "KMIPUtils.h"
#include "KMIPTTLVEncoding.h"

KMIPString::KMIPString(int iTag, int iType, const std::string &sValue) : KMIPField(iTag, iType) {
    this->sValue = sValue;
}

const std::string &KMIPString::getValue() const {
    return sValue;
}

std::string KMIPString::getValueString() const {
    return getValue();
}

void KMIPString::setValue(const std::string &sValue) {
    this->sValue = sValue;
}

bool KMIPString::setValueFromTTLV(const std::string &sValue) {
    setValue(HexUtils::hexEncode(sValue));
    return true;
}

KMIPTextString::KMIPTextString(int iTag, const std::string &sValue) : KMIPString(iTag, kmip::TypeTextString, sValue) {}

kmipsize_t KMIPTextString::calculateLength() const {
    return sValue.size();
}

bool KMIPTextString::setValueFromTTLV(const std::string &sValue) {
    setValue(sValue);
    return true;
}

std::string KMIPTextString::getTTLVValue() const {
    kmipsize_t iBytes = calculateLength();
    return getValue() + KMIPTTLVEncoding::getBuffer(KMIPUtils::getTotalLength(iBytes) - iBytes);
}

KMIPByteString::KMIPByteString(int iTag, const std::string &sValue) : KMIPString(iTag, kmip::TypeByteString, sValue) {}

kmipsize_t KMIPByteString::calculateLength() const {
    return sValue.size() / 2;
}

std::string KMIPByteString::getTTLVValue() const {
    kmipsize_t iBytes = calculateLength();
    return HexUtils::hexDecode(getValue()) + KMIPTTLVEncoding::getBuffer(KMIPUtils::getTotalLength(iBytes) - iBytes);
}

KMIPBigInteger::KMIPBigInteger(int iTag, const std::string &sValue) : KMIPString(iTag, kmip::TypeBigInteger, sValue) {}

kmipsize_t KMIPBigInteger::calculateLength() const {
    return KMIPUtils::getTotalLength(sValue.size() / 2);
}

std::string KMIPBigInteger::getTTLVValue() const {
    kmipsize_t iBytes = calculateLength();
    std::string sRet = HexUtils::hexDecode(getValue()); 
    return KMIPTTLVEncoding::getBuffer(iBytes - sRet.size()) + sRet;
}

