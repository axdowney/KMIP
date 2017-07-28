/* Copyright (C) 2017 Alexander Downey */

#include "KMIPFieldOrders.h"
#include "KMIPDefs.h"
#include "KMIPEnumeration.h"

KMIPFieldOrders::KMIPFieldOrders() {
    mapKFOs = {
        {kmip::TagAttribute, {{0, {
                KMIPFieldOrderItem(kmip::TagAttributeName, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagAttributeIndex, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagAttributeValue, kmip::TypeUnknown)
        }}}},
        {kmip::TagCryptographicParameters, {{0, {
                KMIPFieldOrderItem(kmip::TagBlockCipherMode, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagPaddingMethod, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagHashingAlgorithm, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagKeyRoleType, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagDigitalSignatureAlgorithm, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagCryptographicAlgorithm, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagRandomIV, kmip::TypeBoolean),
                KMIPFieldOrderItem(kmip::TagIVLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagTagLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagFixedFieldLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagInvocationFieldLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagCounterLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagInitialCounterValue, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagSaltLength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagMaskGenerator, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagMaskGeneratorHashingAlgorithm, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagPSource, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagTrailerField, kmip::TypeInteger),
        }}}},
        {kmip::TagCryptographicDomainParameters, {{0, {
                KMIPFieldOrderItem(kmip::TagQlength, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagRecommendedCurve, kmip::TypeEnumeration),
        }}}},
        {kmip::TagX509CertificateIdentifier, {{0, {
                        KMIPFieldOrderItem(kmip::TagIssuerDistinguishedName, kmip::TypeByteString, 1),
                        KMIPFieldOrderItem(kmip::TagCertificateSerialNumber, kmip::TypeByteString, 1),
        }}}},
        {kmip::TagX509CertificateSubject, {{0, {
                KMIPFieldOrderItem(kmip::TagSubjectDistinguishedName, kmip::TypeByteString, 1),
                KMIPFieldOrderItem(kmip::TagSubjectAlternativeName, kmip::TypeByteString),
        }}}},
        {kmip::TagX509CertificateIssuer, {{0, {
                KMIPFieldOrderItem(kmip::TagIssuerDistinguishedName, kmip::TypeByteString, 1),
                KMIPFieldOrderItem(kmip::TagIssuerAlternativeName, kmip::TypeByteString),
        }}}},
        {kmip::TagCertificateIdentifier, {{0, {
                KMIPFieldOrderItem(kmip::TagIssuer, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagSerialNumber, kmip::TypeTextString),
        }}}},
        {kmip::TagCertificateSubject, {{0, {
                KMIPFieldOrderItem(kmip::TagCertificateSubjectDistinguishedName, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagCertificateSubjectAlternativeName, kmip::TypeTextString),
                }}}},
        {kmip::TagCertificateIssuer, {{0, {
                KMIPFieldOrderItem(kmip::TagCertificateIssuerDistinguishedName, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagCertificateIssuerAlternativeName, kmip::TypeTextString),
        }}}},
        {kmip::TagDigest, {{0, {
                KMIPFieldOrderItem(kmip::TagHashingAlgorithm, kmip::TypeEnumeration, 1),
                KMIPFieldOrderItem(kmip::TagDigestValue, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagKeyFormatType, kmip::TypeEnumeration),
        }}}},
        {kmip::TagUsageLimits, {{0, {
                KMIPFieldOrderItem(kmip::TagUsageLimitsTotal, kmip::TypeLongInteger, 1),
                KMIPFieldOrderItem(kmip::TagUsageLimitsCount, kmip::TypeLongInteger, 1),
                KMIPFieldOrderItem(kmip::TagUsageLimitsUnit, kmip::TypeEnumeration, 1),
        }}}},
        {kmip::TagLink, {{0, {
                KMIPFieldOrderItem(kmip::TagLinkType, kmip::TypeEnumeration, 1),
                KMIPFieldOrderItem(kmip::TagLinkedObjectIdentifier, kmip::TypeTextString, 1),
        }}}},
        {kmip::TagApplicationSpecificInformation, {{0, {
                KMIPFieldOrderItem(kmip::TagApplicationNamespace, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagApplicationData, kmip::TypeTextString),
        }}}},
        {kmip::TagAlternativeName, {{0, {
                KMIPFieldOrderItem(kmip::TagAlternativeNameValue, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagAlternativeNameType, kmip::TypeEnumeration, 1),
        }}}},
        {kmip::TagKeyValueLocation, {{0, {
                KMIPFieldOrderItem(kmip::TagKeyValueLocationValue, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagKeyValueLocationType, kmip::TypeEnumeration, 1),
        }}}},
        {kmip::TagNonce, {{0, {
                KMIPFieldOrderItem(kmip::TagNonceID, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagNonceValue, kmip::TypeByteString),
        }}}},
        {kmip::TagCredentialValue, {{0, {
                KMIPFieldOrderItem(kmip::TagUsername, kmip::TypeTextString),

                KMIPFieldOrderItem(kmip::TagDeviceSerialNumber, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagPassword, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagDeviceIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagNetworkIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagMachineIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagMediaIdentifier, kmip::TypeTextString),

                KMIPFieldOrderItem(kmip::TagNonce, kmip::TypeStructure),
                KMIPFieldOrderItem(kmip::TagAttestationType, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagAttestationMeasurement, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagAttestationAssertion, kmip::TypeByteString),
            }},
            {KMIPCredentialType::UsernameAndPassword, {
                KMIPFieldOrderItem(kmip::TagUsername, kmip::TypeTextString, 1),
                KMIPFieldOrderItem(kmip::TagPassword, kmip::TypeTextString),
            }},
            {KMIPCredentialType::Device, {
                KMIPFieldOrderItem(kmip::TagDeviceSerialNumber, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagPassword, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagDeviceIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagNetworkIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagMachineIdentifier, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagMediaIdentifier, kmip::TypeTextString),
            }},
            {KMIPCredentialType::Attestation, {
                KMIPFieldOrderItem(kmip::TagNonce, kmip::TypeStructure, 1),
                KMIPFieldOrderItem(kmip::TagAttestationType, kmip::TypeEnumeration, 1),
                KMIPFieldOrderItem(kmip::TagAttestationMeasurement, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagAttestationAssertion, kmip::TypeByteString),
            }},
        }},
        {kmip::TagCredential, {{0, {
                KMIPFieldOrderItem(kmip::TagCredentialType, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagCredentialValue, kmip::TypeStructure),
        }}}},
        {kmip::TagKeyValue, {{0, {
            KMIPFieldOrderItem(kmip::TagKeyMaterial, {kmip::TypeStructure, kmip::TypeByteString}),
            KMIPFieldOrderItem(kmip::TagAttribute, kmip::TypeStructure, 0, kmip::kiMaxFields),
        }}}},
        {kmip::TagKeyBlock, {{0, {
            KMIPFieldOrderItem(kmip::TagKeyFormatType, kmip::TypeEnumeration),
            KMIPFieldOrderItem(kmip::TagKeyCompressionType, kmip::TypeEnumeration),
            KMIPFieldOrderItem(kmip::TagKeyValue, {kmip::TypeStructure, kmip::TypeByteString}),
            KMIPFieldOrderItem(kmip::TagCryptographicAlgorithm, kmip::TypeEnumeration),
            KMIPFieldOrderItem(kmip::TagCryptographicLength, kmip::TypeInteger),
            KMIPFieldOrderItem(kmip::TagKeyWrappingData, kmip::TypeStructure),
        }}}},
        {kmip::TagEncryptionKeyInformation, {{0, {
            KMIPFieldOrderItem(kmip::TagUniqueIdentifier, kmip::TypeTextString, 1),
            KMIPFieldOrderItem(kmip::TagCryptographicParameters, kmip::TypeStructure),
        }}}},
        {kmip::TagMACSignatureKeyInformation, {{0, {
            KMIPFieldOrderItem(kmip::TagUniqueIdentifier, kmip::TypeTextString, 1),
            KMIPFieldOrderItem(kmip::TagCryptographicParameters, kmip::TypeStructure),
        }}}},
        {kmip::TagKeyWrappingData, {{0, {
            KMIPFieldOrderItem(kmip::TagWrappingMethod, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagEncryptionKeyInformation, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagMACSignatureKeyInformation, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagMACSignature, kmip::TypeByteString),
            KMIPFieldOrderItem(kmip::TagIVCounterNonce, kmip::TypeByteString),
            KMIPFieldOrderItem(kmip::TagEncodingOption, kmip::TypeEnumeration),
        }}}},
        {kmip::TagKeyWrappingSpecification, {{0, {
            KMIPFieldOrderItem(kmip::TagWrappingMethod, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagEncryptionKeyInformation, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagMACSignatureKeyInformation, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagAttributeName, kmip::TypeTextString),
            KMIPFieldOrderItem(kmip::TagEncodingOption, kmip::TypeEnumeration),
        }}}},
        {kmip::TagCertificate, {{0, {
            KMIPFieldOrderItem(kmip::TagCertificateType, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagCertificateValue, kmip::TypeByteString, 1),
        }}}},
        {kmip::TagSymmetricKey, {{0, {
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagPublicKey, {{0, {
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagPrivateKey, {{0, {
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagSplitKey, {{0, {
            KMIPFieldOrderItem(kmip::TagSplitKeyParts, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagKeyPartIdentifier, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagSplitKeyThreshold, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagSplitKeyMethod, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagPrimeFieldSize, kmip::TypeBigInteger),
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagSecretData, {{0, {
            KMIPFieldOrderItem(kmip::TagSecretDataType, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagPGPKey, {{0, {
            KMIPFieldOrderItem(kmip::TagPGPKeyVersion, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagKeyBlock, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagTemplate, {{0, {
            KMIPFieldOrderItem(kmip::TagAttribute, kmip::TypeStructure, 1, kmip::kiMaxFields)
        }}}},
        {kmip::TagOpaqueObject, {{0, {
            KMIPFieldOrderItem(kmip::TagOpaqueDataType, kmip::TypeEnumeration, 1),
            KMIPFieldOrderItem(kmip::TagOpaqueDataValue, kmip::TypeByteString, 1),
        }}}},
        {kmip::TagProtocolVersion, {{0, {
            KMIPFieldOrderItem(kmip::TagProtocolVersionMajor, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagProtocolVersionMinor, kmip::TypeInteger, 1),
        }}}},
        {kmip::TagAuthentication, {{0, {
            KMIPFieldOrderItem(kmip::TagCredential, kmip::TypeStructure, 1, kmip::kiMaxFields),
        }}}},
        {kmip::TagMessageExtension, {{0, {
            KMIPFieldOrderItem(kmip::TagVendorIdentification, kmip::TypeTextString, 1),
            KMIPFieldOrderItem(kmip::TagCriticalityIndicator, kmip::TypeBoolean, 1),
            KMIPFieldOrderItem(kmip::TagVendorExtension, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagRequestMessage, {{0, {
            KMIPFieldOrderItem(kmip::TagRequestHeader, kmip::TypeStructure, 1),
            KMIPFieldOrderItem(kmip::TagBatchItem, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagResponseMessage, {{0, {
            KMIPFieldOrderItem(kmip::TagResponseHeader, kmip::TypeStructure, 1),
            KMIPFieldOrderItem(kmip::TagBatchItem, kmip::TypeStructure, 1),
        }}}},
        {kmip::TagRequestHeader, {{0, {
            KMIPFieldOrderItem(kmip::TagProtocolVersion, kmip::TypeStructure, 1),
            KMIPFieldOrderItem(kmip::TagMaximumResponseSize, kmip::TypeInteger, 1),
            KMIPFieldOrderItem(kmip::TagClientCorrelationValue, kmip::TypeTextString),
            KMIPFieldOrderItem(kmip::TagServerCorrelationValue, kmip::TypeTextString),
            KMIPFieldOrderItem(kmip::TagAsynchronousIndicator, kmip::TypeBoolean),
            KMIPFieldOrderItem(kmip::TagAttestationCapableIndicator, kmip::TypeBoolean),
            KMIPFieldOrderItem(kmip::TagAttestationType, kmip::TypeEnumeration, 0, kmip::kiMaxFields),
            KMIPFieldOrderItem(kmip::TagAuthentication, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagBatchErrorContinuationOption, kmip::TypeEnumeration),
            KMIPFieldOrderItem(kmip::TagBatchOrderOption, kmip::TypeBoolean),
            KMIPFieldOrderItem(kmip::TagTimeStamp, kmip::TypeDateTime),
            KMIPFieldOrderItem(kmip::TagBatchCount, kmip::TypeInteger, 1),
        }}}},
        {kmip::TagResponseHeader, {{0, {
            KMIPFieldOrderItem(kmip::TagProtocolVersion, kmip::TypeStructure, 1),
            KMIPFieldOrderItem(kmip::TagTimeStamp, kmip::TypeDateTime, 1),
            KMIPFieldOrderItem(kmip::TagNonce, kmip::TypeStructure),
            KMIPFieldOrderItem(kmip::TagAttestationType, kmip::TypeEnumeration, 0, kmip::kiMaxFields),
            KMIPFieldOrderItem(kmip::TagClientCorrelationValue, kmip::TypeTextString),
            KMIPFieldOrderItem(kmip::TagServerCorrelationValue, kmip::TypeTextString),
            KMIPFieldOrderItem(kmip::TagBatchCount, kmip::TypeInteger, 1),
        }}}},
        {kmip::TagBatchItem, {{0, {
                KMIPFieldOrderItem(kmip::TagOperation, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagUniqueBatchItemID, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagResultStatus, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagResultReason, kmip::TypeEnumeration),
                KMIPFieldOrderItem(kmip::TagResultMessage, kmip::TypeTextString),
                KMIPFieldOrderItem(kmip::TagAsynchronousCorrelationValue, kmip::TypeByteString),
                KMIPFieldOrderItem(kmip::TagResponsePayload, kmip::TypeStructure),
                KMIPFieldOrderItem(kmip::TagRequestPayload, kmip::TypeStructure),
                KMIPFieldOrderItem(kmip::TagMessageExtension, kmip::TypeStructure),
        }}}},
        {kmip::TagProtocolVersion, {{0, {
                KMIPFieldOrderItem(kmip::TagProtocolVersionMajor, kmip::TypeInteger),
                KMIPFieldOrderItem(kmip::TagProtocolVersionMinor, kmip::TypeInteger),
        }}}},
    };
}


KMIPFieldOrder *KMIPFieldOrders::getKMIPFieldOrder(int iTag, int iType) {
    KMIPFieldOrder *pkfo = nullptr;
    auto mapKFOByType = mapKFOs.find(iTag);
    if (mapKFOByType != mapKFOs.end()) {
        auto iterKFO = mapKFOByType->second.find(iType);
        if (iterKFO != mapKFOByType->second.end()) {
            pkfo = &(iterKFO->second);
        }
    }

    return pkfo;
}
