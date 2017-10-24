#include "KMIPEnumeration.h"
#include <openssl/obj_mac.h>

KMIPEnumeration::KMIPEnumeration(int iTag, uint32_t eValue, uint32_t eFirst, uint32_t eLast) : KMIPNumber(iTag, kmip::TypeEnumeration, eValue) {
    this->eFirst = eFirst;
    this->eLast = eLast;
}

bool KMIPEnumeration::isValid(uint32_t uiVal) const {
    return eFirst <= uiVal && uiVal <= eLast;
}

bool KMIPEnumeration::isValid() const {
    return KMIPNumber::isValid() && isValid(getValue());
}

std::string KMIPEnumeration::getValueName() const {
    return "";
}

bool KMIPEnumeration::setValueFromName(const std::string &sName) {
    return false;
}

bool KMIPEnumeration::setValueFromXML(const std::string &sValue) {
    return setValueFromName(sValue) || KMIPNumber::setValueFromXML(sValue);
}

std::string KMIPEnumeration::getXMLValue() const {
    std::string sRet = getValueName();
    if (sRet.empty()) {
        sRet = KMIPNumber::getXMLValue();
    }

    return sRet;
}

KMIPCredentialType::KMIPCredentialType(uint32_t eValue) : KMIPEnumeration(kmip::TagCredentialType, eValue, KMIPCredentialType::UsernameAndPassword, KMIPCredentialType::Attestation) {}


IMPLEMENT_ENUM_TO_STRING(KMIPCredentialType, VALUE, Unknown, "", CREDENTIAL_TYPE_LIST);



KMIPKeyCompressionType::KMIPKeyCompressionType(uint32_t eValue) : KMIPEnumeration(kmip::TagKeyCompressionType, eValue, KMIPKeyCompressionType::Unknown, KMIPKeyCompressionType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPKeyCompressionType, VALUE, Unknown, "", KEY_COMPRESSION_TYPE_LIST);

KMIPKeyFormatType::KMIPKeyFormatType(uint32_t eValue) : KMIPEnumeration(kmip::TagKeyFormatType, eValue, KMIPKeyFormatType::Unknown, KMIPKeyFormatType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPKeyFormatType, VALUE, Unknown, "", KEY_FORMAT_TYPE_LIST);

KMIPWrappingMethod::KMIPWrappingMethod(uint32_t eValue) : KMIPEnumeration(kmip::TagWrappingMethod, eValue, KMIPWrappingMethod::Unknown, KMIPWrappingMethod::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPWrappingMethod, VALUE, Unknown, "", WRAPPING_METHOD_LIST);

KMIPRecommendedCurve::KMIPRecommendedCurve(uint32_t eValue) : KMIPEnumeration(kmip::TagRecommendedCurve, eValue, KMIPRecommendedCurve::Unknown, KMIPRecommendedCurve::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPRecommendedCurve, VALUE, Unknown, "", RECOMMENDED_CURVE_LIST);

int KMIPRecommendedCurve::CurveToNID(uint32_t eValue) {
    int iRet = Unknown;
#if 0
    switch (eValue) {
        case P_192:
            iRet = NID_p

    b(K_163,0x2) \
    b(B_163,0x3) \
    b(P_224,0x4) \
    b(K_233,0x5) \
    b(B_233,0x6) \
    b(P_256,0x7) \
    b(K_283,0x8) \
    b(B_283,0x9) \
    b(P_384,0x0000000A) \
    b(K_409,0x0000000B) \
    b(B_409,0x0000000C) \
    b(P_521,0x0000000D) \
    b(K_571,0x0000000E) \
    b(B_571,0x0000000F) \
    b(SECP112R1,0x10) \
    b(SECP112R2,0x11) \
    b(SECP128R1,0x12) \
    b(SECP128R2,0x13) \
    b(SECP160K1,0x14) \
    b(SECP160R1,0x15) \
    b(SECP160R2,0x16) \
    b(SECP160K1ECP192K1,0x17) \
    b(SECP224K1,0x18) \
    b(SECP256K1,0x19) \
    b(SECT113R1,0x0000001A) \
    b(SECT113R2,0x0000001B) \
    b(SECT131R1,0x0000001C) \
    b(SECT131R2,0x0000001D) \
    b(SECT163R1,0x0000001E) \
    b(SECT193R1,0x0000001C0001F) \
    b(SECT193R2,0x20) \
    b(SECT239K1,0x21) \
    b(ANSIX9P192V2,0x22) \
    b(ANSIX9P192V3,0x23) \
    b(ANSIX9P239V1,0x24) \
    b(ANSIX9P239V2,0x225) \
    b(ANSIX9P239V3,0x26) \
    b(ANSIX9C2PNB163V1,0x27) \
    b(ANSIX9C2PNB163V2,0x28) \
    b(ANSIX9C2PNB163V3,0x29) \
    b(ANSIX9C2PNB176V1,0x0000002A) \
    b(ANSIX9C2TNB191V1,0x0000002B) \
    b(ANSIX9C2TNB191V2,0x0000002C)      \
    b(ANSIX9C2TNB191V3,0x0000002D) \
    b(ANSIX9C2PNB208W1,0x0000002E) \
    b(ANSIX9C2TNB239V1,0x0000002F) \
    b(ANSIX9C2TNB239V2,0x30) \
    b(ANSIX9C2TNB239V1TNB239V3,0x31) \
    b(ANSIX9C2PNB272W1,0x32) \
    b(ANSIX9C2PNB304W1,0x33) \
    b(ANSIX9C2TNB359V1,0x34) \
    b(ANSIX9C2PNB368W1,0x35) \
    b(ANSIX9C2TNB239V1TNB239V3B431R1,0x36) \
    b(BRAINPOOLP160R1,0x37) \
    b(BRAINPOOLP160T1,0x38) \
    b(BRAINPOOLP192R1,0x39) \
    b(BRAINPOOLP192T1,0x0000003A) \
    b(BRAINPOOLP192R1224R1,0x0000003B) \
    b(BRAINPOOLP224T1,0x0000003C) \
    b(BRAINPOOLP256R1,0x0000003D) \
    b(BRAINPOOLP256T1,0x0000003E) \
    b(BRAINPOOLP320R1,0x0000003C000003F) \
    b(BRAINPOOLP320T1,0x40) \
    b(BRAINPOOLP384R1,0x41) \
    b(BRAINPOOLP320T1NPOOLP384T1,0x42) \
    b(BRAINPOOLP512R1,0x43) \
    b(BRAINPOOLP512T1,0x44) \
    }
#endif
    return iRet;
}

KMIPCertificateType::KMIPCertificateType(uint32_t eValue) : KMIPEnumeration(kmip::TagCertificateType, eValue, KMIPCertificateType::Unknown, KMIPCertificateType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPCertificateType, VALUE, Unknown, "", CERTIFICATE_TYPE_LIST);

KMIPDigitalSignatureAlgorithm::KMIPDigitalSignatureAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagDigitalSignatureAlgorithm, eValue, KMIPDigitalSignatureAlgorithm::Unknown, KMIPDigitalSignatureAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPDigitalSignatureAlgorithm, VALUE, Unknown, "", DIGITAL_SIGNATURE_ALGORITHM_LIST);

KMIPSplitKeyMethod::KMIPSplitKeyMethod(uint32_t eValue) : KMIPEnumeration(kmip::TagSplitKeyMethod, eValue, KMIPSplitKeyMethod::Unknown, KMIPSplitKeyMethod::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPSplitKeyMethod, VALUE, Unknown, "", SPLIT_KEY_METHOD_LIST);

KMIPSecretDataType::KMIPSecretDataType(uint32_t eValue) : KMIPEnumeration(kmip::TagSecretDataType, eValue, KMIPSecretDataType::Unknown, KMIPSecretDataType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPSecretDataType, VALUE, Unknown, "", SECRET_DATA_TYPE_LIST);

KMIPOpaqueDataType::KMIPOpaqueDataType(uint32_t eValue) : KMIPEnumeration(kmip::TagOpaqueDataType, eValue, KMIPOpaqueDataType::Unknown, KMIPOpaqueDataType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPOpaqueDataType, VALUE, Unknown, "", OPAQUE_DATA_TYPE_LIST);

KMIPNameType::KMIPNameType(uint32_t eValue) : KMIPEnumeration(kmip::TagNameType, eValue, KMIPNameType::Unknown, KMIPNameType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPNameType, VALUE, Unknown, "", NAME_TYPE_LIST);

KMIPObjectType::KMIPObjectType(uint32_t eValue) : KMIPEnumeration(kmip::TagObjectType, eValue, KMIPObjectType::Unknown, KMIPObjectType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPObjectType, VALUE, Unknown, "", OBJECT_TYPE_LIST);

KMIPCryptographicAlgorithm::KMIPCryptographicAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagCryptographicAlgorithm, eValue, KMIPCryptographicAlgorithm::Unknown, KMIPCryptographicAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPCryptographicAlgorithm, VALUE, Unknown, "", CRYPTOGRAPHIC_ALGORITHM_LIST);

bool KMIPCryptographicAlgorithm::isFixedLength(uint32_t iAlg) {
    return getCryptoPPAlg(iAlg, MIN_KEYLENGTH) == getCryptoPPAlg(iAlg, MAX_KEYLENGTH);
}

bool KMIPCryptographicAlgorithm::isSymmetric(uint32_t iAlg) {
    return getCryptoPPAlg(iAlg, MAX_KEYLENGTH) > 0;
}

bool KMIPCryptographicAlgorithm::isAsymmetric(uint32_t iAlg) {
    bool bRet = false;
    switch (iAlg) {
        case RSA:
        case DSA:
        case ECDSA:
        case DH:
        case ECDH:
        case ECMQV:
        case EC:
            bRet = true;
            break;
        default:
            break;
    }

    return bRet;
}

KMIPBlockCipherMode::KMIPBlockCipherMode(uint32_t eValue) : KMIPEnumeration(kmip::TagBlockCipherMode, eValue, KMIPBlockCipherMode::Unknown, KMIPBlockCipherMode::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPBlockCipherMode, VALUE, Unknown, "", BLOCK_CIPHER_MODE_LIST);

KMIPPaddingMethod::KMIPPaddingMethod(uint32_t eValue) : KMIPEnumeration(kmip::TagPaddingMethod, eValue, KMIPPaddingMethod::Unknown, KMIPPaddingMethod::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPPaddingMethod, VALUE, Unknown, "", PADDING_METHOD_LIST);

KMIPHashingAlgorithm::KMIPHashingAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagHashingAlgorithm, eValue, KMIPHashingAlgorithm::Unknown, KMIPHashingAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPHashingAlgorithm, VALUE, Unknown, "", HASHING_ALGORITHM_LIST);

KMIPKeyRoleType::KMIPKeyRoleType(uint32_t eValue) : KMIPEnumeration(kmip::TagKeyRoleType, eValue, KMIPKeyRoleType::Unknown, KMIPKeyRoleType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPKeyRoleType, VALUE, Unknown, "", KEY_ROLE_TYPE_LIST);

KMIPState::KMIPState(uint32_t eValue) : KMIPEnumeration(kmip::TagState, eValue, KMIPState::Unknown, KMIPState::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPState, VALUE, Unknown, "", STATE_LIST);

KMIPRevocationReasonCode::KMIPRevocationReasonCode(uint32_t eValue) : KMIPEnumeration(kmip::TagRevocationReasonCode, eValue, KMIPRevocationReasonCode::Unknown, KMIPRevocationReasonCode::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPRevocationReasonCode, VALUE, Unknown, "", REVOCATION_REASON_CODE_LIST);

KMIPLinkType::KMIPLinkType(uint32_t eValue) : KMIPEnumeration(kmip::TagLinkType, eValue, KMIPLinkType::Unknown, KMIPLinkType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPLinkType, VALUE, Unknown, "", LINK_TYPE_LIST);

KMIPDerivationMethod::KMIPDerivationMethod(uint32_t eValue) : KMIPEnumeration(kmip::TagDerivationMethod, eValue, KMIPDerivationMethod::Unknown, KMIPDerivationMethod::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPDerivationMethod, VALUE, Unknown, "", DERIVATION_METHOD_LIST);

KMIPCertificateRequestType::KMIPCertificateRequestType(uint32_t eValue) : KMIPEnumeration(kmip::TagCertificateRequestType, eValue, KMIPCertificateRequestType::Unknown, KMIPCertificateRequestType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPCertificateRequestType, VALUE, Unknown, "", CERTIFICATE_REQUEST_TYPE_LIST);

KMIPValidityIndicator::KMIPValidityIndicator(uint32_t eValue) : KMIPEnumeration(kmip::TagValidityIndicator, eValue, KMIPValidityIndicator::Valid, KMIPValidityIndicator::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPValidityIndicator, VALUE, Unknown, "", VALIDITY_INDICATOR_LIST);

KMIPQueryFunction::KMIPQueryFunction(uint32_t eValue) : KMIPEnumeration(kmip::TagQueryFunction, eValue, KMIPQueryFunction::Unknown, KMIPQueryFunction::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPQueryFunction, VALUE, Unknown, "", QUERY_FUNCTION_LIST);

KMIPCancellationResult::KMIPCancellationResult(uint32_t eValue) : KMIPEnumeration(kmip::TagCancellationResult, eValue, KMIPCancellationResult::Unknown, KMIPCancellationResult::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPCancellationResult, VALUE, Unknown, "", CANCELLATION_RESULT_LIST);

KMIPPutFunction::KMIPPutFunction(uint32_t eValue) : KMIPEnumeration(kmip::TagPutFunction, eValue, KMIPPutFunction::Unknown, KMIPPutFunction::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPPutFunction, VALUE, Unknown, "", PUT_FUNCTION_LIST);

KMIPOperation::KMIPOperation(uint32_t eValue) : KMIPEnumeration(kmip::TagOperation, eValue, KMIPOperation::Unknown, KMIPOperation::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPOperation, VALUE, Unknown, "", OPERATION_LIST);

KMIPResultStatus::KMIPResultStatus(uint32_t eValue) : KMIPEnumeration(kmip::TagResultStatus, eValue, KMIPResultStatus::Success, KMIPResultStatus::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPResultStatus, VALUE, Success, "", RESULT_STATUS_LIST);

KMIPResultReason::KMIPResultReason(uint32_t eValue) : KMIPEnumeration(kmip::TagResultReason, eValue, KMIPResultReason::Unknown, KMIPResultReason::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPResultReason, VALUE, Unknown, "", RESULT_REASON_LIST);

KMIPBatchErrorContinuationOption::KMIPBatchErrorContinuationOption(uint32_t eValue) : KMIPEnumeration(kmip::TagBatchErrorContinuationOption, eValue, KMIPBatchErrorContinuationOption::Unknown, KMIPBatchErrorContinuationOption::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPBatchErrorContinuationOption, VALUE, Unknown, "", BATCH_ERROR_CONTINUATION_OPTION_LIST);

KMIPUsageLimitsUnit::KMIPUsageLimitsUnit(uint32_t eValue) : KMIPEnumeration(kmip::TagUsageLimitsUnit, eValue, KMIPUsageLimitsUnit::Unknown, KMIPUsageLimitsUnit::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPUsageLimitsUnit, VALUE, Unknown, "", USAGE_LIMITS_UNIT_LIST);

KMIPEncodingOption::KMIPEncodingOption(uint32_t eValue) : KMIPEnumeration(kmip::TagEncodingOption, eValue, KMIPEncodingOption::Unknown, KMIPEncodingOption::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPEncodingOption, VALUE, Unknown, "", ENCODING_OPTION_LIST);

KMIPObjectGroupMember::KMIPObjectGroupMember(uint32_t eValue) : KMIPEnumeration(kmip::TagObjectGroupMember, eValue, KMIPObjectGroupMember::Unknown, KMIPObjectGroupMember::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPObjectGroupMember, VALUE, Unknown, "", OBJECT_GROUP_MEMBER_LIST);

KMIPAlternativeNameType::KMIPAlternativeNameType(uint32_t eValue) : KMIPEnumeration(kmip::TagAlternativeNameType, eValue, KMIPAlternativeNameType::Unknown, KMIPAlternativeNameType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPAlternativeNameType, VALUE, Unknown, "", ALTERNATIVE_NAME_TYPE_LIST);

KMIPKeyValueLocationType::KMIPKeyValueLocationType(uint32_t eValue) : KMIPEnumeration(kmip::TagKeyValueLocationType, eValue, KMIPKeyValueLocationType::Unknown, KMIPKeyValueLocationType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPKeyValueLocationType, VALUE, Unknown, "", KEY_VALUE_LOCATION_TYPE_LIST);

KMIPAttestationType::KMIPAttestationType(uint32_t eValue) : KMIPEnumeration(kmip::TagAttestationType, eValue, KMIPAttestationType::Unknown, KMIPAttestationType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPAttestationType, VALUE, Unknown, "", ATTESTATION_TYPE_LIST);

KMIPRNGAlgorithm::KMIPRNGAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagRNGAlgorithm, eValue, KMIPRNGAlgorithm::Unknown, KMIPRNGAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPRNGAlgorithm, VALUE, Unknown, "", RNG_ALGORITHM_LIST);

KMIPDRBGAlgorithm::KMIPDRBGAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagDRBGAlgorithm, eValue, KMIPDRBGAlgorithm::Unknown, KMIPDRBGAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPDRBGAlgorithm, VALUE, Unknown, "", DRBG_ALGORITHM_LIST);

KMIPFIPS186Variation::KMIPFIPS186Variation(uint32_t eValue) : KMIPEnumeration(kmip::TagFIPS186Variation, eValue, KMIPFIPS186Variation::Unknown, KMIPFIPS186Variation::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPFIPS186Variation, VALUE, Unknown, "", FIPS186VARIATION_LIST);

KMIPValidationAuthorityType::KMIPValidationAuthorityType(uint32_t eValue) : KMIPEnumeration(kmip::TagValidationAuthorityType, eValue, KMIPValidationAuthorityType::Unknown, KMIPValidationAuthorityType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPValidationAuthorityType, VALUE, Unknown, "", VALIDATION_AUTHORITY_TYPE_LIST);

KMIPValidationType::KMIPValidationType(uint32_t eValue) : KMIPEnumeration(kmip::TagValidationType, eValue, KMIPValidationType::Unknown, KMIPValidationType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPValidationType, VALUE, Unknown, "", VALIDATION_TYPE_LIST);

KMIPProfileName::KMIPProfileName(uint32_t eValue) : KMIPEnumeration(kmip::TagProfileName, eValue, KMIPProfileName::Unknown, KMIPProfileName::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPProfileName, VALUE, Unknown, "", PROFILE_NAME_LIST);

KMIPUnwrapMode::KMIPUnwrapMode(uint32_t eValue) : KMIPEnumeration(kmip::TagUnwrapMode, eValue, KMIPUnwrapMode::Unknown, KMIPUnwrapMode::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPUnwrapMode, VALUE, Unknown, "", UNWRAP_MODE_LIST);

KMIPDestroyAction::KMIPDestroyAction(uint32_t eValue) : KMIPEnumeration(kmip::TagDestroyAction, eValue, KMIPDestroyAction::Unknown, KMIPDestroyAction::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPDestroyAction, VALUE, Unknown, "", DESTROY_ACTION_LIST);

KMIPShreddingAlgorithm::KMIPShreddingAlgorithm(uint32_t eValue) : KMIPEnumeration(kmip::TagShreddingAlgorithm, eValue, KMIPShreddingAlgorithm::Unknown, KMIPShreddingAlgorithm::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPShreddingAlgorithm, VALUE, Unknown, "", SHREDDING_ALGORITHM_LIST);

KMIPRNGMode::KMIPRNGMode(uint32_t eValue) : KMIPEnumeration(kmip::TagRNGMode, eValue, KMIPRNGMode::Unknown, KMIPRNGMode::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPRNGMode, VALUE, Unknown, "", RNG_MODE_LIST);

KMIPClientRegistrationMethod::KMIPClientRegistrationMethod(uint32_t eValue) : KMIPEnumeration(kmip::TagClientRegistrationMethod, eValue, KMIPClientRegistrationMethod::Unknown, KMIPClientRegistrationMethod::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPClientRegistrationMethod, VALUE, Unknown, "", CLIENT_REGISTRATION_METHOD_LIST);

KMIPKeyWrapType::KMIPKeyWrapType(uint32_t eValue) : KMIPEnumeration(kmip::TagKeyWrapType, eValue, KMIPKeyWrapType::Unknown, KMIPKeyWrapType::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPKeyWrapType, VALUE, Unknown, "", KEY_WRAP_TYPE_LIST);

KMIPMaskGenerator::KMIPMaskGenerator(uint32_t eValue) : KMIPEnumeration(kmip::TagMaskGenerator, eValue, KMIPMaskGenerator::Unknown, KMIPMaskGenerator::NumValues) {}
IMPLEMENT_ENUM_TO_STRING(KMIPMaskGenerator, VALUE, Unknown, "", MASK_GENERATOR_LIST);
