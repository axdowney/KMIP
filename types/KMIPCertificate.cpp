/* Copyright (C) 2017 Alexander Downey */
#include "KMIPCertificate.h"
#include "KMIPDefs.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"

KMIPCertificate::KMIPCertificate() : KMIPStruct(kmip::TagCertificate) {}
int KMIPCertificate::getObjectType() const {
    return KMIPObjectType::Certificate;
}

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificate, Enumeration, uint32_t, CertificateType, kmip::TagCertificateType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificate, ByteString, std::string, CertificateValue, kmip::TagCertificateValue);
