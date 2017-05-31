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


    protected:
        DateTime dtValue;
};

#endif
