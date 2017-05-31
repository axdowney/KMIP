#ifndef _KMIPSTRING_H
#define _KMIPSTRING_H

#include <string>
#include "KMIPField.h"
#include "KMIPDefs.h"

class KMIPString : public KMIPField {
    public:
        const std::string &getValue() const;
        virtual std::string getValueString() const;
        void setValue(const std::string &sValue);
        virtual bool setValueFromTTLV(const std::string &sValue);
    protected:
        KMIPString(int iTag, int iType, const std::string &sValue);
        std::string sValue;
};

class KMIPTextString : public KMIPString {
    public:
        KMIPTextString(int iTag, const std::string &sValue = std::string());
        virtual kmipsize_t calculateLength() const;
        virtual bool setValueFromTTLV(const std::string &sValue);
        virtual std::string getTTLVValue() const;
};

class KMIPByteString : public KMIPString {
    public:
        KMIPByteString(int iTag, const std::string &sValue = std::string());
        virtual kmipsize_t calculateLength() const;
        virtual std::string getTTLVValue() const;
};

class KMIPBigInteger : public KMIPString {
    public:
        KMIPBigInteger(int iTag, const std::string &sValue = std::string());
        virtual kmipsize_t calculateLength() const;
        virtual std::string getTTLVValue() const;
};

#endif
