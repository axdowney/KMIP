/* Copyright (C) 2017 Alexander Downey */
#include "KMIPAttributeStructs.h"
#include "KMIPNumber.h"
#include "KMIPEnumeration.h"
#include "KMIPString.h"
KMIPName::KMIPName() : KMIPStruct(kmip::TagName) {}
KMIPName::KMIPName(uint32_t iNameType, const std::string &sValue) : KMIPStruct(kmip::TagName) {
    setNameType(iNameType);
    setNameValue(sValue);
}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPName, Enumeration, uint32_t, NameType, kmip::TagNameType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPName, TextString, std::string, NameValue, kmip::TagNameValue);


KMIPCryptographicParameters::KMIPCryptographicParameters() : KMIPStruct(kmip::TagCryptographicParameters) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, BlockCipherMode, kmip::TagBlockCipherMode);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, PaddingMethod, kmip::TagPaddingMethod);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, HashingAlgorithm, kmip::TagHashingAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, KeyRoleType, kmip::TagKeyRoleType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, DigitalSignatureAlgorithm, kmip::TagDigitalSignatureAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, CryptographicAlgorithm, kmip::TagCryptographicAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Boolean, bool, RandomIV, kmip::TagRandomIV);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, IVLength, kmip::TagIVLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, TagLength, kmip::TagTagLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, FixedFieldLength, kmip::TagFixedFieldLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, InvocationFieldLength, kmip::TagInvocationFieldLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, CounterLength, kmip::TagCounterLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, InitialCounterValue, kmip::TagInitialCounterValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, SaltLength, kmip::TagSaltLength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, MaskGenerator, kmip::TagMaskGenerator);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Enumeration, uint32_t, MaskGeneratorHashingAlgorithm, kmip::TagMaskGeneratorHashingAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, ByteString, std::string, PSource, kmip::TagPSource);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicParameters, Integer, int, TrailerField, kmip::TagTrailerField);


KMIPCryptographicDomainParameters::KMIPCryptographicDomainParameters() : KMIPStruct(kmip::TagCryptographicDomainParameters) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicDomainParameters, Integer, int, Qlength, kmip::TagQlength);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCryptographicDomainParameters, Enumeration, uint32_t, RecommendedCurve, kmip::TagRecommendedCurve);


KMIPX509CertificateIdentifier::KMIPX509CertificateIdentifier() : KMIPStruct(kmip::TagX509CertificateIssuer) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateIdentifier, ByteString, std::string, IssuerDistinguishedName, kmip::TagIssuerDistinguishedName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateIdentifier, ByteString, std::string, CertificateSerialNumber, kmip::TagCertificateSerialNumber);

KMIPX509CertificateSubject::KMIPX509CertificateSubject() : KMIPStruct(kmip::TagX509CertificateSubject) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateSubject, ByteString, std::string, SubjectDistinguishedName, kmip::TagSubjectDistinguishedName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateSubject, ByteString, std::string, SubjectAlternativeName, kmip::TagSubjectAlternativeName);

KMIPX509CertificateIssuer::KMIPX509CertificateIssuer() : KMIPStruct(kmip::TagX509CertificateIssuer) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateIssuer, ByteString, std::string, IssuerDistinguishedName, kmip::TagIssuerDistinguishedName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPX509CertificateIssuer, ByteString, std::string, IssuerAlternativeName, kmip::TagIssuerAlternativeName);

KMIPCertificateIdentifier::KMIPCertificateIdentifier() : KMIPStruct(kmip::TagCertificateIdentifier) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateIdentifier, TextString, std::string, Issuer, kmip::TagIssuer);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateIdentifier, TextString, std::string, SerialNumber, kmip::TagSerialNumber);

KMIPCertificateSubject::KMIPCertificateSubject() : KMIPStruct(kmip::TagCertificateSubject) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateSubject, TextString, std::string, CertificateSubjectDistinguishedName, kmip::TagCertificateSubjectDistinguishedName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateSubject, TextString, std::string, CertificateSubjectAlternativeName, kmip::TagCertificateSubjectAlternativeName);

KMIPCertificateIssuer::KMIPCertificateIssuer() : KMIPStruct(kmip::TagCertificateIssuer) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateIssuer, TextString, std::string, CertificateIssuerDistinguishedName, kmip::TagCertificateIssuerDistinguishedName);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPCertificateIssuer, TextString, std::string, CertificateIssuerAlternativeName, kmip::TagCertificateIssuerAlternativeName);


KMIPDigest::KMIPDigest() : KMIPStruct(kmip::TagDigest) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPDigest, Enumeration, uint32_t, HashingAlgorithm, kmip::TagHashingAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPDigest, ByteString, std::string, DigestValue, kmip::TagDigestValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPDigest, Enumeration, uint32_t, KeyFormatType, kmip::TagKeyFormatType);

KMIPUsageLimits::KMIPUsageLimits() : KMIPStruct(kmip::TagUsageLimits) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPUsageLimits, LongInteger, int64_t, UsageLimitsTotal, kmip::TagUsageLimitsTotal);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPUsageLimits, LongInteger, int64_t, UsageLimitsCount, kmip::TagUsageLimitsCount);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPUsageLimits, Enumeration, uint32_t, UsageLimitsUnit, kmip::TagUsageLimitsUnit);

KMIPLink::KMIPLink() : KMIPStruct(kmip::TagLink) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPLink, Enumeration, uint32_t, LinkType, kmip::TagLinkType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPLink, TextString, std::string, LinkedObjectIdentifier, kmip::TagLinkedObjectIdentifier);

KMIPApplicationSpecificInformation::KMIPApplicationSpecificInformation() : KMIPStruct(kmip::TagApplicationSpecificInformation) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPApplicationSpecificInformation, TextString, std::string, ApplicationNamespace, kmip::TagApplicationNamespace);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPApplicationSpecificInformation, TextString, std::string, ApplicationData, kmip::TagApplicationData);

KMIPAlternativeName::KMIPAlternativeName() : KMIPStruct(kmip::TagAlternativeName) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPAlternativeName, TextString, std::string, AlternativeNameValue, kmip::TagAlternativeNameValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPAlternativeName, Enumeration, uint32_t, AlternativeNameType, kmip::TagAlternativeNameType);

KMIPKeyValueLocation::KMIPKeyValueLocation() : KMIPStruct(kmip::TagKeyValueLocation) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyValueLocation, TextString, std::string, KeyValueLocationValue, kmip::TagKeyValueLocationValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyValueLocation, Enumeration, uint32_t, KeyValueLocationType, kmip::TagKeyValueLocationType);
