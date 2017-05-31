#ifndef _KMIPNUMBER_H
#define _KMIPNUMBER_H

#include <cstdint>
#include <sstream>
#include "KMIPField.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

template<class T>
class KMIPNumber : public KMIPField {
    public:
        T getValue() const {
            return val;
        }

        void setValue(T value) {
            this->val = value;
        }

        virtual std::string getValueString() const {
            std::stringstream ss;
            ss << val;
            return ss.str();
        }

        virtual bool setValueFromTTLV(const std::string &sValue) {
            setValue(static_cast<T>(KMIPTTLVEncoding::binaryToInt(sValue)));
            return true;
        }

        virtual std::string getTTLVValue() const {
            kmipsize_t iBytes = calculateLength();
            std::string sRet = KMIPTTLVEncoding::intToBinary(getValue(), iBytes);
            return sRet + KMIPTTLVEncoding::getBuffer(KMIPUtils::getTotalLength(getType()) - iBytes);
        }

    protected:
        KMIPNumber(int iTag, int iType, T val) : KMIPField(iTag, iType) {
            this->val = val;
        }
        T val;
};


class KMIPInteger : public KMIPNumber<int> {
    public:
        KMIPInteger(int iTag, int val = int()) : KMIPNumber(iTag, kmip::TypeInteger, val) {}
};

class KMIPLongInteger : public KMIPNumber<long int> {
    public:
        KMIPLongInteger(int iTag, long int val = int()) : KMIPNumber(iTag, kmip::TypeLongInteger, val) {}
};

class KMIPBoolean : public KMIPNumber<bool> {
    public:
        KMIPBoolean(int iTag, bool val = bool()) : KMIPNumber(iTag, kmip::TypeBoolean, val) {}
};

class KMIPInterval : public KMIPNumber<uint32_t> {
    public:
        KMIPInterval(int iTag, uint32_t val = uint32_t()) : KMIPNumber(iTag, kmip::TypeInterval, val) {}
};

#endif
