#ifndef _KMIPNUMBER_H
#define _KMIPNUMBER_H

#include <cstdint>
#include <sstream>
#include <iostream>
#include "KMIPField.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

template<class T>
class KMIPNumber : public KMIPField {
    public:
        ~KMIPNumber() {
//            std::cerr << "Deleting a " << KMIPUtils::printFieldString(this);
        }

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
        
        virtual std::string getTTLVValueTrim() const {
            kmipsize_t iBytes = calculateLength();
            return KMIPTTLVEncoding::intToBinary(getValue(), iBytes);
        }

        virtual std::string getTTLVValue() const {
            kmipsize_t iBytes = calculateLength();
            std::string sRet = KMIPTTLVEncoding::intToBinary(getValue(), iBytes);
            return sRet + KMIPTTLVEncoding::getBuffer(KMIPUtils::getTotalLength(getType()) - iBytes);
        }

        virtual bool setValueFromXML(const std::string &sValue) {
            bool bRet = true;
            try {
                this->val = static_cast<T>(std::stoll(sValue, nullptr, 0));
            } catch (std::invalid_argument e) {
                bRet = false;
            }

            return bRet;
        }

        virtual std::string getXMLValue() const {
            std::stringstream ss;
            ss << val;
            return ss.str();
        }

        bool operator==(const KMIPNumber<T> &kfRight) const {
            return this->KMIPField::operator==(kfRight)
                && getValue() == kfRight.getValue();
        }

        virtual bool operator==(const KMIPField &kfRight) const {
            const KMIPNumber<T> *kpkn = dynamic_cast<const KMIPNumber<T> *>(&kfRight);
            return kpkn ? *this == *kpkn : false;
        }

    protected:
        KMIPNumber(int iTag, int iType, T val) : KMIPField(iTag, iType) {
            this->val = val;
        }
        virtual KMIPField *clone() const {
            KMIPField *pkf = KMIPField::clone();
            KMIPNumber<T> *pkn = dynamic_cast<KMIPNumber<T> *>(pkf);
            if (pkn) {
                pkn->setValue(getValue());
            } else if (pkf) {
                delete pkf;
                pkf = nullptr;
            }

            return pkf;
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
        virtual bool setValueFromXML(const std::string &sValue) {
            if (!KMIPNumber::setValueFromXML(sValue)) {
                std::string sVal = sValue;
                for (char &c : sVal) {
                    c = std::toupper(c);
                }
                val = sVal == "TRUE";
            }
            return true;
        }

        virtual std::string getXMLValue() const {
            return val ? "true" : "false";
        }

};

class KMIPInterval : public KMIPNumber<uint32_t> {
    public:
        KMIPInterval(int iTag, uint32_t val = uint32_t()) : KMIPNumber(iTag, kmip::TypeInterval, val) {}
};

#endif
