/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPKEYWRAPPINGSPECIFICATION_H
#define _KMIPKEYWRAPPINGSPECIFICATION_H

#include "KMIPStruct.h"

class KMIPEncryptionKeyInformation;
class KMIPMACSignatureKeyInformation;
class KMIPKeyWrappingSpecification : public KMIPStruct {
    public:
        KMIPKeyWrappingSpecification();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, WrappingMethod);
        DECLARE_GET_SET_FIELD(KMIPEncryptionKeyInformation, EncryptionKeyInformation);
        DECLARE_GET_SET_FIELD(KMIPMACSignatureKeyInformation, MACSignatureKeyInformation);
        DECLARE_GET_SET_FIELD_VALUE(std::string, AttributeName);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, EncodingOption);
};


#endif
