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
#include "KMIPBitMask.h"

std::map<int, std::shared_ptr<KMIPFactory> > KMIPUtils::mapKMIPFactories = {
    {kmip::TypeStructure, std::shared_ptr<KMIPFactory>(new KMIPStructFactory())},
    {kmip::TypeEnumeration, std::shared_ptr<KMIPFactory>(new KMIPEnumFactory())}
};

std::shared_ptr<KMIPFieldOrders> KMIPUtils::spkfos(new KMIPFieldOrders);

KMIPFieldUP KMIPUtils::createField(int iTag, int iType) {
    KMIPFieldUP upkf;
    switch (iTag) {
        case kmip::TagCryptographicUsageMask:
            upkf.reset(new KMIPCryptographicUsageMask());
            break;
        case kmip::TagStorageStatusMask:
            upkf.reset(new KMIPStorageStatusMask());
            break;
        default:
            break;
    }
    if (!upkf) {
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

int KMIPUtils::TagFromString(const std::string &sTag) {
    int iTag = kmip::TagUnknown;
    for (auto tuple : mapTagToString) {
        if (sTag == tuple.second) {
            iTag = tuple.first;
            break;
        }
    }

    return iTag;
}

int KMIPUtils::TypeFromString(const std::string &sType) {
    int iType = kmip::TypeUnknown;
    for (int i = kmip::TypeUnknown; i < kmip::TypeMulti; ++i) {
        if (sType == TypeToString(i)) {
            iType = i;
            break;
        }
    }

    return iType;
}


std::string KMIPUtils::getTagName(int iTag) {
    std::string sRet;
    for (auto tuple : mapNameToTag) {
        if (tuple.second == iTag) {
            sRet = tuple.first;
            break;
        }
    }

    return sRet;
}

int KMIPUtils::getNameTag(const std::string &sName) {
    auto mapIter = mapNameToTag.find(sName);
    return mapIter != mapNameToTag.end() ? mapIter->second : (int) kmip::TagUnknown;
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
        } else if (pkf->getType() == kmip::TypeEnumeration) {
            const KMIPEnumeration *pke = dynamic_cast<const KMIPEnumeration *>(pkf);
            if (pke) {
                sRet += "|" + KMIPUtils::TagToString(pkf->getTag()) + "|"
                    + KMIPUtils::TypeToString(pkf->getType()) + "|"
                    + pkf->getValueString() + "(" + pke->getValueName() + ")|\n";
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
    {kmip::TagX509CertificateIdentifier, "X_509CertificateIdentifier"},
    {kmip::TagX509CertificateIssuer, "X_509CertificateIssuer"},
    {kmip::TagX509CertificateSubject, "X_509CertificateSubject"},
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

const std::map<std::string, int> KMIPUtils::mapNameToTag = {
    {"Activation Date", kmip::TagActivationDate},
    {"Application Data", kmip::TagApplicationData},
    {"Application Namespace", kmip::TagApplicationNamespace},
    {"Application Specific Information", kmip::TagApplicationSpecificInformation},
    {"Archive Date", kmip::TagArchiveDate},
    {"Asynchronous Correlation Value", kmip::TagAsynchronousCorrelationValue},
    {"Asynchronous Indicator", kmip::TagAsynchronousIndicator},
    {"Attribute", kmip::TagAttribute},
    {"Attribute Index", kmip::TagAttributeIndex},
    {"Attribute Name", kmip::TagAttributeName},
    {"Attribute Value", kmip::TagAttributeValue},
    {"Authentication", kmip::TagAuthentication},
    {"Batch Count", kmip::TagBatchCount},
    {"Batch Error Continuation Option ", kmip::TagBatchErrorContinuationOption},
    {"Batch Item", kmip::TagBatchItem},
    {"Batch Order Option ", kmip::TagBatchOrderOption},
    {"Block Cipher Mode", kmip::TagBlockCipherMode},
    {"Cancellation Result", kmip::TagCancellationResult},
    {"Certificate", kmip::TagCertificate},
    {"Certificate Identifier", kmip::TagCertificateIdentifier},
    {"Certificate Issuer", kmip::TagCertificateIssuer},
    {"Certificate Issuer Alternative Name", kmip::TagCertificateIssuerAlternativeName},
    {"Certificate Issuer Distinguished Name", kmip::TagCertificateIssuerDistinguishedName},
    {"Certificate Request", kmip::TagCertificateRequest},
    {"Certificate Request Type", kmip::TagCertificateRequestType},
    {"Certificate Subject", kmip::TagCertificateSubject},
    {"Certificate Subject Alternative Name", kmip::TagCertificateSubjectAlternativeName},
    {"Certificate Subject Distinguished Name", kmip::TagCertificateSubjectDistinguishedName},
    {"Certificate Type", kmip::TagCertificateType},
    {"Certificate Value", kmip::TagCertificateValue},
    {"Common Template-Attribute", kmip::TagCommonTemplateAttribute},
    {"Compromise  Date", kmip::TagCompromiseDate},
    {"Compromise Occurrence Date", kmip::TagCompromiseOccurrenceDate},
    {"Contact Information", kmip::TagContactInformation},
    {"Credential", kmip::TagCredential},
    {"Credential Type", kmip::TagCredentialType},
    {"Credential Value", kmip::TagCredentialValue},
    {"Criticality Indicator", kmip::TagCriticalityIndicator},
    {"CRT Coefficient", kmip::TagCRTCoefficient},
    {"Cryptographic Algorithm", kmip::TagCryptographicAlgorithm},
    {"Cryptographic Domain Parameters", kmip::TagCryptographicDomainParameters},
    {"Cryptographic Length", kmip::TagCryptographicLength},
    {"Cryptographic Parameters", kmip::TagCryptographicParameters},
    {"Cryptographic Usage Mask", kmip::TagCryptographicUsageMask},
    {"Custom Attribute", kmip::TagCustomAttribute},
    {"D", kmip::TagD},
    {"Deactivation Date", kmip::TagDeactivationDate},
    {"Derivation Data", kmip::TagDerivationData},
    {"Derivation Method ", kmip::TagDerivationMethod},
    {"Derivation Parameters", kmip::TagDerivationParameters},
    {"Destroy Date", kmip::TagDestroyDate},
    {"Digest", kmip::TagDigest},
    {"Digest Value", kmip::TagDigestValue},
    {"Encryption Key Information", kmip::TagEncryptionKeyInformation},
    {"G", kmip::TagG},
    {"Hashing Algorithm", kmip::TagHashingAlgorithm},
    {"Initial Date", kmip::TagInitialDate},
    {"Initialization Vector", kmip::TagInitializationVector},
    {"Issuer", kmip::TagIssuer},
    {"Iteration Count", kmip::TagIterationCount},
    {"IV/Counter/Nonce", kmip::TagIVCounterNonce},
    {"J", kmip::TagJ},
    {"Key", kmip::TagKey},
    {"Key Block", kmip::TagKeyBlock},
    {"Key Compression Type", kmip::TagKeyCompressionType},
    {"Key Format Type", kmip::TagKeyFormatType},
    {"Key Material", kmip::TagKeyMaterial},
    {"Key Part Identifier", kmip::TagKeyPartIdentifier},
    {"Key Value", kmip::TagKeyValue},
    {"Key Wrapping Data", kmip::TagKeyWrappingData},
    {"Key Wrapping Specification", kmip::TagKeyWrappingSpecification},
    {"Last Change Date", kmip::TagLastChangeDate},
    {"Lease Time", kmip::TagLeaseTime},
    {"Link", kmip::TagLink},
    {"Link Type", kmip::TagLinkType},
    {"Linked Object Identifier", kmip::TagLinkedObjectIdentifier},
    {"MAC/Signature", kmip::TagMACSignature},
    {"MAC/Signature Key Information", kmip::TagMACSignatureKeyInformation},
    {"Maximum Items", kmip::TagMaximumItems},
    {"Maximum Response Size", kmip::TagMaximumResponseSize},
    {"Message Extension ", kmip::TagMessageExtension},
    {"Modulus", kmip::TagModulus},
    {"Name", kmip::TagName},
    {"Name Type", kmip::TagNameType},
    {"Name Value", kmip::TagNameValue},
    {"Object Group", kmip::TagObjectGroup},
    {"Object Type", kmip::TagObjectType},
    {"Offset", kmip::TagOffset},
    {"Opaque Data Type", kmip::TagOpaqueDataType},
    {"Opaque Data Value", kmip::TagOpaqueDataValue},
    {"Opaque Object", kmip::TagOpaqueObject},
    {"Operation ", kmip::TagOperation},
    {"Operation Policy Name", kmip::TagOperationPolicyName},
    {"P", kmip::TagP},
    {"Padding Method", kmip::TagPaddingMethod},
    {"Prime Exponent P", kmip::TagPrimeExponentP},
    {"Prime Exponent Q", kmip::TagPrimeExponentQ},
    {"Prime Field Size", kmip::TagPrimeFieldSize},
    {"Private Exponent", kmip::TagPrivateExponent},
    {"Private Key", kmip::TagPrivateKey},
    {"Private Key Template-Attribute", kmip::TagPrivateKeyTemplateAttribute},
    {"Private Key Unique Identifier", kmip::TagPrivateKeyUniqueIdentifier},
    {"Process Start Date", kmip::TagProcessStartDate},
    {"Protect Stop Date", kmip::TagProtectStopDate},
    {"Protocol Version", kmip::TagProtocolVersion},
    {"Protocol Version Major", kmip::TagProtocolVersionMajor},
    {"Protocol Version Minor", kmip::TagProtocolVersionMinor},
    {"Public Exponent", kmip::TagPublicExponent},
    {"Public Key", kmip::TagPublicKey},
    {"Public Key Template-Attribute", kmip::TagPublicKeyTemplateAttribute},
    {"Public Key Unique Identifier", kmip::TagPublicKeyUniqueIdentifier},
    {"Put Function ", kmip::TagPutFunction},
    {"Q", kmip::TagQ},
    {"Q String", kmip::TagQString},
    {"Qlength", kmip::TagQlength},
    {"Query Function", kmip::TagQueryFunction},
    {"Recommended Curve", kmip::TagRecommendedCurve},
    {"Replaced Unique Identifier", kmip::TagReplacedUniqueIdentifier},
    {"Request Header", kmip::TagRequestHeader},
    {"Request Message", kmip::TagRequestMessage},
    {"Request Payload", kmip::TagRequestPayload},
    {"Response Header", kmip::TagResponseHeader},
    {"Response Message", kmip::TagResponseMessage},
    {"Response Payload", kmip::TagResponsePayload},
    {"Result Message", kmip::TagResultMessage},
    {"Result Reason", kmip::TagResultReason},
    {"Result Status", kmip::TagResultStatus},
    {"Revocation Message", kmip::TagRevocationMessage},
    {"Revocation Reason", kmip::TagRevocationReason},
    {"Revocation Reason Code", kmip::TagRevocationReasonCode},
    {"Key Role Type", kmip::TagKeyRoleType},
    {"Salt", kmip::TagSalt},
    {"Secret Data", kmip::TagSecretData},
    {"Secret Data Type", kmip::TagSecretDataType},
    {"Serial Number", kmip::TagSerialNumber},
    {"Server Information", kmip::TagServerInformation},
    {"Split Key", kmip::TagSplitKey},
    {"Split Key Method", kmip::TagSplitKeyMethod},
    {"Split Key Parts", kmip::TagSplitKeyParts},
    {"Split Key Threshold", kmip::TagSplitKeyThreshold},
    {"State", kmip::TagState},
    {"Storage Status Mask", kmip::TagStorageStatusMask},
    {"Symmetric Key", kmip::TagSymmetricKey},
    {"Template", kmip::TagTemplate},
    {"Template-Attribute", kmip::TagTemplateAttribute},
    {"Time Stamp", kmip::TagTimeStamp},
    {"Unique Batch Item ID", kmip::TagUniqueBatchItemID},
    {"Unique Identifier", kmip::TagUniqueIdentifier},
    {"Usage Limits", kmip::TagUsageLimits},
    {"Usage Limits Count", kmip::TagUsageLimitsCount},
    {"Usage Limits Total", kmip::TagUsageLimitsTotal},
    {"Usage Limits Unit", kmip::TagUsageLimitsUnit},
    {"Username", kmip::TagUsername},
    {"Validity Date", kmip::TagValidityDate},
    {"Validity Indicator", kmip::TagValidityIndicator},
    {"Vendor Extension ", kmip::TagVendorExtension},
    {"Vendor Identification", kmip::TagVendorIdentification},
    {"Wrapping Method", kmip::TagWrappingMethod},
    {"X", kmip::TagX},
    {"Y", kmip::TagY},
    {"Password", kmip::TagPassword},
    {"Device Identifier", kmip::TagDeviceIdentifier},
    {"Encoding Option", kmip::TagEncodingOption},
    {"Extension Information", kmip::TagExtensionInformation},
    {"Extension Name", kmip::TagExtensionName},
    {"Extension Tag", kmip::TagExtensionTag},
    {"Extension Type", kmip::TagExtensionType},
    {"Fresh", kmip::TagFresh},
    {"Machine Identifier", kmip::TagMachineIdentifier},
    {"Media Identifier", kmip::TagMediaIdentifier},
    {"Network Identifier", kmip::TagNetworkIdentifier},
    {"Object Group Member", kmip::TagObjectGroupMember},
    {"Certificate Length", kmip::TagCertificateLength},
    {"Digital Signature Algorithm", kmip::TagDigitalSignatureAlgorithm},
    {"Certificate Serial Number", kmip::TagCertificateSerialNumber},
    {"Device Serial Number", kmip::TagDeviceSerialNumber},
    {"Issuer Alternative Name", kmip::TagIssuerAlternativeName},
    {"Issuer Distinguished Name", kmip::TagIssuerDistinguishedName},
    {"Subject Alternative Name", kmip::TagSubjectAlternativeName},
    {"Subject Distinguished Name", kmip::TagSubjectDistinguishedName},
    {"X.509 Certificate Identifier", kmip::TagX509CertificateIdentifier},
    {"X.509 Certificate Issuer", kmip::TagX509CertificateIssuer},
    {"X.509 Certificate Subject", kmip::TagX509CertificateSubject},
    {"Key Value Location", kmip::TagKeyValueLocation},
    {"Key Value Location Value", kmip::TagKeyValueLocationValue},
    {"Key Value Location Type", kmip::TagKeyValueLocationType},
    {"Key Value Present", kmip::TagKeyValuePresent},
    {"Original Creation Date", kmip::TagOriginalCreationDate},
    {"PGP Key", kmip::TagPGPKey},
    {"PGP Key Version", kmip::TagPGPKeyVersion},
    {"Alternative Name", kmip::TagAlternativeName},
    {"Alternative Name Value", kmip::TagAlternativeNameValue},
    {"Alternative Name Type", kmip::TagAlternativeNameType},
    {"Data", kmip::TagData},
    {"Signature Data", kmip::TagSignatureData},
    {"Data Length", kmip::TagDataLength},
    {"Random IV", kmip::TagRandomIV},
    {"MAC Data", kmip::TagMACData},
    {"Attestation Type", kmip::TagAttestationType},
    {"Nonce", kmip::TagNonce},
    {"Nonce ID", kmip::TagNonceID},
    {"Nonce Value", kmip::TagNonceValue},
    {"Attestation Measurement", kmip::TagAttestationMeasurement},
    {"Attestation Assertion", kmip::TagAttestationAssertion},
    {"IV Length", kmip::TagIVLength},
    {"Tag Length", kmip::TagTagLength},
    {"Fixed Field Length", kmip::TagFixedFieldLength},
    {"Counter Length", kmip::TagCounterLength},
    {"Initial Counter Value", kmip::TagInitialCounterValue},
    {"Invocation Field Length", kmip::TagInvocationFieldLength},
    {"Attestation Capable Indicator", kmip::TagAttestationCapableIndicator},
    {"Offset Items", kmip::TagOffsetItems},
    {"Located Items", kmip::TagLocatedItems},
    {"Correlation Value", kmip::TagCorrelationValue},
    {"Init Indicator", kmip::TagInitIndicator},
    {"Final Indicator", kmip::TagFinalIndicator},
    {"RNG Parameters", kmip::TagRNGParameters},
    {"RNG Algorithm", kmip::TagRNGAlgorithm},
    {"DRBG Algorithm", kmip::TagDRBGAlgorithm},
    {"FIPS186 Variation", kmip::TagFIPS186Variation},
    {"Prediction Resistance", kmip::TagPredictionResistance},
    {"Random Number Generator", kmip::TagRandomNumberGenerator},
    {"Validation Information", kmip::TagValidationInformation},
    {"Validation Authority Type", kmip::TagValidationAuthorityType},
    {"Validation Authority Country", kmip::TagValidationAuthorityCountry},
    {"Validation Authority URI", kmip::TagValidationAuthorityURI},
    {"Validation Version Major", kmip::TagValidationVersionMajor},
    {"Validation Version Minor", kmip::TagValidationVersionMinor},
    {"Validation Type", kmip::TagValidationType},
    {"Validation Level", kmip::TagValidationLevel},
    {"Validation Certificate Identifier", kmip::TagValidationCertificateIdentifier},
    {"Validation Certificate URI", kmip::TagValidationCertificateURI},
    {"Validation Vendor URI", kmip::TagValidationVendorURI},
    {"Validation Profile", kmip::TagValidationProfile},
    {"Profile Information", kmip::TagProfileInformation},
    {"Profile Name", kmip::TagProfileName},
    {"Server URI", kmip::TagServerURI},
    {"Server Port", kmip::TagServerPort},
    {"Streaming Capability", kmip::TagStreamingCapability},
    {"Asynchronous Capability", kmip::TagAsynchronousCapability},
    {"Attestation Capability", kmip::TagAttestationCapability},
    {"Unwrap Mode", kmip::TagUnwrapMode},
    {"Destroy Action", kmip::TagDestroyAction},
    {"Shredding Algorithm", kmip::TagShreddingAlgorithm},
    {"RNG Mode", kmip::TagRNGMode},
    {"Client Registration Method", kmip::TagClientRegistrationMethod},
    {"Capability Information", kmip::TagCapabilityInformation},
    {"Key Wrap Type", kmip::TagKeyWrapType},
    {"Batch Undo Capability", kmip::TagBatchUndoCapability},
    {"Batch Continue Capability", kmip::TagBatchContinueCapability},
    {"PKCS#12 Friendly Name", kmip::TagPKCS_12FriendlyName},
    {"Description", kmip::TagDescription},
    {"Comment", kmip::TagComment},
    {"Authenticated Encryption Additional Data", kmip::TagAuthenticatedEncryptionAdditionalData},
    {"Authenticated Encryption Tag", kmip::TagAuthenticatedEncryptionTag},
    {"Salt Length", kmip::TagSaltLength},
    {"Mask Generator", kmip::TagMaskGenerator},
    {"Mask Generator Hashing Algorithm", kmip::TagMaskGeneratorHashingAlgorithm},
    {"P Source", kmip::TagPSource},
    {"Trailer Field", kmip::TagTrailerField},
    {"Client Correlation Value", kmip::TagClientCorrelationValue},
    {"Server Correlation Value", kmip::TagServerCorrelationValue},
    {"Digested Data", kmip::TagDigestedData},
    {"Certificate Subject CN", kmip::TagCertificateSubjectCN},
    {"Certificate Subject O", kmip::TagCertificateSubjectO},
    {"Certificate Subject OU", kmip::TagCertificateSubjectOU},
    {"Certificate Subject Email", kmip::TagCertificateSubjectEmail},
    {"Certificate Subject C", kmip::TagCertificateSubjectC},
    {"Certificate Subject ST", kmip::TagCertificateSubjectST},
    {"Certificate Subject L", kmip::TagCertificateSubjectL},
    {"Certificate Subject UID", kmip::TagCertificateSubjectUID},
    {"Certificate Subject Serial Number", kmip::TagCertificateSubjectSerialNumber},
    {"Certificate Subject Title", kmip::TagCertificateSubjectTitle},
    {"Certificate Subject DC", kmip::TagCertificateSubjectDC},
    {"Certificate Subject DN Qualifier", kmip::TagCertificateSubjectDNQualifier},
    {"Certificate Issuer CN", kmip::TagCertificateIssuerCN},
    {"Certificate Issuer O", kmip::TagCertificateIssuerO},
    {"Certificate Issuer OU", kmip::TagCertificateIssuerOU},
    {"Certificate Issuer Email", kmip::TagCertificateIssuerEmail},
    {"Certificate Issuer C", kmip::TagCertificateIssuerC},
    {"Certificate Issuer ST", kmip::TagCertificateIssuerST},
    {"Certificate Issuer L", kmip::TagCertificateIssuerL},
    {"Certificate Issuer UID", kmip::TagCertificateIssuerUID},
    {"Certificate Issuer Serial Number", kmip::TagCertificateIssuerSerialNumber},
    {"Certificate Issuer Title", kmip::TagCertificateIssuerTitle},
    {"Certificate Issuer DC", kmip::TagCertificateIssuerDC},
    {"Certificate Issuer DN Qualifier", kmip::TagCertificateIssuerDNQualifier},
    {"Sensitive", kmip::TagSensitive},
    {"Always Sensitive", kmip::TagAlwaysSensitive},
    {"Extractable", kmip::TagExtractable},
    {"Never Extractable", kmip::TagNeverExtractable},
    {"Replace Existing", kmip::TagReplaceExisting},
};

int KMIPUtils::getTagType(int iTag) {
    int eRet = kmip::TypeUnknown;
    switch (iTag) {
	case kmip::TagActivationDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagApplicationData:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagApplicationNamespace:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagApplicationSpecificInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagArchiveDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagAsynchronousCorrelationValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagAsynchronousIndicator:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagAttribute:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagAttributeIndex:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagAttributeName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagAttributeValue:
	    eRet = kmip::TypeUnknown;
	    break;
	case kmip::TagAuthentication:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagBatchCount:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagBatchErrorContinuationOption:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagBatchItem:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagBatchOrderOption:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagBlockCipherMode:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCancellationResult:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCertificate:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateIdentifier:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateIssuer:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateIssuerAlternativeName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerDistinguishedName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateRequest:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagCertificateRequestType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCertificateSubject:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateSubjectAlternativeName:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateSubjectDistinguishedName:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCertificateType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCertificateValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagCommonTemplateAttribute:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCompromiseDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagCompromiseOccurrenceDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagContactInformation:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCredential:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCredentialType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCredentialValue:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCriticalityIndicator:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagCRTCoefficient:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagCryptographicAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCryptographicDomainParameters:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCryptographicLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagCryptographicParameters:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagCryptographicUsageMask:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagCustomAttribute:
	    eRet = kmip::TypeUnknown;
	    break;
	case kmip::TagD:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagDeactivationDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagDerivationData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagDerivationMethod:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagDerivationParameters:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagDestroyDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagDigest:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagDigestValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagEncryptionKeyInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagG:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagHashingAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagInitialDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagInitializationVector:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagIssuer:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagIterationCount:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagIVCounterNonce:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagJ:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagKey:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagKeyBlock:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagKeyCompressionType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagKeyFormatType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagKeyMaterial:
	    eRet = kmip::TypeUnknown;
	    break;
	case kmip::TagKeyPartIdentifier:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagKeyValue:
	    eRet = kmip::TypeUnknown;
	    break;
	case kmip::TagKeyWrappingData:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagKeyWrappingSpecification:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagLastChangeDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagLeaseTime:
	    eRet = kmip::TypeInterval;
	    break;
	case kmip::TagLink:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagLinkType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagLinkedObjectIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagMACSignature:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagMACSignatureKeyInformation:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagMaximumItems:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagMaximumResponseSize:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagMessageExtension:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagModulus:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagName:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagNameType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagNameValue:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagObjectGroup:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagObjectType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagOffset:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagOpaqueDataType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagOpaqueDataValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagOpaqueObject:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagOperation:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagOperationPolicyName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagP:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPaddingMethod:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagPrimeExponentP:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPrimeExponentQ:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPrimeFieldSize:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPrivateExponent:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPrivateKey:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagPrivateKeyTemplateAttribute:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagPrivateKeyUniqueIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagProcessStartDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagProtectStopDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagProtocolVersion:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagProtocolVersionMajor:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagProtocolVersionMinor:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagPublicExponent:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPublicKey:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagPublicKeyTemplateAttribute:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagPublicKeyUniqueIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagPutFunction:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagQ:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagQString:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagQlength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagQueryFunction:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagRecommendedCurve:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagReplacedUniqueIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagRequestHeader:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagRequestMessage:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagRequestPayload:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagResponseHeader:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagResponseMessage:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagResponsePayload:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagResultMessage:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagResultReason:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagResultStatus:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagRevocationMessage:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagRevocationReason:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagRevocationReasonCode:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagKeyRoleType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagSalt:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagSecretData:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagSecretDataType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagSerialNumber:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagServerInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagSplitKey:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagSplitKeyMethod:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagSplitKeyParts:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagSplitKeyThreshold:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagState:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagStorageStatusMask:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagSymmetricKey:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagTemplate:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagTemplateAttribute:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagTimeStamp:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagUniqueBatchItemID:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagUniqueIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagUsageLimits:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagUsageLimitsCount:
	    eRet = kmip::TypeLongInteger;
	    break;
	case kmip::TagUsageLimitsTotal:
	    eRet = kmip::TypeLongInteger;
	    break;
	case kmip::TagUsageLimitsUnit:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagUsername:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidityDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagValidityIndicator:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagVendorExtension:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagVendorIdentification:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagWrappingMethod:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagX:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagY:
	    eRet = kmip::TypeBigInteger;
	    break;
	case kmip::TagPassword:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagDeviceIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagEncodingOption:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagExtensionInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagExtensionName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagExtensionTag:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagExtensionType:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagFresh:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagMachineIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagMediaIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagNetworkIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagObjectGroupMember:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCertificateLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagDigitalSignatureAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCertificateSerialNumber:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagDeviceSerialNumber:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagIssuerAlternativeName:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagIssuerDistinguishedName:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagSubjectAlternativeName:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagSubjectDistinguishedName:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagX509CertificateIdentifier:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagX509CertificateIssuer:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagX509CertificateSubject:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagKeyValueLocation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagKeyValueLocationValue:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagKeyValueLocationType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagKeyValuePresent:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagOriginalCreationDate:
	    eRet = kmip::TypeDateTime;
	    break;
	case kmip::TagPGPKey:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagPGPKeyVersion:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagAlternativeName:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagAlternativeNameValue:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagAlternativeNameType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagSignatureData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagDataLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagRandomIV:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagMACData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagAttestationType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagNonce:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagNonceID:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagNonceValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagAttestationMeasurement:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagAttestationAssertion:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagIVLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagTagLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagFixedFieldLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagCounterLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagInitialCounterValue:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagInvocationFieldLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagAttestationCapableIndicator:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagOffsetItems:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagLocatedItems:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagCorrelationValue:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagInitIndicator:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagFinalIndicator:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagRNGParameters:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagRNGAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagDRBGAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagFIPS186Variation:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagPredictionResistance:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagRandomNumberGenerator:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagValidationInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagValidationAuthorityType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagValidationAuthorityCountry:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidationAuthorityURI:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidationVersionMajor:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagValidationVersionMinor:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagValidationType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagValidationLevel:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagValidationCertificateIdentifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidationCertificateURI:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidationVendorURI:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagValidationProfile:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagProfileInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagProfileName:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagServerURI:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagServerPort:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagStreamingCapability:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagAsynchronousCapability:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagAttestationCapability:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagUnwrapMode:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagDestroyAction:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagShreddingAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagRNGMode:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagClientRegistrationMethod:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagCapabilityInformation:
	    eRet = kmip::TypeStructure;
	    break;
	case kmip::TagKeyWrapType:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagBatchUndoCapability:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagBatchContinueCapability:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagPKCS_12FriendlyName:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagDescription:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagComment:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagAuthenticatedEncryptionAdditionalData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagAuthenticatedEncryptionTag:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagSaltLength:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagMaskGenerator:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagMaskGeneratorHashingAlgorithm:
	    eRet = kmip::TypeEnumeration;
	    break;
	case kmip::TagPSource:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagTrailerField:
	    eRet = kmip::TypeInteger;
	    break;
	case kmip::TagClientCorrelationValue:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagServerCorrelationValue:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagDigestedData:
	    eRet = kmip::TypeByteString;
	    break;
	case kmip::TagCertificateSubjectCN:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectO:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectOU:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectEmail:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectC:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectST:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectL:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectUID:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectSerialNumber:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectTitle:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectDC:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateSubjectDNQualifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerCN:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerO:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerOU:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerEmail:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerC:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerST:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerL:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerUID:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerSerialNumber:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerTitle:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerDC:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagCertificateIssuerDNQualifier:
	    eRet = kmip::TypeTextString;
	    break;
	case kmip::TagSensitive:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagAlwaysSensitive:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagExtractable:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagNeverExtractable:
	    eRet = kmip::TypeBoolean;
	    break;
	case kmip::TagReplaceExisting:
	    eRet = kmip::TypeBoolean;
	    break;
	default:
	    break;
    }

    return eRet;
}
