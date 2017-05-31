#ifndef _KMIPENUMERATION_H
#define _KMIPENUMERATION_H

#include "KMIPNumber.h"
#include "EnumMacros.h"

class KMIPEnumeration : public KMIPNumber<uint32_t> {
    public:
        KMIPEnumeration(int iTag, uint32_t eValue = 0, uint32_t eFirst = 0, uint32_t eLast = -1);
        virtual bool isValid() const;
    protected:
        uint32_t eFirst;
        uint32_t eLast;
};

class KMIPCredentialType : public KMIPEnumeration {
#define CREDENTIAL_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(UsernameAndPassword,1)\
    b(Device,2)\
    b(Attestation,3)\
    a(NumValues)

    DECLARE_ENUM_LIST(VALUE, CREDENTIAL_TYPE_LIST);
    KMIPCredentialType(uint32_t eValue);
};



#endif
