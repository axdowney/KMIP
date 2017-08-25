/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTERULE_H
#define _KMIPATTRIBUTERULE_H

#include <bitset>

#include "KMIPDefs.h"
#include "KMIPEnumeration.h"

class KMIPAttributeRule {
    public:
        enum Rule {
            RuleUnknown = -1,
            RuleShallHaveValue,
            RuleServerSet,
            RuleClientSet,
            RuleServerModify,
            RuleClientModify,
            RuleClientDelete,
            RuleMultiInstance,
            RuleEnd
        };

        enum RuleFlag {
            TFShallHaveValue = 1 << (RuleShallHaveValue),
            TFServerSet = 1 << (RuleServerSet),
            TFClientSet = 1 << (RuleClientSet),
            TFServerModify = 1 << (RuleServerModify),
            TFClientModify = 1 << (RuleClientModify),
            TFClientDelete = 1 << (RuleClientDelete),
            TFMultiInstance = 1 << (RuleMultiInstance),

            TFServerAll = TFServerSet | TFServerModify,
            TFClientAll = TFClientSet | TFClientModify | TFClientDelete,
            TFAll = TFShallHaveValue | TFServerAll | TFClientAll | TFMultiInstance,
            TFNone = 0,
        };

        enum ObjectFlag {
            ObjCertificate = 1 << (KMIPObjectType::Certificate - 1),
            ObjSymmetricKey = 1 << (KMIPObjectType::SymmetricKey - 1),
            ObjPublicKey = 1 << (KMIPObjectType::PublicKey - 1),
            ObjPrivateKey = 1 << (KMIPObjectType::PrivateKey - 1),
            ObjSplitKey = 1 << (KMIPObjectType::SplitKey - 1),
            ObjTemplate = 1 << (KMIPObjectType::Template - 1),
            ObjSecretData = 1 << (KMIPObjectType::SecretData - 1),
            ObjOpaqueObject = 1 << (KMIPObjectType::OpaqueObject - 1),
            ObjPGPKey = 1 << (KMIPObjectType::PGPKey - 1),

            ObjAll = ObjPGPKey | ObjOpaqueObject | ObjSecretData | ObjTemplate | ObjSplitKey | ObjPrivateKey
                | ObjPublicKey | ObjSymmetricKey | ObjCertificate,
//            ObjCrypto = ObjPGPKey | ObjSecretData | ObjSplitKey | ObjPrivateKey
//                | ObjPublicKey | ObjSymmetricKey | ObjCertificate,
            ObjKeys = ObjSplitKey | ObjPrivateKey | ObjPublicKey | ObjSymmetricKey,
            ObjCerts = ObjPGPKey | ObjCertificate,
            ObjCrypto = ObjKeys | ObjCerts | ObjSecretData,
            ObjAsymmetricKeys = ObjSplitKey | ObjPrivateKey | ObjPublicKey,
            ObjPrivateData = ObjSymmetricKey | ObjPrivateKey | ObjSplitKey | ObjSecretData,
        };

        enum OperationFlag : uint64_t {
            OpNone = 0,
            OpCreate = 1 << (KMIPOperation::Create - 1),
            OpCreateKeyPair = 1 << (KMIPOperation::CreateKeyPair - 1),
            OpRegister = 1 << (KMIPOperation::Register - 1),
            OpReKey = 1 << (KMIPOperation::ReKey - 1),
            OpDeriveKey = 1 << (KMIPOperation::DeriveKey - 1),
            OpCertify = 1 << (KMIPOperation::Certify - 1),
            OpReCertify = 1 << (KMIPOperation::ReCertify - 1),
            OpLocate = 1 << (KMIPOperation::Locate - 1),
            OpCheck = 1 << (KMIPOperation::Check - 1),
            OpGet = 1 << (KMIPOperation::Get - 1),
            OpGetAttributes = 1 << (KMIPOperation::GetAttributes - 1),
            OpGetAttributeList = 1 << (KMIPOperation::GetAttributeList - 1),
            OpAddAttribute = 1 << (KMIPOperation::AddAttribute - 1),
            OpModifyAttribute = 1 << (KMIPOperation::ModifyAttribute - 1),
            OpDeleteAttribute = 1 << (KMIPOperation::DeleteAttribute - 1),
            OpObtainLease = 1 << (KMIPOperation::ObtainLease - 1),
            OpGetUsageAllocation = 1 << (KMIPOperation::GetUsageAllocation - 1),
            OpActivate = 1 << (KMIPOperation::Activate - 1),
            OpRevoke = 1 << (KMIPOperation::Revoke - 1),
            OpDestroy = 1 << (KMIPOperation::Destroy - 1),
            OpArchive = 1 << (KMIPOperation::Archive - 1),
            OpRecover = 1 << (KMIPOperation::Recover - 1),
            OpValidate = 1 << (KMIPOperation::Validate - 1),
            OpQuery = 1 << (KMIPOperation::Query - 1),
            OpCancel = 1 << (KMIPOperation::Cancel - 1),
            OpPoll = 1 << (KMIPOperation::Poll - 1),
            OpNotify = 1 << (KMIPOperation::Notify - 1),
            OpPut = 1 << (KMIPOperation::Put - 1),
            OpReKeyKeyPair = 1 << (KMIPOperation::ReKeyKeyPair - 1),
            OpDiscoverVersions = 1 << (KMIPOperation::DiscoverVersions - 1),
            OpEncrypt = 1 << (KMIPOperation::Encrypt - 1),
            OpDecrypt = 1lu << (KMIPOperation::Decrypt - 1),
            OpSign = 1lu << (KMIPOperation::Sign - 1),
            OpSignatureVerify = 1lu << (KMIPOperation::SignatureVerify - 1),
            OpMAC = 1lu << (KMIPOperation::MAC - 1),
            OpMACVerify = 1lu << (KMIPOperation::MACVerify - 1),
            OpRNGRetrieve = 1lu << (KMIPOperation::RNGRetrieve - 1),
            OpRNGSeed = 1lu << (KMIPOperation::RNGSeed - 1),
            OpHash = 1lu << (KMIPOperation::Hash - 1),
            OpCreateSplitKey = 1lu << (KMIPOperation::CreateSplitKey - 1),
            OpJoinSplitKey = 1lu << (KMIPOperation::JoinSplitKey - 1),
            OpImport = 1lu << (KMIPOperation::Import - 1),
            OpExport = 1lu << (KMIPOperation::Export - 1),

            OpCreateSymmetricKey = OpCreate | OpRegister | OpDeriveKey,
            OpCreateAsymmetricKey = OpCreateKeyPair | OpRegister,
            OpCopyObject = OpReKey | OpReCertify | OpReKeyKeyPair,
            OpAttributes = OpAddAttribute | OpModifyAttribute | OpDeleteAttribute,
            OpCreateObject = OpCreateSymmetricKey | OpCreateAsymmetricKey | OpCertify,
            OpAddObject = OpCreateObject | OpCopyObject,
        };

        KMIPAttributeRule();
        bool getTFRule(Rule eRule) const;
        bool isRequired() const;
        bool canServerSet() const;
        bool canClientSet() const;
        bool canServerModify() const;
        bool canClientModify() const;
        bool canClientDelete() const;
        bool isMultiInstance() const;
        bool isSetByOperation(int iOp) const;
        bool appliesToObject(int iObj) const;

        bool isAttributeAddable(int iIndex, int iObjectType, int iOperation, bool bServer);
        bool isAttributeModifiable(int iIndex, int iObjectType, int iOperation, bool bServer);
        bool isAttributeDeletable(int iIndex, int iObjectType, int iOperation, bool bServer);

        static constexpr int getCryptoSet();
        static constexpr int getCompleteSet();
        static constexpr int getKeySet();
        static constexpr int getCertSet();

    protected:
        std::bitset<RuleEnd> bsTFRules;
        std::bitset<kmip::kiNumOperations> bsOps;
        std::bitset<kmip::kiNumObjects> bsObjs;
};

class KMIPUniqueIdentifierRule : public KMIPAttributeRule {
    public:
        KMIPUniqueIdentifierRule();
};

class KMIPNameRule : public KMIPAttributeRule {
    public:
        KMIPNameRule();
};

class KMIPObjectTypeRule : public KMIPAttributeRule {
    public:
        KMIPObjectTypeRule();
};

class KMIPCryptographicAlgorithmRule : public KMIPAttributeRule {
    public:
        KMIPCryptographicAlgorithmRule();
};

class KMIPCryptographicLengthRule : public KMIPAttributeRule {
    public:
        KMIPCryptographicLengthRule();
};

class KMIPCryptographicParametersRule : public KMIPAttributeRule {
    public:
        KMIPCryptographicParametersRule();
};

class KMIPCryptographicDomainParametersRule : public KMIPAttributeRule {
    public:
        KMIPCryptographicDomainParametersRule();
};

class KMIPCertificateTypeRule : public KMIPAttributeRule {
    public:
        KMIPCertificateTypeRule();
};

class KMIPCertificateLengthRule : public KMIPAttributeRule {
    public:
        KMIPCertificateLengthRule();
};

class KMIPX509CertificateIdentifierRule : public KMIPAttributeRule {
    public:
        KMIPX509CertificateIdentifierRule();
};

class KMIPX509CertificateSubjectRule : public KMIPAttributeRule {
    public:
        KMIPX509CertificateSubjectRule();
};

class KMIPX509CertificateIssuerRule : public KMIPAttributeRule {
    public:
        KMIPX509CertificateIssuerRule();
};

class KMIPCertificateIdentifierRule : public KMIPAttributeRule {
    public:
        KMIPCertificateIdentifierRule();
};

class KMIPCertificateSubjectRule : public KMIPAttributeRule {
    public:
        KMIPCertificateSubjectRule();
};

class KMIPCertificateIssuerRule : public KMIPAttributeRule {
    public:
        KMIPCertificateIssuerRule();
};

class KMIPDigitalSignatureAlgorithmRule : public KMIPAttributeRule {
    public:
        KMIPDigitalSignatureAlgorithmRule();
};

class KMIPDigestRule : public KMIPAttributeRule {
    public:
        KMIPDigestRule();
};

class KMIPOperationPolicyNameRule : public KMIPAttributeRule {
    public:
        KMIPOperationPolicyNameRule();
};

class KMIPCryptographicUsageMaskRule : public KMIPAttributeRule {
    public:
        KMIPCryptographicUsageMaskRule();
};

class KMIPLeaseTimeRule : public KMIPAttributeRule {
    public:
        KMIPLeaseTimeRule();
};

class KMIPUsageLimitsRule : public KMIPAttributeRule {
    public:
        KMIPUsageLimitsRule();
};

class KMIPStateRule : public KMIPAttributeRule {
    public:
        KMIPStateRule();
};

class KMIPInitialDateRule : public KMIPAttributeRule {
    public:
        KMIPInitialDateRule();
};

class KMIPActivationDateRule : public KMIPAttributeRule {
    public:
        KMIPActivationDateRule();
};

class KMIPProcessStartDateRule : public KMIPAttributeRule {
    public:
        KMIPProcessStartDateRule();
};

class KMIPProtectStopDateRule : public KMIPAttributeRule {
    public:
        KMIPProtectStopDateRule();
};

class KMIPDeactivationDateRule : public KMIPAttributeRule {
    public:
        KMIPDeactivationDateRule();
};

class KMIPDestroyDateRule : public KMIPAttributeRule {
    public:
        KMIPDestroyDateRule();
};

class KMIPCompromiseOccurrenceDateRule : public KMIPAttributeRule {
    public:
        KMIPCompromiseOccurrenceDateRule();
};

class KMIPCompromiseDateRule : public KMIPAttributeRule {
    public:
        KMIPCompromiseDateRule();
};

class KMIPRevocationReasonRule : public KMIPAttributeRule {
    public:
        KMIPRevocationReasonRule();
};

class KMIPArchiveDateRule : public KMIPAttributeRule {
    public:
        KMIPArchiveDateRule();
};

class KMIPObjectGroupRule : public KMIPAttributeRule {
    public:
        KMIPObjectGroupRule();
};

class KMIPFreshRule : public KMIPAttributeRule {
    public:
        KMIPFreshRule();
};

class KMIPLinkRule : public KMIPAttributeRule {
    public:
        KMIPLinkRule();
};

class KMIPApplicationSpecificInformationRule : public KMIPAttributeRule {
    public:
        KMIPApplicationSpecificInformationRule();
};

class KMIPContactInformationRule : public KMIPAttributeRule {
    public:
        KMIPContactInformationRule();
};

class KMIPLastChangeDateRule : public KMIPAttributeRule {
    public:
        KMIPLastChangeDateRule();
};

class KMIPCustomAttributeRule : public KMIPAttributeRule {
    public:
        KMIPCustomAttributeRule();
};

class KMIPAlternativeNameRule : public KMIPAttributeRule {
    public:
        KMIPAlternativeNameRule();
};

class KMIPKeyValuePresentRule : public KMIPAttributeRule {
    public:
        KMIPKeyValuePresentRule();
};

class KMIPKeyValueLocationRule : public KMIPAttributeRule {
    public:
        KMIPKeyValueLocationRule();
};

class KMIPOriginalCreationDateRule : public KMIPAttributeRule {
    public:
        KMIPOriginalCreationDateRule();
};

class KMIPRandomNumberGeneratorRule : public KMIPAttributeRule {
    public:
        KMIPRandomNumberGeneratorRule();
};

class KMIPPKCS_12FriendlyNameRule : public KMIPAttributeRule {
    public:
        KMIPPKCS_12FriendlyNameRule();
};

class KMIPDescriptionRule : public KMIPAttributeRule {
    public:
        KMIPDescriptionRule();
};

class KMIPCommentRule : public KMIPAttributeRule {
    public:
        KMIPCommentRule();
};

class KMIPSensitiveRule : public KMIPAttributeRule {
    public:
        KMIPSensitiveRule();
};

class KMIPAlwaysSensitiveRule : public KMIPAttributeRule {
    public:
        KMIPAlwaysSensitiveRule();
};

class KMIPExtractableRule : public KMIPAttributeRule {
    public:
        KMIPExtractableRule();
};

class KMIPNeverExtractableRule : public KMIPAttributeRule {
    public:
        KMIPNeverExtractableRule();
};
#endif

