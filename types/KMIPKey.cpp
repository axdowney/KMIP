/* Copyright (C) 2017 Alexander Downey */
#include "KMIPKey.h"
#include "KMIPKeyBlock.h"
#include "KMIPEnumeration.h"
#include "KMIPString.h"


        IMPLEMENT_GET_SET_FIELD(KMIPKey, KMIPKeyBlock, KeyBlock, kmip::TagKeyBlock);
KMIPKey::KMIPKey(int iTag) : KMIPManagedObject(iTag) {}
KMIPSymmetricKey::KMIPSymmetricKey() : KMIPKey(kmip::TagSymmetricKey) {}
int KMIPSymmetricKey::getObjectType() const {
    return KMIPObjectType::SymmetricKey;
}

KMIPPublicKey::KMIPPublicKey() : KMIPKey(kmip::TagPublicKey) {}
int KMIPPublicKey::getObjectType() const {
    return KMIPObjectType::PublicKey;
}

KMIPPrivateKey::KMIPPrivateKey() : KMIPKey(kmip::TagPrivateKey) {}
int KMIPPrivateKey::getObjectType() const {
    return KMIPObjectType::PrivateKey;
}

KMIPSplitKey::KMIPSplitKey() : KMIPKey(kmip::TagSplitKey) {}
int KMIPSplitKey::getObjectType() const {
    return KMIPObjectType::SplitKey;
}

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSplitKey, Integer, int, SplitKeyParts, kmip::TagSplitKeyParts);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSplitKey, Integer, int, KeyPartIdentifier, kmip::TagKeyPartIdentifier);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSplitKey, Integer, int, SplitKeyThreshold, kmip::TagSplitKeyThreshold);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSplitKey, Enumeration, uint32_t, SplitKeyMethod, kmip::TagSplitKeyMethod);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSplitKey, BigInteger, std::string, PrimeFieldSize, kmip::TagPrimeFieldSize);

KMIPSecretData::KMIPSecretData() : KMIPKey(kmip::TagSecretData) {}
int KMIPSecretData::getObjectType() const {
    return KMIPObjectType::SecretData;
}

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPSecretData, Enumeration, uint32_t, SecretDataType, kmip::TagSecretDataType);
KMIPPGPKey::KMIPPGPKey() : KMIPKey(kmip::TagPGPKey) {}
int KMIPPGPKey::getObjectType() const {
    return KMIPObjectType::PGPKey;
}

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPPGPKey, Integer, int, PGPKeyVersion, kmip::TagPGPKeyVersion);
