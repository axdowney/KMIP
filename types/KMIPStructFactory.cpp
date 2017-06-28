/* Copyright (C) 2017 Alexander Downey */

#include "KMIPStructFactory.h"
#include "KMIPStruct.h"
#include "KMIPAttribute.h"
#include "KMIPAttributeStructs.h"
#include "KMIPAuthentication.h"
#include "KMIPMessageExtension.h"
#include "KMIPMessage.h"
#include "KMIPHeader.h"
#include "KMIPBatchItem.h"
#include "KMIPProtocolVersion.h"
#include "KMIPManagedObject.h"


KMIPFieldUP KMIPStructFactory::createField(int iTag) const {
    return createStructure(iTag);
}

KMIPStructUP KMIPStructFactory::createStructure(int iTag) const {
    KMIPStructUP upkst;
    switch(iTag) {
        case kmip::TagAttribute:
            upkst.reset(new KMIPAttribute());
            break;
        case kmip::TagName:
            upkst.reset(new KMIPName());
            break;
        case kmip::TagCryptographicParameters:
            upkst.reset(new KMIPCryptographicParameters());
            break;
        case kmip::TagCryptographicDomainParameters:
            upkst.reset(new KMIPCryptographicDomainParameters());
            break;
        case kmip::TagX509CertificateIdentifier:
            upkst.reset(new KMIPX509CertificateIdentifier());
            break;
        case kmip::TagX509CertificateSubject:
            upkst.reset(new KMIPX509CertificateSubject());
            break;
        case kmip::TagX509CertificateIssuer:
            upkst.reset(new KMIPX509CertificateIssuer());
            break;
        case kmip::TagCertificateIdentifier:
            upkst.reset(new KMIPCertificateIdentifier());
            break;
        case kmip::TagCertificateSubject:
            upkst.reset(new KMIPCertificateSubject());
            break;
        case kmip::TagCertificateIssuer:
            upkst.reset(new KMIPCertificateIssuer());
            break;
        case kmip::TagDigest:
            upkst.reset(new KMIPDigest());
            break;
        case kmip::TagUsageLimits:
            upkst.reset(new KMIPUsageLimits());
            break;
        case kmip::TagLink:
            upkst.reset(new KMIPLink());
            break;
        case kmip::TagApplicationSpecificInformation:
            upkst.reset(new KMIPApplicationSpecificInformation());
            break;
        case kmip::TagAlternativeName:
            upkst.reset(new KMIPAlternativeName());
            break;
        case kmip::TagKeyValueLocation:
            upkst.reset(new KMIPKeyValueLocation());
            break;
        case kmip::TagProtocolVersion:
            upkst.reset(new KMIPProtocolVersion());
            break;
        case kmip::TagAuthentication:
            upkst.reset(new KMIPAuthentication());
            break;
        case kmip::TagMessageExtension:
            upkst.reset(new KMIPMessageExtension());
            break;
        case kmip::TagRequestMessage:
            upkst.reset(new KMIPRequestMessage());
            break;
        case kmip::TagResponseMessage:
            upkst.reset(new KMIPResponseMessage());
            break;
        case kmip::TagRequestHeader:
            upkst.reset(new KMIPRequestHeader());
            break;
        case kmip::TagResponseHeader:
            upkst.reset(new KMIPResponseHeader());
            break;
        case kmip::TagBatchItem:
            upkst.reset(new KMIPBatchItem());
            break;
        case kmip::TagCertificate:
        case kmip::TagSymmetricKey:
        case kmip::TagPublicKey:
        case kmip::TagPrivateKey:
        case kmip::TagSplitKey:
        case kmip::TagTemplate:
        case kmip::TagSecretData:
        case kmip::TagOpaqueObject:
        case kmip::TagPGPKey:
            upkst = kmof.createObject(iTag);
            break;
        default:
            upkst.reset(new KMIPStruct(iTag));
            break;
    }

    return upkst;
}

