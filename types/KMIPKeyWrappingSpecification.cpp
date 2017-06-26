/* Copyright (C) 2017 Alexander Downey */
#include "KMIPKeyWrappingSpecification.h"
#include "KMIPKeyWrappingData.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"


KMIPKeyWrappingSpecification::KMIPKeyWrappingSpecification() : KMIPStruct(kmip::TagKeyWrappingSpecification) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingSpecification, Enumeration, uint32_t, WrappingMethod, kmip::TagWrappingMethod);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyWrappingSpecification, KMIPEncryptionKeyInformation, EncryptionKeyInformation, kmip::TagEncryptionKeyInformation);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyWrappingSpecification, KMIPMACSignatureKeyInformation, MACSignatureKeyInformation, kmip::TagMACSignatureKeyInformation);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingSpecification, TextString, std::string, AttributeName, kmip::TagAttributeName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingSpecification, Enumeration, uint32_t, EncodingOption, kmip::TagEncodingOption);
