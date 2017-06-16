/* Copyright (C) 2017 Alexander Downey */
#include "KMIPAttribute.h"
#include "KMIPString.h"
#include "KMIPNumber.h"
#include "KMIPDefs.h"


KMIPAttribute::KMIPAttribute() : KMIPStruct(kmip::TagAttribute) {}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldUP upkfValue) : KMIPAttribute(sName, iIndex, upkfValue.release()) {
}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPField *pkfValue) : KMIPAttribute(sName, iIndex, KMIPFieldSP(pkfValue)) {
}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldSP spkfValue) : KMIPStruct(kmip::TagAttribute) {
    setName(sName);
    setIndex(iIndex);
    setValue(spkfValue);
}

std::string KMIPAttribute::getName() const {
    return getChildValue<KMIPTextString>(kmip::TagAttributeName, std::string());
}

bool KMIPAttribute::setName(const std::string &sNewName) {
    return setOrderedTextString(kmip::TagAttributeName, sNewName);
}

int KMIPAttribute::getIndex() const {
    return getChildValue<KMIPInteger>(kmip::TagAttributeIndex, 0);
}

bool KMIPAttribute::setIndex(int iNewIndex) {
    return setOrderedInteger(kmip::TagAttributeIndex, iNewIndex);
}

KMIPFieldSP KMIPAttribute::getValue() {
    return getChild<KMIPField>(kmip::TagAttributeValue);
}

KMIPFieldSPK KMIPAttribute::getValue() const {
    return getChild<KMIPField>(kmip::TagAttributeValue);
}

bool KMIPAttribute::setValue(KMIPFieldSP spkfValue) {
    spkfValue->forceAttributeValue(true);
    return addOrderedField(spkfValue);
}

int KMIPAttribute::getNameTag(const std::string &sName) {
    auto mapIter = mapNameToTag.find(sName);
    return mapIter == mapNameToTag.end() ? kmip::TagCustomAttribute : mapIter->second;
}

int KMIPAttribute::getNameTag() const {
    return getNameTag(getName());
}

std::string KMIPAttribute::getNameFromTag(int iTag) {
    std::string sRet = "";
    for (auto mapIter : mapNameToTag) {
        if (mapIter.second == iTag) {
            sRet = mapIter.first;
            break;
        }
    }

    return sRet;
}

std::shared_ptr<KMIPAttributeRule> KMIPAttribute::getRuleFromName(const std::string &sName) {
    return KMIPUtils::getAttributeRule(getNameTag(sName));
}

std::shared_ptr<KMIPAttributeRule> KMIPAttribute::getRuleFromName() const {
    return getRuleFromName(getName()); 
}

const std::map<std::string, int> KMIPAttribute::mapNameToTag {
    {"Unique Identifier", kmip::TagUniqueIdentifier},
    {"Name", kmip::TagName},
    {"Object Type", kmip::TagObjectType},
    {"Cryptographic Algorithm", kmip::TagCryptographicAlgorithm},
    {"Cryptographic Length", kmip::TagCryptographicLength},
    {"Cryptographic Parameters", kmip::TagCryptographicParameters},
    {"Cryptographic Domain Parameters", kmip::TagCryptographicDomainParameters},
    {"Certificate Type", kmip::TagCertificateType},
    {"Certificate Length", kmip::TagCertificateLength},
    {"X.509 Certificate Identifier", kmip::TagX509CertificateIdentifier},
    {"X.509 Certificate Subject", kmip::TagX509CertificateSubject},
    {"X.509 Certificate Issuer", kmip::TagX509CertificateIssuer},
    {"Certificate Identifier", kmip::TagCertificateIdentifier},
    {"Certificate Subject", kmip::TagCertificateSubject},
    {"Certificate Issuer", kmip::TagCertificateIssuer},
    {"Digital Signature Algorithm", kmip::TagDigitalSignatureAlgorithm},
    {"Digest", kmip::TagDigest},
    {"Operation Policy Name", kmip::TagOperationPolicyName},
    {"Cryptographic Usage Mask", kmip::TagCryptographicUsageMask},
    {"Lease Time", kmip::TagLeaseTime},
    {"Usage Limits", kmip::TagUsageLimits},
    {"State", kmip::TagState},
    {"Initial Date", kmip::TagInitialDate},
    {"Activation Date", kmip::TagActivationDate},
    {"Process Start Date", kmip::TagProcessStartDate},
    {"Protect Stop Date", kmip::TagProtectStopDate},
    {"Deactivation Date", kmip::TagDeactivationDate},
    {"Destroy Date", kmip::TagDestroyDate},
    {"Compromise Occurrence Date", kmip::TagCompromiseOccurrenceDate},
    {"Compromise Date", kmip::TagCompromiseDate},
    {"Revocation Reason", kmip::TagRevocationReason},
    {"Archive Date", kmip::TagArchiveDate},
    {"Object Group", kmip::TagObjectGroup},
    {"Fresh", kmip::TagFresh},
    {"Link", kmip::TagLink},
    {"Application Specific Information", kmip::TagApplicationSpecificInformation},
    {"Contact Information", kmip::TagContactInformation},
    {"Last Change Date", kmip::TagLastChangeDate},
    {"Custom Attribute", kmip::TagCustomAttribute},
    {"Alternative Name", kmip::TagAlternativeName},
    {"Key Value Present", kmip::TagKeyValuePresent},
    {"Key Value Location", kmip::TagKeyValueLocation},
    {"Original Creation Date", kmip::TagOriginalCreationDate},
    {"Random Number Generator", kmip::TagRandomNumberGenerator},
    {"PKCS#12 Friendly Name", kmip::TagPKCS_12FriendlyName},
    {"Description", kmip::TagDescription},
    {"Comment", kmip::TagComment},
    {"Sensitive", kmip::TagSensitive},
    {"Always Sensitive", kmip::TagAlwaysSensitive},
    {"Extractable", kmip::TagExtractable},
    {"Never Extractable", kmip::TagNeverExtractable}
};
