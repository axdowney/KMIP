#include "KMIPUtils.h"
#include "KMIPStruct.h"
#include "KMIPNumber.h"
#include "KMIPEnumeration.h"
#include "KMIPString.h"
#include "KMIPDateTime.h"
#include "KMIPFactory.h"
#include "KMIPEnumFactory.h"
#include "KMIPStructFactory.h"
#include "KMIPFieldOrders.h"
#include "KMIPAttributeRule.h"

std::map<int, std::shared_ptr<KMIPFactory> > KMIPUtils::mapKMIPFactories = {
    {kmip::TypeStructure, std::shared_ptr<KMIPFactory>(new KMIPStructFactory())},
    {kmip::TypeEnumeration, std::shared_ptr<KMIPFactory>(new KMIPEnumFactory())}
};

std::shared_ptr<KMIPFieldOrders> KMIPUtils::spkfos(new KMIPFieldOrders);

KMIPFieldUP KMIPUtils::createField(int iTag, int iType) {
    KMIPFieldUP upkf;
    switch (iType) {
        case kmip::TypeStructure:
            upkf = mapKMIPFactories[iType]->createField(iTag);
            break;
        case kmip::TypeInteger:
            upkf.reset(new KMIPInteger(iTag));
            break;
        case kmip::TypeLongInteger:
            upkf.reset(new KMIPLongInteger(iTag));
            break;
        case kmip::TypeBigInteger:
            upkf.reset(new KMIPBigInteger(iTag));
            break;
        case kmip::TypeEnumeration:
            upkf = mapKMIPFactories[iType]->createField(iTag);
            break;
        case kmip::TypeBoolean:
            upkf.reset(new KMIPBoolean(iTag));
            break;
        case kmip::TypeTextString:
            upkf.reset(new KMIPTextString(iTag));
            break;
        case kmip::TypeByteString:
            upkf.reset(new KMIPByteString(iTag));
            break;
        case kmip::TypeDateTime:
            upkf.reset(new KMIPDateTime(iTag));
            break;
        case kmip::TypeInterval:
            upkf.reset(new KMIPInterval(iTag));
            break;
        default:
            break;
    }

    return upkf;
}

KMIPFieldOrder *KMIPUtils::getKMIPFieldOrder(int iTag, int iType) {
    return spkfos ? spkfos->getKMIPFieldOrder(iTag, iType) : nullptr;
}

std::shared_ptr<KMIPAttributeRule> KMIPUtils::getAttributeRule(int iTag) {
    auto mapIter = mapTagToRule.find(iTag);
    return mapIter == mapTagToRule.end() ? std::shared_ptr<KMIPAttributeRule>() : mapIter->second;
}

std::string KMIPUtils::TypeToString(int iType) {
    std::string sRet = "Unknown";
    switch (iType) {
        case kmip::TypeStructure:
            sRet = "Structure";
            break;
        case kmip::TypeInteger:
            sRet = "Integer";
            break;
        case kmip::TypeLongInteger:
            sRet = "LongInteger";
            break;
        case kmip::TypeBigInteger:
            sRet = "BigInteger";
            break;
        case kmip::TypeEnumeration:
            sRet = "Enumeration";
            break;
        case kmip::TypeBoolean:
            sRet = "Boolean";
            break;
        case kmip::TypeTextString:
            sRet = "TextString";
            break;
        case kmip::TypeByteString:
            sRet = "ByteString";
            break;
        case kmip::TypeDateTime:
            sRet = "DateTime";
            break;
        case kmip::TypeInterval:
            sRet = "Interval";
            break;
        default:
            break;
    }

    return sRet;
}


bool KMIPUtils::isTagUnknown(int iTag) {
    return iTag <= kmip::TagUnknownEnd || iTag > kmip::TagEndExtensionTags;
}

bool KMIPUtils::isTagReserved(int iTag) {
    return kmip::TagBegReservedTags <= iTag && iTag <= kmip::TagEndReservedTags;
}

bool KMIPUtils::isTagExtension(int iTag) {
    return kmip::TagBegExtensionTags <= iTag && iTag <= kmip::TagEndExtensionTags;
}

bool KMIPUtils::isTagKnown(int iTag) {
    return kmip::TagUnknownEnd < iTag && iTag < kmip::TagBegReservedTags;
}

std::string KMIPUtils::TagToString(int iTag) {
    auto mapIter = mapTagToString.find(iTag);
    return mapIter != mapTagToString.end() ? mapIter->second : "Unknown";
}

unsigned int KMIPUtils::getTotalLength(unsigned int iLength) {
    int iMod = iLength % 8;
    return iMod == 0 ? iLength : iLength + (8 - iMod);
}

std::string KMIPUtils::printFieldString(const KMIPField *pkf, int iDepth) {
    std::string sRet(iDepth, '\t');
    if (pkf) {
        if (pkf->getType() == kmip::TypeStructure) {
            sRet += "|" + KMIPUtils::TagToString(pkf->getTag()) + "|"
                + KMIPUtils::TypeToString(pkf->getType()) + "|\n";
            const KMIPStruct *pkfst = static_cast<const KMIPStruct *>(pkf);
            if (pkfst) {
                auto listFields = pkfst->getFields();
                for (auto iter = listFields.begin(); iter != listFields.end(); iter++) {
                    sRet += printFieldString(iter->get(), iDepth + 1);
                }
            }
        } else {
            sRet += "|" + KMIPUtils::TagToString(pkf->getTag()) + "|"
                + KMIPUtils::TypeToString(pkf->getType()) + "|"
                + pkf->getValueString() + "|\n";
        }
    }

    return sRet;
}

const std::map<int, std::string> KMIPUtils::mapTagToString = {
        {kmip::TagUnknown, "Unknown"},
        {kmip::TagUnknownEnd, "UnknownEnd"},
        {kmip::TagActivationDate, "ActivationDate"},
        {kmip::TagApplicationData, "ApplicationData"},
        {kmip::TagApplicationNamespace, "ApplicationNamespace"},
        {kmip::TagApplicationSpecificInformation, "ApplicationSpecificInformation"},
        {kmip::TagArchiveDate, "ArchiveDate"},
        {kmip::TagAsynchronousCorrelationValue, "AsynchronousCorrelationValue"},
        {kmip::TagAsynchronousIndicator, "AsynchronousIndicator"},
        {kmip::TagAttribute, "Attribute"},
        {kmip::TagAttributeIndex, "AttributeIndex"},
        {kmip::TagAttributeName, "AttributeName"},
        {kmip::TagAttributeValue, "AttributeValue"},
        {kmip::TagAuthentication, "Authentication"},
        {kmip::TagBatchCount, "BatchCount"},
        {kmip::TagBatchErrorContinuationOption, "BatchErrorContinuationOption"},
        {kmip::TagBatchItem, "BatchItem"},
        {kmip::TagBatchOrderOption, "BatchOrderOption"},
        {kmip::TagBlockCipherMode, "BlockCipherMode"},
        {kmip::TagCancellationResult, "CancellationResult"},
        {kmip::TagCertificate, "Certificate"},
        {kmip::TagCertificateIdentifier, "CertificateIdentifier"},
        {kmip::TagCertificateIssuer, "CertificateIssuer"},
        {kmip::TagCertificateIssuerAlternativeName, "CertificateIssuerAlternativeName"},
        {kmip::TagCertificateIssuerDistinguishedName, "CertificateIssuerDistinguishedName"},
        {kmip::TagCertificateRequest, "CertificateRequest"},
        {kmip::TagCertificateRequestType, "CertificateRequestType"},
        {kmip::TagCertificateSubject, "CertificateSubject"},
        {kmip::TagCertificateSubjectAlternativeName, "CertificateSubjectAlternativeName"},
        {kmip::TagCertificateSubjectDistinguishedName, "CertificateSubjectDistinguishedName"},
        {kmip::TagCertificateType, "CertificateType"},
        {kmip::TagCertificateValue, "CertificateValue"},
        {kmip::TagCommonTemplateAttribute, "CommonTemplateAttribute"},
        {kmip::TagCompromiseDate, "CompromiseDate"},
        {kmip::TagCompromiseOccurrenceDate, "CompromiseOccurrenceDate"},
        {kmip::TagContactInformation, "ContactInformation"},
        {kmip::TagCredential, "Credential"},
        {kmip::TagCredentialType, "CredentialType"},
        {kmip::TagCredentialValue, "CredentialValue"},
        {kmip::TagCriticalityIndicator, "CriticalityIndicator"},
        {kmip::TagCRTCoefficient, "CRTCoefficient"},
        {kmip::TagCryptographicAlgorithm, "CryptographicAlgorithm"},
        {kmip::TagCryptographicDomainParameters, "CryptographicDomainParameters"},
        {kmip::TagCryptographicLength, "CryptographicLength"},
        {kmip::TagCryptographicParameters, "CryptographicParameters"},
        {kmip::TagCryptographicUsageMask, "CryptographicUsageMask"},
        {kmip::TagCustomAttribute, "CustomAttribute"},
        {kmip::TagD, "D"},
        {kmip::TagDeactivationDate, "DeactivationDate"},
        {kmip::TagDerivationData, "DerivationData"},
        {kmip::TagDerivationMethod, "DerivationMethod"},
        {kmip::TagDerivationParameters, "DerivationParameters"},
        {kmip::TagDestroyDate, "DestroyDate"},
        {kmip::TagDigest, "Digest"},
        {kmip::TagDigestValue, "DigestValue"},
        {kmip::TagEncryptionKeyInformation, "EncryptionKeyInformation"},
        {kmip::TagG, "G"},
        {kmip::TagHashingAlgorithm, "HashingAlgorithm"},
        {kmip::TagInitialDate, "InitialDate"},
        {kmip::TagInitializationVector, "InitializationVector"},
        {kmip::TagIssuer, "Issuer"},
        {kmip::TagIterationCount, "IterationCount"},
        {kmip::TagIVCounterNonce, "IVCounterNonce"},
        {kmip::TagJ, "J"},
        {kmip::TagKey, "Key"},
        {kmip::TagKeyBlock, "KeyBlock"},
        {kmip::TagKeyCompressionType, "KeyCompressionType"},
        {kmip::TagKeyFormatType, "KeyFormatType"},
        {kmip::TagKeyMaterial, "KeyMaterial"},
        {kmip::TagKeyPartIdentifier, "KeyPartIdentifier"},
        {kmip::TagKeyValue, "KeyValue"},
        {kmip::TagKeyWrappingData, "KeyWrappingData"},
        {kmip::TagKeyWrappingSpecification, "KeyWrappingSpecification"},
        {kmip::TagLastChangeDate, "LastChangeDate"},
        {kmip::TagLeaseTime, "LeaseTime"},
        {kmip::TagLink, "Link"},
        {kmip::TagLinkType, "LinkType"},
        {kmip::TagLinkedObjectIdentifier, "LinkedObjectIdentifier"},
        {kmip::TagMACSignature, "MACSignature"},
        {kmip::TagMACSignatureKeyInformation, "MACSignatureKeyInformation"},
        {kmip::TagMaximumItems, "MaximumItems"},
        {kmip::TagMaximumResponseSize, "MaximumResponseSize"},
        {kmip::TagMessageExtension, "MessageExtension"},
        {kmip::TagModulus, "Modulus"},
        {kmip::TagName, "Name"},
        {kmip::TagNameType, "NameType"},
        {kmip::TagNameValue, "NameValue"},
        {kmip::TagObjectGroup, "ObjectGroup"},
        {kmip::TagObjectType, "ObjectType"},
        {kmip::TagOffset, "Offset"},
        {kmip::TagOpaqueDataType, "OpaqueDataType"},
        {kmip::TagOpaqueDataValue, "OpaqueDataValue"},
        {kmip::TagOpaqueObject, "OpaqueObject"},
        {kmip::TagOperation, "Operation"},
        {kmip::TagOperationPolicyName, "OperationPolicyName"},
        {kmip::TagP, "P"},
        {kmip::TagPaddingMethod, "PaddingMethod"},
        {kmip::TagPrimeExponentP, "PrimeExponentP"},
        {kmip::TagPrimeExponentQ, "PrimeExponentQ"},
        {kmip::TagPrimeFieldSize, "PrimeFieldSize"},
        {kmip::TagPrivateExponent, "PrivateExponent"},
        {kmip::TagPrivateKey, "PrivateKey"},
        {kmip::TagPrivateKeyTemplateAttribute, "PrivateKeyTemplateAttribute"},
        {kmip::TagPrivateKeyUniqueIdentifier, "PrivateKeyUniqueIdentifier"},
        {kmip::TagProcessStartDate, "ProcessStartDate"},
        {kmip::TagProtectStopDate, "ProtectStopDate"},
        {kmip::TagProtocolVersion, "ProtocolVersion"},
        {kmip::TagProtocolVersionMajor, "ProtocolVersionMajor"},
        {kmip::TagProtocolVersionMinor, "ProtocolVersionMinor"},
        {kmip::TagPublicExponent, "PublicExponent"},
        {kmip::TagPublicKey, "PublicKey"},
        {kmip::TagPublicKeyTemplateAttribute, "PublicKeyTemplateAttribute"},
        {kmip::TagPublicKeyUniqueIdentifier, "PublicKeyUniqueIdentifier"},
        {kmip::TagPutFunction, "PutFunction"},
        {kmip::TagQ, "Q"},
        {kmip::TagQString, "QString"},
        {kmip::TagQlength, "Qlength"},
        {kmip::TagQueryFunction, "QueryFunction"},
        {kmip::TagRecommendedCurve, "RecommendedCurve"},
        {kmip::TagReplacedUniqueIdentifier, "ReplacedUniqueIdentifier"},
        {kmip::TagRequestHeader, "RequestHeader"},
        {kmip::TagRequestMessage, "RequestMessage"},
        {kmip::TagRequestPayload, "RequestPayload"},
        {kmip::TagResponseHeader, "ResponseHeader"},
        {kmip::TagResponseMessage, "ResponseMessage"},
        {kmip::TagResponsePayload, "ResponsePayload"},
        {kmip::TagResultMessage, "ResultMessage"},
        {kmip::TagResultReason, "ResultReason"},
        {kmip::TagResultStatus, "ResultStatus"},
        {kmip::TagRevocationMessage, "RevocationMessage"},
        {kmip::TagRevocationReason, "RevocationReason"},
        {kmip::TagRevocationReasonCode, "RevocationReasonCode"},
        {kmip::TagKeyRoleType, "KeyRoleType"},
        {kmip::TagSalt, "Salt"},
        {kmip::TagSecretData, "SecretData"},
        {kmip::TagSecretDataType, "SecretDataType"},
        {kmip::TagSerialNumber, "SerialNumber"},
        {kmip::TagServerInformation, "ServerInformation"},
        {kmip::TagSplitKey, "SplitKey"},
        {kmip::TagSplitKeyMethod, "SplitKeyMethod"},
        {kmip::TagSplitKeyParts, "SplitKeyParts"},
        {kmip::TagSplitKeyThreshold, "SplitKeyThreshold"},
        {kmip::TagState, "State"},
        {kmip::TagStorageStatusMask, "StorageStatusMask"},
        {kmip::TagSymmetricKey, "SymmetricKey"},
        {kmip::TagTemplate, "Template"},
        {kmip::TagTemplateAttribute, "TemplateAttribute"},
        {kmip::TagTimeStamp, "TimeStamp"},
        {kmip::TagUniqueBatchItemID, "UniqueBatchItemID"},
        {kmip::TagUniqueIdentifier, "UniqueIdentifier"},
        {kmip::TagUsageLimits, "UsageLimits"},
        {kmip::TagUsageLimitsCount, "UsageLimitsCount"},
        {kmip::TagUsageLimitsTotal, "UsageLimitsTotal"},
        {kmip::TagUsageLimitsUnit, "UsageLimitsUnit"},
        {kmip::TagUsername, "Username"},
        {kmip::TagValidityDate, "ValidityDate"},
        {kmip::TagValidityIndicator, "ValidityIndicator"},
        {kmip::TagVendorExtension, "VendorExtension"},
        {kmip::TagVendorIdentification, "VendorIdentification"},
        {kmip::TagWrappingMethod, "WrappingMethod"},
        {kmip::TagX, "X"},
        {kmip::TagY, "Y"},
        {kmip::TagPassword, "Password"},
        {kmip::TagDeviceIdentifier, "DeviceIdentifier"},
        {kmip::TagEncodingOption, "EncodingOption"},
        {kmip::TagExtensionInformation, "ExtensionInformation"},
        {kmip::TagExtensionName, "ExtensionName"},
        {kmip::TagExtensionTag, "ExtensionTag"},
        {kmip::TagExtensionType, "ExtensionType"},
        {kmip::TagFresh, "Fresh"},
        {kmip::TagMachineIdentifier, "MachineIdentifier"},
        {kmip::TagMediaIdentifier, "MediaIdentifier"},
        {kmip::TagNetworkIdentifier, "NetworkIdentifier"},
        {kmip::TagObjectGroupMember, "ObjectGroupMember"},
        {kmip::TagCertificateLength, "CertificateLength"},
        {kmip::TagDigitalSignatureAlgorithm, "DigitalSignatureAlgorithm"},
        {kmip::TagCertificateSerialNumber, "CertificateSerialNumber"},
        {kmip::TagDeviceSerialNumber, "DeviceSerialNumber"},
        {kmip::TagIssuerAlternativeName, "IssuerAlternativeName"},
        {kmip::TagIssuerDistinguishedName, "IssuerDistinguishedName"},
        {kmip::TagSubjectAlternativeName, "SubjectAlternativeName"},
        {kmip::TagSubjectDistinguishedName, "SubjectDistinguishedName"},
        {kmip::TagX509CertificateIdentifier, "X509CertificateIdentifier"},
        {kmip::TagX509CertificateIssuer, "X509CertificateIssuer"},
        {kmip::TagX509CertificateSubject, "X509CertificateSubject"},
        {kmip::TagKeyValueLocation, "KeyValueLocation"},
        {kmip::TagKeyValueLocationValue, "KeyValueLocationValue"},
        {kmip::TagKeyValueLocationType, "KeyValueLocationType"},
        {kmip::TagKeyValuePresent, "KeyValuePresent"},
        {kmip::TagOriginalCreationDate, "OriginalCreationDate"},
        {kmip::TagPGPKey, "PGPKey"},
        {kmip::TagPGPKeyVersion, "PGPKeyVersion"},
        {kmip::TagAlternativeName, "AlternativeName"},
        {kmip::TagAlternativeNameValue, "AlternativeNameValue"},
        {kmip::TagAlternativeNameType, "AlternativeNameType"},
        {kmip::TagData, "Data"},
        {kmip::TagSignatureData, "SignatureData"},
        {kmip::TagDataLength, "DataLength"},
        {kmip::TagRandomIV, "RandomIV"},
        {kmip::TagMACData, "MACData"},
        {kmip::TagAttestationType, "AttestationType"},
        {kmip::TagNonce, "Nonce"},
        {kmip::TagNonceID, "NonceID"},
        {kmip::TagNonceValue, "NonceValue"},
        {kmip::TagAttestationMeasurement, "AttestationMeasurement"},
        {kmip::TagAttestationAssertion, "AttestationAssertion"},
        {kmip::TagIVLength, "IVLength"},
        {kmip::TagTagLength, "TagLength"},
        {kmip::TagFixedFieldLength, "FixedFieldLength"},
        {kmip::TagCounterLength, "CounterLength"},
        {kmip::TagInitialCounterValue, "InitialCounterValue"},
        {kmip::TagInvocationFieldLength, "InvocationFieldLength"},
        {kmip::TagAttestationCapableIndicator, "AttestationCapableIndicator"},
        {kmip::TagOffsetItems, "OffsetItems"},
        {kmip::TagLocatedItems, "LocatedItems"},
        {kmip::TagCorrelationValue, "CorrelationValue"},
        {kmip::TagInitIndicator, "InitIndicator"},
        {kmip::TagFinalIndicator, "FinalIndicator"},
        {kmip::TagRNGParameters, "RNGParameters"},
        {kmip::TagRNGAlgorithm, "RNGAlgorithm"},
        {kmip::TagDRBGAlgorithm, "DRBGAlgorithm"},
        {kmip::TagFIPS186Variation, "FIPS186Variation"},
        {kmip::TagPredictionResistance, "PredictionResistance"},
        {kmip::TagRandomNumberGenerator, "RandomNumberGenerator"},
        {kmip::TagValidationInformation, "ValidationInformation"},
        {kmip::TagValidationAuthorityType, "ValidationAuthorityType"},
        {kmip::TagValidationAuthorityCountry, "ValidationAuthorityCountry"},
        {kmip::TagValidationAuthorityURI, "ValidationAuthorityURI"},
        {kmip::TagValidationVersionMajor, "ValidationVersionMajor"},
        {kmip::TagValidationVersionMinor, "ValidationVersionMinor"},
        {kmip::TagValidationType, "ValidationType"},
        {kmip::TagValidationLevel, "ValidationLevel"},
        {kmip::TagValidationCertificateIdentifier, "ValidationCertificateIdentifier"},
        {kmip::TagValidationCertificateURI, "ValidationCertificateURI"},
        {kmip::TagValidationVendorURI, "ValidationVendorURI"},
        {kmip::TagValidationProfile, "ValidationProfile"},
        {kmip::TagProfileInformation, "ProfileInformation"},
        {kmip::TagProfileName, "ProfileName"},
        {kmip::TagServerURI, "ServerURI"},
        {kmip::TagServerPort, "ServerPort"},
        {kmip::TagStreamingCapability, "StreamingCapability"},
        {kmip::TagAsynchronousCapability, "AsynchronousCapability"},
        {kmip::TagAttestationCapability, "AttestationCapability"},
        {kmip::TagUnwrapMode, "UnwrapMode"},
        {kmip::TagDestroyAction, "DestroyAction"},
        {kmip::TagShreddingAlgorithm, "ShreddingAlgorithm"},
        {kmip::TagRNGMode, "RNGMode"},
        {kmip::TagClientRegistrationMethod, "ClientRegistrationMethod"},
        {kmip::TagCapabilityInformation, "CapabilityInformation"},
        {kmip::TagKeyWrapType, "KeyWrapType"},
        {kmip::TagBatchUndoCapability, "BatchUndoCapability"},
        {kmip::TagBatchContinueCapability, "BatchContinueCapability"},
        {kmip::TagPKCS_12FriendlyName, "PKCS_12FriendlyName"},
        {kmip::TagDescription, "Description"},
        {kmip::TagComment, "Comment"},
        {kmip::TagAuthenticatedEncryptionAdditionalData, "AuthenticatedEncryptionAdditionalData"},
        {kmip::TagAuthenticatedEncryptionTag, "AuthenticatedEncryptionTag"},
        {kmip::TagSaltLength, "SaltLength"},
        {kmip::TagMaskGenerator, "MaskGenerator"},
        {kmip::TagMaskGeneratorHashingAlgorithm, "MaskGeneratorHashingAlgorithm"},
        {kmip::TagPSource, "PSource"},
        {kmip::TagTrailerField, "TrailerField"},
        {kmip::TagClientCorrelationValue, "ClientCorrelationValue"},
        {kmip::TagServerCorrelationValue, "ServerCorrelationValue"},
        {kmip::TagDigestedData, "DigestedData"},
        {kmip::TagCertificateSubjectCN, "CertificateSubjectCN"},
        {kmip::TagCertificateSubjectO, "CertificateSubjectO"},
        {kmip::TagCertificateSubjectOU, "CertificateSubjectOU"},
        {kmip::TagCertificateSubjectEmail, "CertificateSubjectEmail"},
        {kmip::TagCertificateSubjectC, "CertificateSubjectC"},
        {kmip::TagCertificateSubjectST, "CertificateSubjectST"},
        {kmip::TagCertificateSubjectL, "CertificateSubjectL"},
        {kmip::TagCertificateSubjectUID, "CertificateSubjectUID"},
        {kmip::TagCertificateSubjectSerialNumber, "CertificateSubjectSerialNumber"},
        {kmip::TagCertificateSubjectTitle, "CertificateSubjectTitle"},
        {kmip::TagCertificateSubjectDC, "CertificateSubjectDC"},
        {kmip::TagCertificateSubjectDNQualifier, "CertificateSubjectDNQualifier"},
        {kmip::TagCertificateIssuerCN, "CertificateIssuerCN"},
        {kmip::TagCertificateIssuerO, "CertificateIssuerO"},
        {kmip::TagCertificateIssuerOU, "CertificateIssuerOU"},
        {kmip::TagCertificateIssuerEmail, "CertificateIssuerEmail"},
        {kmip::TagCertificateIssuerC, "CertificateIssuerC"},
        {kmip::TagCertificateIssuerST, "CertificateIssuerST"},
        {kmip::TagCertificateIssuerL, "CertificateIssuerL"},
        {kmip::TagCertificateIssuerUID, "CertificateIssuerUID"},
        {kmip::TagCertificateIssuerSerialNumber, "CertificateIssuerSerialNumber"},
        {kmip::TagCertificateIssuerTitle, "CertificateIssuerTitle"},
        {kmip::TagCertificateIssuerDC, "CertificateIssuerDC"},
        {kmip::TagCertificateIssuerDNQualifier, "CertificateIssuerDNQualifier"},
        {kmip::TagSensitive, "Sensitive"},
        {kmip::TagAlwaysSensitive, "AlwaysSensitive"},
        {kmip::TagExtractable, "Extractable"},
        {kmip::TagNeverExtractable, "NeverExtractable"},
        {kmip::TagReplaceExisting, "ReplaceExisting"},
        {kmip::TagBegReservedTags, "BegReservedTags,"},
        {kmip::TagEndReservedTags, "EndReservedTags"},
        {kmip::TagBegExtensionTags, "BegExtensionTags"},
        {kmip::TagEndExtensionTags, "EndExtensionTags"}
};

const std::map<int, std::shared_ptr<KMIPAttributeRule> > KMIPUtils::mapTagToRule = {
    {kmip::TagUniqueIdentifier, std::shared_ptr<KMIPAttributeRule>(new KMIPUniqueIdentifierRule)},
    {kmip::TagName, std::shared_ptr<KMIPAttributeRule>(new KMIPNameRule)},
    {kmip::TagObjectType, std::shared_ptr<KMIPAttributeRule>(new KMIPObjectTypeRule)},
    {kmip::TagCryptographicAlgorithm, std::shared_ptr<KMIPAttributeRule>(new KMIPCryptographicAlgorithmRule)},
    {kmip::TagCryptographicLength, std::shared_ptr<KMIPAttributeRule>(new KMIPCryptographicLengthRule)},
    {kmip::TagCryptographicParameters, std::shared_ptr<KMIPAttributeRule>(new KMIPCryptographicParametersRule)},
    {kmip::TagCryptographicDomainParameters, std::shared_ptr<KMIPAttributeRule>(new KMIPCryptographicDomainParametersRule)},
    {kmip::TagCertificateType, std::shared_ptr<KMIPAttributeRule>(new KMIPCertificateTypeRule)},
    {kmip::TagCertificateLength, std::shared_ptr<KMIPAttributeRule>(new KMIPCertificateLengthRule)},
    {kmip::TagX509CertificateIdentifier, std::shared_ptr<KMIPAttributeRule>(new KMIPX509CertificateIdentifierRule)},
    {kmip::TagX509CertificateSubject, std::shared_ptr<KMIPAttributeRule>(new KMIPX509CertificateSubjectRule)},
    {kmip::TagX509CertificateIssuer, std::shared_ptr<KMIPAttributeRule>(new KMIPX509CertificateIssuerRule)},
    {kmip::TagCertificateIdentifier, std::shared_ptr<KMIPAttributeRule>(new KMIPCertificateIdentifierRule)},
    {kmip::TagCertificateSubject, std::shared_ptr<KMIPAttributeRule>(new KMIPCertificateSubjectRule)},
    {kmip::TagCertificateIssuer, std::shared_ptr<KMIPAttributeRule>(new KMIPCertificateIssuerRule)},
    {kmip::TagDigitalSignatureAlgorithm, std::shared_ptr<KMIPAttributeRule>(new KMIPDigitalSignatureAlgorithmRule)},
    {kmip::TagDigest, std::shared_ptr<KMIPAttributeRule>(new KMIPDigestRule)},
    {kmip::TagOperationPolicyName, std::shared_ptr<KMIPAttributeRule>(new KMIPOperationPolicyNameRule)},
    {kmip::TagCryptographicUsageMask, std::shared_ptr<KMIPAttributeRule>(new KMIPCryptographicUsageMaskRule)},
    {kmip::TagLeaseTime, std::shared_ptr<KMIPAttributeRule>(new KMIPLeaseTimeRule)},
    {kmip::TagUsageLimits, std::shared_ptr<KMIPAttributeRule>(new KMIPUsageLimitsRule)},
    {kmip::TagState, std::shared_ptr<KMIPAttributeRule>(new KMIPStateRule)},
    {kmip::TagInitialDate, std::shared_ptr<KMIPAttributeRule>(new KMIPInitialDateRule)},
    {kmip::TagActivationDate, std::shared_ptr<KMIPAttributeRule>(new KMIPActivationDateRule)},
    {kmip::TagProcessStartDate, std::shared_ptr<KMIPAttributeRule>(new KMIPProcessStartDateRule)},
    {kmip::TagProtectStopDate, std::shared_ptr<KMIPAttributeRule>(new KMIPProtectStopDateRule)},
    {kmip::TagDeactivationDate, std::shared_ptr<KMIPAttributeRule>(new KMIPDeactivationDateRule)},
    {kmip::TagDestroyDate, std::shared_ptr<KMIPAttributeRule>(new KMIPDestroyDateRule)},
    {kmip::TagCompromiseOccurrenceDate, std::shared_ptr<KMIPAttributeRule>(new KMIPCompromiseOccurrenceDateRule)},
    {kmip::TagCompromiseDate, std::shared_ptr<KMIPAttributeRule>(new KMIPCompromiseDateRule)},
    {kmip::TagRevocationReason, std::shared_ptr<KMIPAttributeRule>(new KMIPRevocationReasonRule)},
    {kmip::TagArchiveDate, std::shared_ptr<KMIPAttributeRule>(new KMIPArchiveDateRule)},
    {kmip::TagObjectGroup, std::shared_ptr<KMIPAttributeRule>(new KMIPObjectGroupRule)},
    {kmip::TagFresh, std::shared_ptr<KMIPAttributeRule>(new KMIPFreshRule)},
    {kmip::TagLink, std::shared_ptr<KMIPAttributeRule>(new KMIPLinkRule)},
    {kmip::TagApplicationSpecificInformation, std::shared_ptr<KMIPAttributeRule>(new KMIPApplicationSpecificInformationRule)},
    {kmip::TagContactInformation, std::shared_ptr<KMIPAttributeRule>(new KMIPContactInformationRule)},
    {kmip::TagLastChangeDate, std::shared_ptr<KMIPAttributeRule>(new KMIPLastChangeDateRule)},
    {kmip::TagCustomAttribute, std::shared_ptr<KMIPAttributeRule>(new KMIPCustomAttributeRule)},
    {kmip::TagAlternativeName, std::shared_ptr<KMIPAttributeRule>(new KMIPAlternativeNameRule)},
    {kmip::TagKeyValuePresent, std::shared_ptr<KMIPAttributeRule>(new KMIPKeyValuePresentRule)},
    {kmip::TagKeyValueLocation, std::shared_ptr<KMIPAttributeRule>(new KMIPKeyValueLocationRule)},
    {kmip::TagOriginalCreationDate, std::shared_ptr<KMIPAttributeRule>(new KMIPOriginalCreationDateRule)},
    {kmip::TagRandomNumberGenerator, std::shared_ptr<KMIPAttributeRule>(new KMIPRandomNumberGeneratorRule)},
    {kmip::TagPKCS_12FriendlyName, std::shared_ptr<KMIPAttributeRule>(new KMIPPKCS_12FriendlyNameRule)},
    {kmip::TagDescription, std::shared_ptr<KMIPAttributeRule>(new KMIPDescriptionRule)},
    {kmip::TagComment, std::shared_ptr<KMIPAttributeRule>(new KMIPCommentRule)},
    {kmip::TagSensitive, std::shared_ptr<KMIPAttributeRule>(new KMIPSensitiveRule)},
    {kmip::TagAlwaysSensitive, std::shared_ptr<KMIPAttributeRule>(new KMIPAlwaysSensitiveRule)},
    {kmip::TagExtractable, std::shared_ptr<KMIPAttributeRule>(new KMIPExtractableRule)},
    {kmip::TagNeverExtractable, std::shared_ptr<KMIPAttributeRule>(new KMIPNeverExtractableRule)}
};


int KMIPUtils::getTagType(int iTag) {
    int iType = kmip::TypeUnknown;
    switch (iTag) {
        default:
            break;
    }

    return iType;
}
