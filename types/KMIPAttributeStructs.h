/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTESTRUCTS_H
#define _KMIPATTRIBUTESTRUCTS_H

#include "KMIPStruct.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"

class KMIPName : public KMIPStruct {
    public:
        KMIPName();
        KMIPName(uint32_t iNameType, const std::string &sValue);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, NameType);
        DECLARE_GET_SET_FIELD_VALUE(std::string, NameValue);
};

class KMIPCryptographicParameters : public KMIPStruct {
    public:
        KMIPCryptographicParameters();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, BlockCipherMode);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, PaddingMethod);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, HashingAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, KeyRoleType);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, DigitalSignatureAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, CryptographicAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(bool, RandomIV);
        DECLARE_GET_SET_FIELD_VALUE(int, IVLength);
        DECLARE_GET_SET_FIELD_VALUE(int, TagLength);
        DECLARE_GET_SET_FIELD_VALUE(int, FixedFieldLength);
        DECLARE_GET_SET_FIELD_VALUE(int, InvocationFieldLength);
        DECLARE_GET_SET_FIELD_VALUE(int, CounterLength);
        DECLARE_GET_SET_FIELD_VALUE(int, InitialCounterValue);
        DECLARE_GET_SET_FIELD_VALUE(int, SaltLength);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, MaskGenerator);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, MaskGeneratorHashingAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PSource);
        DECLARE_GET_SET_FIELD_VALUE(int, TrailerField);
};

class KMIPCryptographicDomainParameters : public KMIPStruct {
    public:
        KMIPCryptographicDomainParameters();
        DECLARE_GET_SET_FIELD_VALUE(int, Qlength);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, RecommendedCurve);
};

class KMIPX509CertificateIdentifier : public KMIPStruct {
    public:
        KMIPX509CertificateIdentifier();
        DECLARE_GET_SET_FIELD_VALUE(std::string, IssuerDistinguishedName);
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateSerialNumber);
};

class KMIPX509CertificateSubject : public KMIPStruct {
    public:
        KMIPX509CertificateSubject();
        DECLARE_GET_SET_FIELD_VALUE(std::string, SubjectDistinguishedName);
        DECLARE_GET_SET_FIELD_VALUE(std::string, SubjectAlternativeName);
};

class KMIPX509CertificateIssuer : public KMIPStruct {
    public:
        KMIPX509CertificateIssuer();
        DECLARE_GET_SET_FIELD_VALUE(std::string, IssuerDistinguishedName);
        DECLARE_GET_SET_FIELD_VALUE(std::string, IssuerAlternativeName);
};

class KMIPCertificateIdentifier : public KMIPStruct {
    public:
        KMIPCertificateIdentifier();
        DECLARE_GET_SET_FIELD_VALUE(std::string, Issuer);
        DECLARE_GET_SET_FIELD_VALUE(std::string, SerialNumber);
};

class KMIPCertificateSubject : public KMIPStruct {
    public:
        KMIPCertificateSubject();
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateSubjectDistinguishedName);
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateSubjectAlternativeName);
};

class KMIPCertificateIssuer : public KMIPStruct {
    public:
        KMIPCertificateIssuer();
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateIssuerDistinguishedName);
        DECLARE_GET_SET_FIELD_VALUE(std::string, CertificateIssuerAlternativeName);
};

class KMIPDigest : public KMIPStruct {
    public:
        KMIPDigest();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, HashingAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(std::string, DigestValue);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, KeyFormatType);
};

class KMIPUsageLimits : public KMIPStruct {
    public:
        KMIPUsageLimits();
        DECLARE_GET_SET_FIELD_VALUE(long int, UsageLimitsTotal);
        DECLARE_GET_SET_FIELD_VALUE(long int, UsageLimitsCount);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, UsageLimitsUnit);
};

class KMIPLink : public KMIPStruct {
    public:
        KMIPLink();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, LinkType);
        DECLARE_GET_SET_FIELD_VALUE(std::string, LinkedObjectIdentifier);
};

class KMIPApplicationSpecificInformation : public KMIPStruct {
    public:
        KMIPApplicationSpecificInformation();
        DECLARE_GET_SET_FIELD_VALUE(std::string, ApplicationNamespace);
        DECLARE_GET_SET_FIELD_VALUE(std::string, ApplicationData);
};

class KMIPAlternativeName : public KMIPStruct {
    public:
        KMIPAlternativeName();
        DECLARE_GET_SET_FIELD_VALUE(std::string, AlternativeNameValue);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, AlternativeNameType);
};

class KMIPKeyValueLocation : public KMIPStruct {
    public:
        KMIPKeyValueLocation();
        DECLARE_GET_SET_FIELD_VALUE(std::string, KeyValueLocationValue);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, KeyValueLocationType);
};


#endif
