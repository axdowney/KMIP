/* Copyright (C) 2017 Alexander Downey */
#include "KMIPKeyWrappingData.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"
#include "KMIPAttributeStructs.h"
KMIPEncryptionKeyInformation::KMIPEncryptionKeyInformation() : KMIPStruct(kmip::TagEncryptionKeyInformation) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPEncryptionKeyInformation, TextString, std::string, UniqueIdentifier, kmip::TagUniqueIdentifier);
        IMPLEMENT_GET_SET_FIELD(KMIPEncryptionKeyInformation, KMIPCryptographicParameters, CryptographicParameters, kmip::TagCryptographicParameters);

KMIPMACSignatureKeyInformation::KMIPMACSignatureKeyInformation() : KMIPStruct(kmip::TagMACSignatureKeyInformation) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPMACSignatureKeyInformation, TextString, std::string, UniqueIdentifier, kmip::TagUniqueIdentifier);
        IMPLEMENT_GET_SET_FIELD(KMIPMACSignatureKeyInformation, KMIPCryptographicParameters, CryptographicParameters, kmip::TagCryptographicParameters);

KMIPKeyWrappingData::KMIPKeyWrappingData() : KMIPStruct(kmip::TagKeyWrappingData) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingData, Enumeration, uint32_t, WrappingMethod, kmip::TagWrappingMethod);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyWrappingData, KMIPEncryptionKeyInformation, EncryptionKeyInformation, kmip::TagEncryptionKeyInformation);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyWrappingData, KMIPMACSignatureKeyInformation, MACSignatureKeyInformation, kmip::TagMACSignatureKeyInformation);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingData, ByteString, std::string, MACSignature, kmip::TagMACSignature);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingData, ByteString, std::string, IVCounterNonce, kmip::TagIVCounterNonce);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyWrappingData, Enumeration, uint32_t, EncodingOption, kmip::TagEncodingOption);
