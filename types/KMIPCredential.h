/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPCREDENTIAL_H
#define _KMIPCREDENTIAL_H

#include "KMIPStruct.h"

class KMIPNonce : public KMIPStruct {
    public:
        KMIPNonce();
        DECLARE_GET_SET_FIELD_VALUE(std::string, NonceID);
        DECLARE_GET_SET_FIELD_VALUE(std::string, NonceValue);

};

class KMIPCredentialValue : public KMIPStruct {
    public:
        KMIPCredentialValue();
        DECLARE_GET_SET_FIELD_VALUE(std::string, Username);

        DECLARE_GET_SET_FIELD_VALUE(std::string, DeviceSerialNumber);
        DECLARE_GET_SET_FIELD_VALUE(std::string, Password);
        DECLARE_GET_SET_FIELD_VALUE(std::string, DeviceIdentifier);
        DECLARE_GET_SET_FIELD_VALUE(std::string, NetworkIdentifier);
        DECLARE_GET_SET_FIELD_VALUE(std::string, MachineIdentifier);
        DECLARE_GET_SET_FIELD_VALUE(std::string, MediaIdentifier);

        DECLARE_GET_SET_FIELD(KMIPNonce, Nonce);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, AttestationType);
        DECLARE_GET_SET_FIELD_VALUE(std::string, AttestationMeasurement);
        DECLARE_GET_SET_FIELD_VALUE(std::string, AttestationAssertion);

};

class KMIPCredential : public KMIPStruct {
    public:
        KMIPCredential();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, CredentialType);
        DECLARE_GET_SET_FIELD(KMIPCredentialValue, CredentialValue);
};



#endif
