/* Copyright (C) 2017 Alexander Downey */
#include "KMIPAttributeRule.h"


KMIPAttributeRule::KMIPAttributeRule() {}
bool KMIPAttributeRule::getTFRule(Rule eRule) const {
    return (eRule > RuleUnknown && eRule < RuleEnd) ? bsTFRules[eRule] : false;
}

bool KMIPAttributeRule::isRequired() const {
    return getTFRule(RuleShallHaveValue);
}

bool KMIPAttributeRule::canServerSet() const {
    return getTFRule(RuleServerSet);
}

bool KMIPAttributeRule::canClientSet() const {
    return getTFRule(RuleClientSet);
}

bool KMIPAttributeRule::canServerModify() const {
    return getTFRule(RuleServerModify);
}

bool KMIPAttributeRule::canClientModify() const {
    return getTFRule(RuleClientModify);
}

bool KMIPAttributeRule::canClientDelete() const {
    return getTFRule(RuleClientDelete);
}

bool KMIPAttributeRule::isMultiInstance() const {
    return getTFRule(RuleMultiInstance);
}

bool KMIPAttributeRule::isSetByOperation(int iOp) const {
    return (iOp >= 0 && iOp < bsOps.size()) ? bsOps[iOp] : false;
}

bool KMIPAttributeRule::appliesToObject(int iObj) const {
    return (iObj >= 0 && iObj < bsObjs.size()) ? bsObjs[iObj] : false;
}

bool KMIPAttributeRule::isAttributeAddable(int iIndex, int iObjectType, int iOperation, bool bServer) {
    return (iIndex == 0 || iIndex > 0 && isMultiInstance())
        && (appliesToObject(iObjectType))
        && (isSetByOperation(iOperation) || iOperation == KMIPOperation::AddAttribute)
        && (bServer ? canServerSet() : canClientSet());
}

bool KMIPAttributeRule::isAttributeModifiable(int iIndex, int iObjectType, int iOperation, bool bServer) {
    return (iIndex == 0 || iIndex > 0 && isMultiInstance())
        && (appliesToObject(iObjectType))
        && (isSetByOperation(iOperation) || iOperation == KMIPOperation::ModifyAttribute)
        && (bServer ? canServerModify() : canClientModify());
}

bool KMIPAttributeRule::isAttributeDeletable(int iIndex, int iObjectType, int iOperation, bool bServer) {
    return (iIndex == 0 || iIndex > 0 && isMultiInstance())
        && (appliesToObject(iObjectType))
        && (isSetByOperation(iOperation) || iOperation == KMIPOperation::DeleteAttribute)
        && (bServer || canClientDelete());
}

constexpr int KMIPAttributeRule::getCryptoSet() {
    return ObjCrypto;
}

constexpr int KMIPAttributeRule::getCompleteSet() {
    return ObjAll;
}

constexpr int KMIPAttributeRule::getKeySet() {
    return ObjKeys;
}
constexpr int KMIPAttributeRule::getCertSet() {
    return ObjCerts;
}

KMIPUniqueIdentifierRule::KMIPUniqueIdentifierRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPNameRule::KMIPNameRule() {
    bsObjs = ObjAll;
    bsOps = OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFClientAll | TFServerModify | TFMultiInstance;
}

KMIPObjectTypeRule::KMIPObjectTypeRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCryptographicAlgorithmRule::KMIPCryptographicAlgorithmRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCryptographicLengthRule::KMIPCryptographicLengthRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCryptographicParametersRule::KMIPCryptographicParametersRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFClientAll | TFMultiInstance;
}

KMIPCryptographicDomainParametersRule::KMIPCryptographicDomainParametersRule() {
    bsObjs = ObjAsymmetricKeys | ObjTemplate;
    bsOps = OpReKey | OpReKeyKeyPair;
    bsTFRules = TFClientAll | TFMultiInstance;
}

KMIPCertificateTypeRule::KMIPCertificateTypeRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCertificateLengthRule::KMIPCertificateLengthRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPX509CertificateIdentifierRule::KMIPX509CertificateIdentifierRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPX509CertificateSubjectRule::KMIPX509CertificateSubjectRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPX509CertificateIssuerRule::KMIPX509CertificateIssuerRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCertificateIdentifierRule::KMIPCertificateIdentifierRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCertificateSubjectRule::KMIPCertificateSubjectRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPCertificateIssuerRule::KMIPCertificateIssuerRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet;
}

KMIPDigitalSignatureAlgorithmRule::KMIPDigitalSignatureAlgorithmRule() {
    bsObjs = ObjCerts;
    bsOps = OpRegister | OpCertify | OpReCertify;
    bsTFRules = TFShallHaveValue | TFServerSet | TFMultiInstance;
}

KMIPDigestRule::KMIPDigestRule() {
    bsObjs = ObjCrypto | ObjOpaqueObject;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerSet | TFMultiInstance;
}

KMIPOperationPolicyNameRule::KMIPOperationPolicyNameRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientSet;
}

KMIPCryptographicUsageMaskRule::KMIPCryptographicUsageMaskRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFShallHaveValue | TFServerAll | TFClientSet;
}

KMIPLeaseTimeRule::KMIPLeaseTimeRule() {
    bsObjs = ObjCrypto;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll;
}

KMIPUsageLimitsRule::KMIPUsageLimitsRule() {
    bsObjs = ObjKeys | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpReKey | OpReKeyKeyPair | OpGetUsageAllocation;
    bsTFRules = TFServerAll | TFClientAll;
}

KMIPStateRule::KMIPStateRule() {
    bsObjs = ObjCrypto;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll;
}

KMIPInitialDateRule::KMIPInitialDateRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll;
}

KMIPActivationDateRule::KMIPActivationDateRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpActivate | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientSet | TFClientModify;
}

KMIPProcessStartDateRule::KMIPProcessStartDateRule() {
    bsObjs = ObjSymmetricKey | ObjSplitKey | ObjTemplate;
    bsOps = OpCreate | OpRegister | OpDeriveKey | OpReKey;
    bsTFRules = TFServerAll | TFClientSet | TFClientModify;
}

KMIPProtectStopDateRule::KMIPProtectStopDateRule() {
    bsObjs = ObjSymmetricKey | ObjSplitKey | ObjTemplate;
    bsOps = OpCreate | OpRegister | OpDeriveKey | OpReKey;
    bsTFRules = TFServerAll | TFClientSet | TFClientModify;
}

KMIPDeactivationDateRule::KMIPDeactivationDateRule() {
    bsObjs = ObjCrypto | ObjTemplate;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpRevoke | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientSet | TFClientModify;
}

KMIPDestroyDateRule::KMIPDestroyDateRule() {
    bsObjs = ObjCrypto | ObjOpaqueObject;
    bsOps = OpDestroy;
    bsTFRules = TFServerSet;
}

KMIPCompromiseOccurrenceDateRule::KMIPCompromiseOccurrenceDateRule() {
    bsObjs = ObjCrypto | ObjOpaqueObject;
    bsOps = OpRevoke;
    bsTFRules = TFServerSet;
}

KMIPCompromiseDateRule::KMIPCompromiseDateRule() {
    bsObjs = ObjCrypto | ObjOpaqueObject;
    bsOps = OpRevoke;
    bsTFRules = TFServerSet;
}

KMIPRevocationReasonRule::KMIPRevocationReasonRule() {
    bsObjs = ObjCrypto | ObjOpaqueObject;
    bsOps = OpRevoke;
    bsTFRules = TFServerSet;
}

KMIPArchiveDateRule::KMIPArchiveDateRule() {
    bsObjs = ObjAll;
    bsOps = OpArchive;
    bsTFRules = TFServerSet;
}

KMIPObjectGroupRule::KMIPObjectGroupRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpRevoke | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientAll | TFMultiInstance;
}

KMIPFreshRule::KMIPFreshRule() {
    bsObjs = ObjCrypto;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpRevoke | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientSet;
}

KMIPLinkRule::KMIPLinkRule() {
    bsObjs = ObjCrypto;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpRevoke | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientSet | TFMultiInstance;
}

KMIPApplicationSpecificInformationRule::KMIPApplicationSpecificInformationRule() {
    bsObjs = ObjAll;
    bsOps = OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientAll | TFMultiInstance;
}

KMIPContactInformationRule::KMIPContactInformationRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpRegister | OpDeriveKey | OpRevoke | OpCertify | OpReCertify | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerAll | TFClientAll;
}

KMIPLastChangeDateRule::KMIPLastChangeDateRule() {
    bsObjs = ObjAll;
    bsOps = OpAddObject | OpAttributes | OpActivate | OpRevoke | OpDestroy | OpArchive | OpRecover | OpGetUsageAllocation;
    bsTFRules = TFShallHaveValue | TFServerAll;
}

KMIPCustomAttributeRule::KMIPCustomAttributeRule() {
    bsObjs = ObjAll;
    bsOps = OpAddObject;
    bsTFRules = TFServerAll | TFClientAll | TFMultiInstance;
}

KMIPAlternativeNameRule::KMIPAlternativeNameRule() {
    bsObjs = ObjAll;
    bsOps = OpNone;
    bsTFRules = TFServerAll | TFClientAll | TFMultiInstance;
}

KMIPKeyValuePresentRule::KMIPKeyValuePresentRule() {
    bsObjs = ObjPrivateData;
    bsOps = OpRegister;
    bsTFRules = TFServerSet;
}

KMIPKeyValueLocationRule::KMIPKeyValueLocationRule() {
    bsObjs = ObjPrivateData;
    bsOps = OpNone;
    bsTFRules = TFClientAll;
}

KMIPOriginalCreationDateRule::KMIPOriginalCreationDateRule() {
    bsObjs = ObjAll;
    bsOps = OpCreate | OpCreateKeyPair | OpDeriveKey | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFServerSet | TFClientSet;
}

KMIPRandomNumberGeneratorRule::KMIPRandomNumberGeneratorRule() {
    bsObjs = ObjCrypto;
    bsOps = OpCreate | OpCreateKeyPair | OpDeriveKey | OpReKey | OpReKeyKeyPair;
    bsTFRules = TFClientSet;
}

KMIPPKCS_12FriendlyNameRule::KMIPPKCS_12FriendlyNameRule() {
    bsObjs = ObjCrypto;
    bsOps = OpNone;
    bsTFRules = TFServerSet | TFClientAll;
}

KMIPDescriptionRule::KMIPDescriptionRule() {
    bsObjs = ObjAll;
    bsOps = OpNone;
    bsTFRules = TFServerAll | TFClientAll;
}

KMIPCommentRule::KMIPCommentRule() {
    bsObjs = ObjAll;
    bsOps = OpNone;
    bsTFRules = TFServerAll | TFClientAll;
}

KMIPSensitiveRule::KMIPSensitiveRule() {
    bsObjs = ObjAll;
    bsOps = OpAddObject;
    bsTFRules = TFShallHaveValue | TFServerAll | TFClientSet;
}

KMIPAlwaysSensitiveRule::KMIPAlwaysSensitiveRule() {
    bsObjs = ObjAll;
    bsOps = OpNone;
    bsTFRules = TFShallHaveValue | TFServerAll;
}

KMIPExtractableRule::KMIPExtractableRule() {
    bsObjs = ObjAll;
    bsOps = OpAddObject;
    bsTFRules = TFShallHaveValue | TFServerAll | TFClientSet | TFClientModify;
}

KMIPNeverExtractableRule::KMIPNeverExtractableRule() {
    bsObjs = ObjAll;
    bsOps = OpNone;
    bsTFRules = TFShallHaveValue | TFServerAll;
}
