/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPKEY_H
#define _KMIPKEY_H

#include "KMIPManagedObject.h"

class KMIPKeyBlock;
class KMIPKey : public KMIPManagedObject {
    public:
        DECLARE_GET_SET_FIELD(KMIPKeyBlock, KeyBlock);
    protected:
        KMIPKey(int iTag);
};

class KMIPSymmetricKey : public KMIPKey {
    public:
        KMIPSymmetricKey();
        virtual int getObjectType() const;
};

class KMIPPublicKey : public KMIPKey {
    public:
        KMIPPublicKey();
        virtual int getObjectType() const;
};

class KMIPPrivateKey : public KMIPKey {
    public:
        KMIPPrivateKey();
        virtual int getObjectType() const;
};

class KMIPSplitKey : public KMIPKey {
    public:
        KMIPSplitKey();
        virtual int getObjectType() const;
        DECLARE_GET_SET_FIELD_VALUE(int, SplitKeyParts);
        DECLARE_GET_SET_FIELD_VALUE(int, KeyPartIdentifier);
        DECLARE_GET_SET_FIELD_VALUE(int, SplitKeyThreshold);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, SplitKeyMethod);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PrimeFieldSize)

};

class KMIPSecretData : public KMIPKey {
    public:
        KMIPSecretData();
        virtual int getObjectType() const;
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, SecretDataType);
};

class KMIPPGPKey : public KMIPKey {
    public:
        KMIPPGPKey();
        virtual int getObjectType() const;
        DECLARE_GET_SET_FIELD_VALUE(int, PGPKeyVersion);
};
#endif
