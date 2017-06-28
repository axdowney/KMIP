/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPCERTIFICATE_H
#define _KMIPCERTIFICATE_H

#include "KMIPManagedObject.h"

class KMIPCertificate : public KMIPManagedObject {
    public:
        KMIPCertificate();
        virtual int getObjectType() const;
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, CertificateType);
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateValue);
};

#endif
