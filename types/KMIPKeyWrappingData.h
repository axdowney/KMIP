/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPKEYWRAPPINGDATA_H
#define _KMIPKEYWRAPPINGDATA_H

#include "KMIPStruct.h"
class KMIPCryptographicParameters;
class KMIPEncryptionKeyInformation : public KMIPStruct {
    public:
        KMIPEncryptionKeyInformation();
        DECLARE_GET_SET_FIELD_VALUE(std::string, UniqueIdentifier);
        DECLARE_GET_SET_FIELD(KMIPCryptographicParameters, CryptographicParameters);

};

class KMIPMACSignatureKeyInformation : public KMIPStruct {
    public:
        KMIPMACSignatureKeyInformation();
        DECLARE_GET_SET_FIELD_VALUE(std::string, UniqueIdentifier);
        DECLARE_GET_SET_FIELD(KMIPCryptographicParameters, CryptographicParameters);

};

class KMIPKeyWrappingData : public KMIPStruct {
    public:
        KMIPKeyWrappingData();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, WrappingMethod);
        DECLARE_GET_SET_FIELD(KMIPEncryptionKeyInformation, EncryptionKeyInformation);
        DECLARE_GET_SET_FIELD(KMIPMACSignatureKeyInformation, MACSignatureKeyInformation);
        DECLARE_GET_SET_FIELD_VALUE(std::string, MACSignature);
        DECLARE_GET_SET_FIELD_VALUE(std::string, IVCounterNonce);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, EncodingOption);


};


#endif
