#include "KMIPEnumFactory.h"
#include "KMIPEnumeration.h"

KMIPFieldUP KMIPEnumFactory::createField(int iTag) const {
    return createEnumeration(iTag);
}

KMIPEnumerationUP KMIPEnumFactory::createEnumeration(int iTag, uint32_t eValue) const {
    KMIPEnumerationUP upke;
    switch(iTag) {
        case kmip::TagCredentialType:
            upke.reset(new KMIPCredentialType(eValue));
            break;
        case kmip::TagKeyCompressionType:
            upke.reset(new KMIPKeyCompressionType(eValue));
            break;
        case kmip::TagKeyFormatType:
            upke.reset(new KMIPKeyFormatType(eValue));
            break;
        case kmip::TagWrappingMethod:
            upke.reset(new KMIPWrappingMethod(eValue));
            break;
        case kmip::TagRecommendedCurve:
            upke.reset(new KMIPRecommendedCurve(eValue));
            break;
        case kmip::TagCertificateType:
            upke.reset(new KMIPCertificateType(eValue));
            break;
        case kmip::TagDigitalSignatureAlgorithm:
            upke.reset(new KMIPDigitalSignatureAlgorithm(eValue));
            break;
        case kmip::TagSplitKeyMethod:
            upke.reset(new KMIPSplitKeyMethod(eValue));
            break;
        case kmip::TagSecretDataType:
            upke.reset(new KMIPSecretDataType(eValue));
            break;
        case kmip::TagOpaqueDataType:
            upke.reset(new KMIPOpaqueDataType(eValue));
            break;
        case kmip::TagNameType:
            upke.reset(new KMIPNameType(eValue));
            break;
        case kmip::TagObjectType:
            upke.reset(new KMIPObjectType(eValue));
            break;
        case kmip::TagCryptographicAlgorithm:
            upke.reset(new KMIPCryptographicAlgorithm(eValue));
            break;
        case kmip::TagBlockCipherMode:
            upke.reset(new KMIPBlockCipherMode(eValue));
            break;
        case kmip::TagPaddingMethod:
            upke.reset(new KMIPPaddingMethod(eValue));
            break;
        case kmip::TagHashingAlgorithm:
            upke.reset(new KMIPHashingAlgorithm(eValue));
            break;
        case kmip::TagKeyRoleType:
            upke.reset(new KMIPKeyRoleType(eValue));
            break;
        case kmip::TagState:
            upke.reset(new KMIPState(eValue));
            break;
        case kmip::TagRevocationReasonCode:
            upke.reset(new KMIPRevocationReasonCode(eValue));
            break;
        case kmip::TagLinkType:
            upke.reset(new KMIPLinkType(eValue));
            break;
        case kmip::TagDerivationMethod:
            upke.reset(new KMIPDerivationMethod(eValue));
            break;
        case kmip::TagCertificateRequestType:
            upke.reset(new KMIPCertificateRequestType(eValue));
            break;
        case kmip::TagValidityIndicator:
            upke.reset(new KMIPValidityIndicator(eValue));
            break;
        case kmip::TagQueryFunction:
            upke.reset(new KMIPQueryFunction(eValue));
            break;
        case kmip::TagCancellationResult:
            upke.reset(new KMIPCancellationResult(eValue));
            break;
        case kmip::TagPutFunction:
            upke.reset(new KMIPPutFunction(eValue));
            break;
        case kmip::TagOperation:
            upke.reset(new KMIPOperation(eValue));
            break;
        case kmip::TagResultStatus:
            upke.reset(new KMIPResultStatus(eValue));
            break;
        case kmip::TagResultReason:
            upke.reset(new KMIPResultReason(eValue));
            break;
        case kmip::TagBatchErrorContinuationOption:
            upke.reset(new KMIPBatchErrorContinuationOption(eValue));
            break;
        case kmip::TagUsageLimitsUnit:
            upke.reset(new KMIPUsageLimitsUnit(eValue));
            break;
        case kmip::TagEncodingOption:
            upke.reset(new KMIPEncodingOption(eValue));
            break;
        case kmip::TagObjectGroupMember:
            upke.reset(new KMIPObjectGroupMember(eValue));
            break;
        case kmip::TagAlternativeNameType:
            upke.reset(new KMIPAlternativeNameType(eValue));
            break;
        case kmip::TagKeyValueLocationType:
            upke.reset(new KMIPKeyValueLocationType(eValue));
            break;
        case kmip::TagAttestationType:
            upke.reset(new KMIPAttestationType(eValue));
            break;
        case kmip::TagRNGAlgorithm:
            upke.reset(new KMIPRNGAlgorithm(eValue));
            break;
        case kmip::TagDRBGAlgorithm:
            upke.reset(new KMIPDRBGAlgorithm(eValue));
            break;
        case kmip::TagFIPS186Variation:
            upke.reset(new KMIPFIPS186Variation(eValue));
            break;
        case kmip::TagValidationAuthorityType:
            upke.reset(new KMIPValidationAuthorityType(eValue));
            break;
        case kmip::TagValidationType:
            upke.reset(new KMIPValidationType(eValue));
            break;
        case kmip::TagProfileName:
            upke.reset(new KMIPProfileName(eValue));
            break;
        case kmip::TagUnwrapMode:
            upke.reset(new KMIPUnwrapMode(eValue));
            break;
        case kmip::TagDestroyAction:
            upke.reset(new KMIPDestroyAction(eValue));
            break;
        case kmip::TagShreddingAlgorithm:
            upke.reset(new KMIPShreddingAlgorithm(eValue));
            break;
        case kmip::TagRNGMode:
            upke.reset(new KMIPRNGMode(eValue));
            break;
        case kmip::TagClientRegistrationMethod:
            upke.reset(new KMIPClientRegistrationMethod(eValue));
            break;
        case kmip::TagKeyWrapType:
            upke.reset(new KMIPKeyWrapType(eValue));
            break;
        case kmip::TagMaskGenerator:
            upke.reset(new KMIPMaskGenerator(eValue));
            break;
        default:
            upke.reset(new KMIPEnumeration(iTag, eValue));
            break;
    }
    
    return upke;
}

