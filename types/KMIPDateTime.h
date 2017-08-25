#ifndef _KMIPDATETIME_H
#define _KMIPDATETIME_H

#include "KMIPField.h"
#include "DateTime.h"

class KMIPDateTime : public KMIPField {
    public:
        KMIPDateTime(int iTag, const DateTime &dtValue = DateTime());
        const DateTime &getValue() const;
        void setValue(const DateTime &dtValue);
        virtual std::string getValueString() const;

        virtual bool setValueFromTTLV(const std::string &sValue);
        virtual std::string getTTLVValue() const;
        virtual std::string getTTLVValueTrim() const;

        virtual bool setValueFromXML(const std::string &sValue);
        virtual std::string getXMLValue() const;

        virtual bool operator==(const KMIPField &kfRight) const;
        bool operator==(const KMIPDateTime &kfLeft) const;

    protected:
        virtual KMIPField *clone() const;
        DateTime dtValue;
};

#endif
