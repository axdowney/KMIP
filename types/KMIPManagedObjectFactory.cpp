/* Copyright (C) 2017 Alexander Downey */
#include "KMIPManagedObjectFactory.h"
#include "KMIPDefs.h"
#include "KMIPManagedObject.h"
#include "KMIPCertificate.h"
#include "KMIPKey.h"
#include "KMIPOpaqueObject.h"
#include "KMIPTemplate.h"


KMIPFieldUP KMIPManagedObjectFactory::createField(int iTag) const {
    return createObject(iTag);
}

KMIPManagedObjectUP KMIPManagedObjectFactory::createObject(int iTag) const {
    KMIPManagedObjectUP upkst;
    switch(iTag) {
        case kmip::TagCertificate:
            upkst.reset(new KMIPCertificate());
            break;
        case kmip::TagSymmetricKey:
            upkst.reset(new KMIPSymmetricKey());
            break;
        case kmip::TagPublicKey:
            upkst.reset(new KMIPPublicKey());
            break;
        case kmip::TagPrivateKey:
            upkst.reset(new KMIPPrivateKey());
            break;
        case kmip::TagSplitKey:
            upkst.reset(new KMIPSplitKey());
            break;
        case kmip::TagTemplate:
            upkst.reset(new KMIPTemplate());
            break;
        case kmip::TagSecretData:
            upkst.reset(new KMIPSecretData());
            break;
        case kmip::TagOpaqueObject:
            upkst.reset(new KMIPOpaqueObject());
            break;
        case kmip::TagPGPKey:
            upkst.reset(new KMIPPGPKey());
            break;
        default:
            break;
    }

    return upkst;
}
