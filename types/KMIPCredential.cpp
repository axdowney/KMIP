/* Copyright (C) 2017 Alexander Downey */
#include "KMIPCredential.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"
#include "KMIPNumber.h"

KMIPNonce::KMIPNonce() : KMIPStruct(kmip::TagNonce) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPNonce, ByteString, std::string, NonceID, kmip::TagNonceID);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPNonce, ByteString, std::string, NonceValue, kmip::TagNonceValue);

KMIPCredentialValue::KMIPCredentialValue() : KMIPStruct(kmip::TagCredentialValue) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, Username, kmip::TagUsername);

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, DeviceSerialNumber, kmip::TagDeviceSerialNumber);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, Password, kmip::TagPassword);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, DeviceIdentifier, kmip::TagDeviceIdentifier);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, NetworkIdentifier, kmip::TagNetworkIdentifier);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, MachineIdentifier, kmip::TagMachineIdentifier);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, TextString, std::string, MediaIdentifier, kmip::TagMediaIdentifier);

        IMPLEMENT_GET_SET_FIELD(KMIPCredentialValue, KMIPNonce, Nonce, kmip::TagNonce);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, Enumeration, uint32_t, AttestationType, kmip::TagAttestationType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, ByteString, std::string, AttestationMeasurement, kmip::TagAttestationMeasurement);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredentialValue, ByteString, std::string, AttestationAssertion, kmip::TagAttestationAssertion);

KMIPCredential::KMIPCredential() : KMIPStruct(kmip::TagCredential) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCredential, Enumeration, uint32_t, CredentialType, kmip::TagCredentialType);
        IMPLEMENT_GET_SET_FIELD(KMIPCredential, KMIPCredentialValue, CredentialValue, kmip::TagCredentialValue);
