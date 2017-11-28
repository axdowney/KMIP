/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPENUMERATION_H
#define _KMIPENUMERATION_H


#include <crypto++/aes.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/des.h>
#include <crypto++/blowfish.h>
#include <crypto++/twofish.h>
#include <crypto++/camellia.h>
#include <crypto++/cast.h>
#include <crypto++/idea.h>
#include <crypto++/mars.h>
#include <crypto++/rc2.h>
#include <crypto++/rc5.h>
#include <crypto++/rc6.h>
#include <crypto++/skipjack.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/arc4.h>
#include <crypto++/hmac.h>
#include <crypto++/sha.h>
#include <crypto++/md5.h>


#include "KMIPNumber.h"
#include "EnumMacros.h"

#define DECLARE_KMIPENUM_LIST(name, list)\
    DECLARE_ENUM_LIST(name, list)\
    virtual std::string getValueName() const {\
        return VALUEToString(static_cast<VALUE>(getValue()));\
    }\
    virtual bool setValueFromName(const std::string &sName) {\
        setValue(VALUEFromString(sName));\
        return isValid();\
    }\

class KMIPEnumeration : public KMIPNumber<uint32_t> {
    public:
        KMIPEnumeration(int iTag, uint32_t eValue = 0, uint32_t eFirst = 0, uint32_t eLast = -1);
        virtual bool isValid() const;
        virtual bool isValid(uint32_t uiVal) const;
        virtual std::string getValueName() const;
        virtual bool setValueFromName(const std::string &sName);
        virtual bool setValueFromXML(const std::string &sValue);
        virtual std::string getXMLValue() const;
    protected:
        uint32_t eFirst;
        uint32_t eLast;
};

typedef std::unique_ptr<KMIPEnumeration> KMIPEnumerationUP;

class KMIPCredentialType : public KMIPEnumeration {
#define CREDENTIAL_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(UsernameAndPassword,1)\
    b(Device,2)\
    b(Attestation,3)\
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, CREDENTIAL_TYPE_LIST);
    KMIPCredentialType(uint32_t eValue);
};

class KMIPKeyCompressionType : public KMIPEnumeration {
#define KEY_COMPRESSION_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(ECPublicKeyTypeUncompressed,0x1) \
    b(ECPublicKeyTypeX9_62CompressedPrime,0x2) \
    b(ECPublicKeyTypeX9_62CompressedChar2,0x3) \
    b(ECPublicKeyTypeX9_62CompressedPrimeKeyTypeX9_62Hybrid,0x4) \
    a(NumValues)


    DECLARE_KMIPENUM_LIST(VALUE, KEY_COMPRESSION_TYPE_LIST);
    KMIPKeyCompressionType(uint32_t eValue);
};

class KMIPKeyFormatType : public KMIPEnumeration {
#define KEY_FORMAT_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(Raw,0x1) \
    b(Opaque,0x2) \
    b(PKCS_1,0x3) \
    b(PKCS_8,0x4) \
    b(X_509,0x5) \
    b(ECPrivateKey,0x6) \
    b(TransparentSymmetricKey,0x7) \
    b(TransparentDSAPrivateKey,0x8) \
    b(TransparentDSAPublicKey,0x9) \
    b(TransparentRSAPrivateKey,0x0000000A) \
    b(TransparentRSAPublicKey,0x0000000B) \
    b(TransparentDHPrivateKey,0x0000000C) \
    b(TransparentRSAPublicKeyarentDHPublicKey,0x0000000D) \
    b(TransparentECDSAPrivateKey,0x0000000CE) \
    b(TransparentECDSAPublicKey,0x0000000F) \
    b(TransparentECDHPrivateKey,0x10) \
    b(TransparentECDHPublicKey,0x11) \
    b(TransparentECMQVPrivateKey,0x12) \
    b(TransparentECMQVPublicKey,0x13) \
    b(TransparentECPrivateKey,0x14) \
    b(TransparentECPublicKey,0x15) \
    b(PKCS_12,0x16) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, KEY_FORMAT_TYPE_LIST);
    KMIPKeyFormatType(uint32_t eValue);
};

class KMIPWrappingMethod : public KMIPEnumeration {
#define WRAPPING_METHOD_LIST(a,b)\
    b(Unknown,0)\
    b(Encrypt,0x1) \
    b(MACSign,0x2) \
    b(EncryptThenMACSign,0x3) \
    b(MACSigngnThenEncrypt,0x4) \
    b(TR_31,0x5) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, WRAPPING_METHOD_LIST);
    KMIPWrappingMethod(uint32_t eValue);
};

class KMIPRecommendedCurve : public KMIPEnumeration {
#define RECOMMENDED_CURVE_LIST(a,b)\
    b(Unknown,0)\
    b(P_192,0x1) \
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
    b(SECP192K1,0x17) \
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
    b(ANSIX9C2TNB239V3,0x31) \
    b(ANSIX9C2PNB272W1,0x32) \
    b(ANSIX9C2PNB304W1,0x33) \
    b(ANSIX9C2TNB359V1,0x34) \
    b(ANSIX9C2PNB368W1,0x35) \
    b(ANSIX9C2TNB431R1,0x36) \
    b(BRAINPOOLP160R1,0x37) \
    b(BRAINPOOLP160T1,0x38) \
    b(BRAINPOOLP192R1,0x39) \
    b(BRAINPOOLP192T1,0x0000003A) \
    b(BRAINPOOLP224R1,0x0000003B) \
    b(BRAINPOOLP224T1,0x0000003C) \
    b(BRAINPOOLP256R1,0x0000003D) \
    b(BRAINPOOLP256T1,0x0000003E) \
    b(BRAINPOOLP320R1,0x0000003F) \
    b(BRAINPOOLP320T1,0x40) \
    b(BRAINPOOLP384R1,0x41) \
    b(BRAINPOOLP384T1,0x42) \
    b(BRAINPOOLP512R1,0x43) \
    b(BRAINPOOLP512T1,0x44) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, RECOMMENDED_CURVE_LIST);
    KMIPRecommendedCurve(uint32_t eValue);
    static int CurveToNID(uint32_t eValue);
};

class KMIPCertificateType : public KMIPEnumeration {
#define CERTIFICATE_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(X_509,0x1) \
    b(PGP,0x2) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, CERTIFICATE_TYPE_LIST);
    KMIPCertificateType(uint32_t eValue);
};

class KMIPDigitalSignatureAlgorithm : public KMIPEnumeration {
#define DIGITAL_SIGNATURE_ALGORITHM_LIST(a,b)\
    b(Unknown,0)\
    b(MD2WithRSAEncryption,0x1) \
    b(MD5WithRSAEncryptionPKCS_1V1_5,0x2) \
    b(SHA_1WithRSAEncryptionPKCS_1V1_5,0x3) \
    b(SHA_224WithRSAEncryptionPKCS_1V1_5,0x4) \
    b(SHA_256WithRSAEncryptionPKCS_1V1_5,0x5) \
    b(SHA_384WithRSAEncryptionPKCS_1V1_5,0x6) \
    b(SHA_512WithRSAEncryptionPKCS_1V1_5,0x7) \
    b(RSASSAPSS,0x8) \
    b(DSAWithSHA_1,0x9) \
    b(DECLARE_KMIPENUM_LISTSAWithSHA224,0x0000000A) \
    b(DSAWithSHA256,0x0000000B) \
    b(ECDSAWithSHA_1,0x0000000C) \
    b(ECDSAWithSHA224,0x0000000D) \
    b(ECDSAWithSHA256,0x0000000E) \
    b(ECDSAWithSHA384,0x0000000F) \
    b(ECDSAWithSHA512,0x10) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, DIGITAL_SIGNATURE_ALGORITHM_LIST);
    KMIPDigitalSignatureAlgorithm(uint32_t eValue);
};

class KMIPSplitKeyMethod : public KMIPEnumeration {
#define SPLIT_KEY_METHOD_LIST(a,b)\
    b(Unknown,0)\
    b(X_509,0x1) \
    b(PGP,0x2) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, SPLIT_KEY_METHOD_LIST);
    KMIPSplitKeyMethod(uint32_t eValue);
};

class KMIPSecretDataType : public KMIPEnumeration {
#define SECRET_DATA_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(Password,0x1) \
    b(Seed,0x2) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, SECRET_DATA_TYPE_LIST);
    KMIPSecretDataType(uint32_t eValue);
};

class KMIPOpaqueDataType : public KMIPEnumeration {
#define OPAQUE_DATA_TYPE_LIST(a,b)\
    b(Unknown,0)\
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, OPAQUE_DATA_TYPE_LIST);
    KMIPOpaqueDataType(uint32_t eValue);
};

class KMIPNameType : public KMIPEnumeration {
#define NAME_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(UninterpretedTextString,0x1) \
    b(URI,0x2) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, NAME_TYPE_LIST);
    KMIPNameType(uint32_t eValue);
};

class KMIPObjectType : public KMIPEnumeration {
#define OBJECT_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(Certificate,0x1) \
    b(SymmetricKey,0x2) \
    b(PublicKey,0x3) \
    b(PrivateKey,0x4) \
    b(SplitKey,0x5) \
    b(Template,0x6) \
    b(SecretData,0x7) \
    b(OpaqueObject,0x8) \
    b(PGPKey,0x9) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, OBJECT_TYPE_LIST);
    KMIPObjectType(uint32_t eValue);
};

class KMIPCryptographicAlgorithm : public KMIPEnumeration {
#define CRYPTOGRAPHIC_ALGORITHM_LIST(a,b)\
    b(Unknown,0)\
    b(DES,0x1) \
    b(DES3,0x2) \
    b(AES,0x3) \
    b(RSA,0x4) \
    b(DSA,0x5) \
    b(ECDSA,0x6) \
    b(HMACSHA1,0x7) \
    b(HMACSHA224,0x8)               \
    b(HMACSHA256,0x9) \
    b(HMACSHA384,0x0000000A) \
    b(HMACSHA512,0x0000000B) \
    b(HMACMD5,0x0000000C) \
    b(DH,0x0000000D) \
    b(ECDH,0x0000000E) \
    b(ECMQV,0x0000000F) \
    b(Blowfish,0x10) \
    b(Camellia,0x11) \
    b(CAST5,0x12) \
    b(IDEA,0x13) \
    b(MARS,0x14) \
    b(RC2,0x15) \
    b(RC4,0x16) \
    b(RC5,0x17) \
    b(SKIPJACK,0x18) \
    b(Twofish,0x19) \
    b(EC,0x0000000C01A) \
    b(OneTimePad,0x0000001B) \
    a(NumValues)


#define getCryptoPPAlg(e, val) \
    (e == KMIPCryptographicAlgorithm::DES ? CryptoPP::DES::val :\
    e == KMIPCryptographicAlgorithm::DES3 ? CryptoPP::DES_EDE3::val :\
    e == KMIPCryptographicAlgorithm::AES ? CryptoPP::AES::val :\
    e == KMIPCryptographicAlgorithm::Blowfish ? CryptoPP::Blowfish::val :\
    e == KMIPCryptographicAlgorithm::Camellia ? CryptoPP::Camellia::val :\
    e == KMIPCryptographicAlgorithm::CAST5 ? CryptoPP::CAST128::val :\
    e == KMIPCryptographicAlgorithm::IDEA ? CryptoPP::IDEA::val :\
    e == KMIPCryptographicAlgorithm::MARS ? CryptoPP::MARS::val :\
    e == KMIPCryptographicAlgorithm::RC2 ? CryptoPP::RC2::val :\
    e == KMIPCryptographicAlgorithm::RC4 ? CryptoPP::Weak::ARC4::val :\
    e == KMIPCryptographicAlgorithm::RC5 ? CryptoPP::RC5::val :\
    e == KMIPCryptographicAlgorithm::SKIPJACK ? CryptoPP::SKIPJACK::val :\
    e == KMIPCryptographicAlgorithm::Twofish ? CryptoPP::Twofish::val :\
    0)
            
#define getCryptoPPAlgVariableLength(e, val) \
    (e == KMIPCryptographicAlgorithm::AES ? CryptoPP::AES::val :\
    e == KMIPCryptographicAlgorithm::Blowfish ? CryptoPP::Blowfish::val :\
    e == KMIPCryptographicAlgorithm::Camellia ? CryptoPP::Camellia::val :\
    e == KMIPCryptographicAlgorithm::CAST5 ? CryptoPP::CAST128::val :\
    e == KMIPCryptographicAlgorithm::MARS ? CryptoPP::MARS::val :\
    e == KMIPCryptographicAlgorithm::RC2 ? CryptoPP::RC2::val :\
    e == KMIPCryptographicAlgorithm::RC4 ? CryptoPP::Weak::ARC4::val :\
    e == KMIPCryptographicAlgorithm::RC5 ? CryptoPP::RC5::val :\
    e == KMIPCryptographicAlgorithm::Twofish ? CryptoPP::Twofish::val :\
    0)
            

    DECLARE_KMIPENUM_LIST(VALUE, CRYPTOGRAPHIC_ALGORITHM_LIST);
    KMIPCryptographicAlgorithm(uint32_t eValue);
    static bool isFixedLength(uint32_t iAlg);
    static bool isSymmetric(uint32_t iAlg);
    static bool isAsymmetric(uint32_t iAlg);
};

class KMIPBlockCipherMode : public KMIPEnumeration {
#define BLOCK_CIPHER_MODE_LIST(a,b)\
    b(Unknown,0)\
    b(CBC,0x1) \
    b(ECB,0x2) \
    b(PCBC,0x3) \
    b(CFB,0x4) \
    b(OFB,0x5) \
    b(CTR,0x6) \
    b(CMAC,0x7) \
    b(CCM,0x8) \
    b(GCM,0x9) \
    b(CBCMAC,0x0000000A) \
    b(XTS,0x0000000B) \
    b(AESKeyWrapPadding,0x0000000C) \
    b(NISTKeyWrap,0x0000000D) \
    b(X9_102AESKW,0x0000000E) \
    b(X9_102TDKW,0x0000000F) \
    b(X9_102AKW1,0x10) \
    b(X9_102AKW2,0x11) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, BLOCK_CIPHER_MODE_LIST);
    KMIPBlockCipherMode(uint32_t eValue);
};

class KMIPPaddingMethod : public KMIPEnumeration {
#define PADDING_METHOD_LIST(a,b)\
    b(Unknown,0)\
    b(None,0x1) \
    b(OAEP,0x2) \
    b(PKCS5,0x3) \
    b(SSL3,0x4) \
    b(Zeros,0x5) \
    b(ANSIX9_23,0x6) \
    b(ISO10126,0x7) \
    b(PKCS1V1_5,0x8) \
    b(ISO10126X9_31,0x9) \
    b(PSS,0x0000000A) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, PADDING_METHOD_LIST);
    KMIPPaddingMethod(uint32_t eValue);
};

class KMIPHashingAlgorithm : public KMIPEnumeration {
#define HASHING_ALGORITHM_LIST(a,b)\
    b(Unknown,0)\
    b(MD2,0x1) \
    b(MD4,0x2) \
    b(MD5,0x3) \
    b(SHA_1,0x4) \
    b(SHA_256WithRSAEncryptionPKCS_1V1_5A_224,0x5) \
    b(SHA_256,0x6) \
    b(SHA_384,0x7) \
    b(SHA_512,0x8) \
    b(RSAIPEMD_160,0x9) \
    b(Tiger,0x0000000A) \
    b(Whirlpool,0x0000000B) \
    b(SHA_256HA_512_224,0x0000000C) \
    b(SHA_512_256,0x0000000D) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, HASHING_ALGORITHM_LIST);
    KMIPHashingAlgorithm(uint32_t eValue);
};

class KMIPKeyRoleType : public KMIPEnumeration {
#define KEY_ROLE_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(BDK,0x1) \
    b(CVK,0x2) \
    b(DEK,0x3) \
    b(MKAC,0x4) \
    b(MKSMC,0x5) \
    b(MKSMI,0x6) \
    b(MKDAC,0x7) \
    b(MKDN,0x8) \
    b(MKCP,0x9) \
    b(MKOTH,0x0000000A) \
    b(KEK,0x0000000B) \
    b(MAC16609,0x0000000DC) \
    b(MAC97971,0x0000000D) \
    b(MAC97972,0x0000000E) \
    b(MAC97973,0x0000000DC0000000F) \
    b(MAC97974,0x10) \
    b(MAC97975,0x11) \
    b(ZPK,0x12) \
    b(PVKIBM,0x13) \
    b(PVKPVV,0x14) \
    b(PVKOTH,0x15) \
    b(DUKPT,0x16) \
    b(IV,0x17) \
    b(TRKBK,0x18) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, KEY_ROLE_TYPE_LIST);
    KMIPKeyRoleType(uint32_t eValue);
};

class KMIPState : public KMIPEnumeration {
#define STATE_LIST(a,b)\
    b(Unknown,0)\
    b(PreActive,0x1) \
    b(Active,0x2) \
    b(Deactivated,0x3) \
    b(Compromised,0x4) \
    b(Destroyed,0x5) \
    b(DestroyedCompromised,0x6) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, STATE_LIST);
    KMIPState(uint32_t eValue);
};

class KMIPRevocationReasonCode : public KMIPEnumeration {
#define REVOCATION_REASON_CODE_LIST(a,b)\
    b(Unknown,0)\
    b(Unspecified,0x1) \
    b(KeyCompromise,0x2) \
    b(CACompromise,0x63) \
    b(AffiliationChanged,0x4) \
    b(Superseded,0x5) \
    b(CessationOfOperation,0x6) \
    b(PrivilegeWithdrawn,0x7) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, REVOCATION_REASON_CODE_LIST);
    KMIPRevocationReasonCode(uint32_t eValue);
};

class KMIPLinkType : public KMIPEnumeration {
#define LINK_TYPE_LIST(a,b)\
    b(Unknown,0)\
    b(CertificateLink,0x101) \
    b(PublicKeyLink,0x102) \
    b(PublicKeyLinkPrivateKeyLink,0x103) \
    b(DerivationBaseObjectLink,0x104) \
    b(DerivedKeyLink,0x105) \
    b(ReplacementObjectLink,0x106) \
    b(ReplacedObjectLink,0x107) \
    b(ParentLink,0x108) \
    b(ChildLink,0x109) \
    b(PreviousLink,0x0000010A) \
    b(NextLink,0x0000010B) \
    b(PKCS_12CertificateLink,0x0000010C) \
    b(PKCS_12PasswordLink,0x0000010D) \
    a(NumValues)

    DECLARE_KMIPENUM_LIST(VALUE, LINK_TYPE_LIST);
    KMIPLinkType(uint32_t eValue);
};

class KMIPDerivationMethod : public KMIPEnumeration {
#define DERIVATION_METHOD_LIST(a,b) \
        b(Unknown,0)\
	b(PBKDF2,	0x1) \
	b(HASH,	0x2) \
	b(HMAC,	0x3) \
	b(ENCRYPT,	0x4) \
	b(NIST800_108_C,	0x5) \
	b(NIST800_108_F,	0x6) \
	b(NIST800_108DPI,	0x7) \
	b(AsymmetricKey,	0x8) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, DERIVATION_METHOD_LIST)
	KMIPDerivationMethod(uint32_t eValue);
};

class KMIPCertificateRequestType : public KMIPEnumeration {
#define CERTIFICATE_REQUEST_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(CRMF,	0x1) \
	b(PKCS_10,	0x2) \
	b(PEM,	0x3) \
	b(PGP,	0x4) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, CERTIFICATE_REQUEST_TYPE_LIST)
	KMIPCertificateRequestType(uint32_t eValue);
};

class KMIPValidityIndicator : public KMIPEnumeration {
#define VALIDITY_INDICATOR_LIST(a,b) \
	b(Valid,	0x1) \
	b(Invalid,	0x2) \
	b(Unknown,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, VALIDITY_INDICATOR_LIST)
	KMIPValidityIndicator(uint32_t eValue);
};

class KMIPQueryFunction : public KMIPEnumeration {
#define QUERY_FUNCTION_LIST(a,b) \
        b(Unknown,0)\
	b(QueryOperations,	0x1) \
	b(QueryObjects,	0x2) \
	b(QueryServerInformation,	0x3) \
	b(QueryApplicationNamespaces,	0x4) \
	b(QueryExtensionList,	0x5) \
	b(QueryExtensionMap,	0x6) \
	b(QueryAttestationTypes,	0x7) \
	b(QueryRNGs,	0x8) \
	b(QueryValidations,	0x9) \
	b(QueryProfiles,	0x0000000A) \
	b(QueryCapabilities,	0x0000000B) \
	b(QueryClientRegistrationMethods,	0x0000000C) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, QUERY_FUNCTION_LIST)
	KMIPQueryFunction(uint32_t eValue);
};

class KMIPCancellationResult : public KMIPEnumeration {
#define CANCELLATION_RESULT_LIST(a,b) \
        b(Unknown,0)\
	b(Canceled,	0x1) \
	b(UnableToCancel,	0x2) \
	b(Completed,	0x3) \
	b(Failed,	0x4) \
	b(Unavailable,	0x5) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, CANCELLATION_RESULT_LIST)
	KMIPCancellationResult(uint32_t eValue);
};

class KMIPPutFunction : public KMIPEnumeration {
#define PUT_FUNCTION_LIST(a,b) \
        b(Unknown,0)\
	b(New,	0x1) \
	b(Replace,	0x2) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, PUT_FUNCTION_LIST)
	KMIPPutFunction(uint32_t eValue);
};

class KMIPOperation : public KMIPEnumeration {
#define OPERATION_LIST(a,b) \
        b(Unknown,0)\
	b(Create,	0x1) \
	b(CreateKeyPair,	0x2) \
	b(Register,	0x3) \
	b(ReKey,	0x4) \
	b(DeriveKey,	0x5) \
	b(Certify,	0x6) \
	b(ReCertify,	0x7) \
	b(Locate,	0x8) \
	b(Check,	0x9) \
	b(Get,	0x0000000A) \
	b(GetAttributes,	0x0000000B) \
	b(GetAttributeList,	0x0000000C) \
	b(AddAttribute,	0x0000000D) \
	b(ModifyAttribute,	0x0000000E) \
	b(DeleteAttribute,	0x0000000F) \
	b(ObtainLease,	0x10) \
	b(GetUsageAllocation,	0x11) \
	b(Activate,	0x12) \
	b(Revoke,	0x13) \
	b(Destroy,	0x14) \
	b(Archive,	0x15) \
	b(Recover,	0x16) \
	b(Validate,	0x17) \
	b(Query,	0x18) \
	b(Cancel,	0x19) \
	b(Poll,	0x0000001A) \
	b(Notify,	0x0000001B) \
	b(Put,	0x0000001C) \
	b(ReKeyKeyPair,	0x0000001D) \
	b(DiscoverVersions,	0x0000001E) \
	b(Encrypt,	0x0000001F) \
	b(Decrypt,	0x20) \
	b(Sign,	0x21) \
	b(SignatureVerify,	0x22) \
	b(MAC,	0x23) \
	b(MACVerify,	0x24) \
	b(RNGRetrieve,	0x25) \
	b(RNGSeed,	0x26) \
	b(Hash,	0x27) \
	b(CreateSplitKey,	0x28) \
	b(JoinSplitKey,	0x29) \
	b(Import,	0x0000002A) \
	b(Export,	0x0000002B) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, OPERATION_LIST)
	KMIPOperation(uint32_t eValue);
};

class KMIPResultStatus : public KMIPEnumeration {
#define RESULT_STATUS_LIST(a,b) \
	b(Success,	0x0) \
	b(OperationFailed,	0x1) \
	b(OperationPending,	0x2) \
	b(OperationUndone,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, RESULT_STATUS_LIST)
	KMIPResultStatus(uint32_t eValue);
};

class KMIPResultReason : public KMIPEnumeration {
#define RESULT_REASON_LIST(a,b) \
        b(Unknown,0)\
	b(ItemNotFound,	0x1) \
	b(ResponseTooLarge,	0x2) \
	b(AuthenticationNotSuccessful,	0x3) \
	b(InvalidMessage,	0x4) \
	b(OperationNotSupported,	0x5) \
	b(MissingData,	0x6) \
	b(InvalidField,	0x7) \
	b(FeatureNotSupported,	0x8) \
	b(OperationCanceledByRequester,	0x9) \
	b(CryptographicFailure,	0x0000000A) \
	b(IllegalOperation,	0x0000000B) \
	b(PermissionDenied,	0x0000000C) \
	b(ObjectArchived,	0x0000000D) \
	b(IndexOutOfBounds,	0x0000000E) \
	b(ApplicationNamespaceNotSupported,	0x0000000F) \
	b(KeyFormatTypeNotSupported,	0x10) \
	b(KeyCompressionTypeNotSupported,	0x11) \
	b(EncodingOptionError,	0x12) \
	b(KeyValueNotPresent,	0x13) \
	b(AttestationRequired,	0x14) \
	b(AttestationFailed,	0x15) \
	b(Sensitive,	0x16) \
	b(NotExtractable,	0x17) \
	b(ObjectAlreadyExists,	0x18) \
	b(GeneralFailure,	0x100) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, RESULT_REASON_LIST)
	KMIPResultReason(uint32_t eValue);
};

class KMIPBatchErrorContinuationOption : public KMIPEnumeration {
#define BATCH_ERROR_CONTINUATION_OPTION_LIST(a,b) \
        b(Unknown,0)\
	b(Continue,	0x1) \
	b(Stop,	0x2) \
	b(Undo,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, BATCH_ERROR_CONTINUATION_OPTION_LIST)
	KMIPBatchErrorContinuationOption(uint32_t eValue);
};

class KMIPUsageLimitsUnit : public KMIPEnumeration {
#define USAGE_LIMITS_UNIT_LIST(a,b) \
        b(Unknown,0)\
	b(Byte,	0x1) \
	b(Object,	0x2) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, USAGE_LIMITS_UNIT_LIST)
	KMIPUsageLimitsUnit(uint32_t eValue);
};

class KMIPEncodingOption : public KMIPEnumeration {
#define ENCODING_OPTION_LIST(a,b) \
        b(Unknown,0)\
	b(NoEncoding,	0x1) \
	b(TTLVEncoding,	0x2) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, ENCODING_OPTION_LIST)
	KMIPEncodingOption(uint32_t eValue);
};

class KMIPObjectGroupMember : public KMIPEnumeration {
#define OBJECT_GROUP_MEMBER_LIST(a,b) \
        b(Unknown,0)\
	b(GroupMemberFresh,	0x1) \
	b(GroupMemberDefault,	0x2) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, OBJECT_GROUP_MEMBER_LIST)
	KMIPObjectGroupMember(uint32_t eValue);
};

class KMIPAlternativeNameType : public KMIPEnumeration {
#define ALTERNATIVE_NAME_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(UninterpretedTextString,	0x1) \
	b(URI,	0x2) \
	b(ObjectSerialNumber,	0x3) \
	b(EmailAddress,	0x4) \
	b(DNSName,	0x5) \
	b(X_500DistinguishedName,	0x6) \
	b(IPAddress,	0x7) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, ALTERNATIVE_NAME_TYPE_LIST)
	KMIPAlternativeNameType(uint32_t eValue);
};

class KMIPKeyValueLocationType : public KMIPEnumeration {
#define KEY_VALUE_LOCATION_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(UninterpretedTextString,	0x1) \
	b(URI,	0x2) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, KEY_VALUE_LOCATION_TYPE_LIST)
	KMIPKeyValueLocationType(uint32_t eValue);
};

class KMIPAttestationType : public KMIPEnumeration {
#define ATTESTATION_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(TPMQuote,	0x1) \
	b(TCGIntegrityReport,	0x2) \
	b(SAMLAssertion,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, ATTESTATION_TYPE_LIST)
	KMIPAttestationType(uint32_t eValue);
};

class KMIPRNGAlgorithm : public KMIPEnumeration {
#define RNG_ALGORITHM_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(FIPS186_2,	0x2) \
	b(DRBG,	0x3) \
	b(NRBG,	0x4) \
	b(ANSIX9_31,	0x5) \
	b(ANSIX9_62,	0x6) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, RNG_ALGORITHM_LIST)
	KMIPRNGAlgorithm(uint32_t eValue);
};

class KMIPDRBGAlgorithm : public KMIPEnumeration {
#define DRBG_ALGORITHM_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(DualEC,	0x2) \
	b(Hash,	0x3) \
	b(HMAC,	0x4) \
	b(CTR,	0x5) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, DRBG_ALGORITHM_LIST)
	KMIPDRBGAlgorithm(uint32_t eValue);
};

class KMIPFIPS186Variation : public KMIPEnumeration {
#define FIPS186VARIATION_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(GPXOriginal,	0x2) \
	b(GPXChangeNotice,	0x3) \
	b(xOriginal,	0x4) \
	b(xChangeNotice,	0x5) \
	b(kOriginal,	0x6) \
	b(kChangeNotice,	0x7) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, FIPS186VARIATION_LIST)
	KMIPFIPS186Variation(uint32_t eValue);
};

class KMIPValidationAuthorityType : public KMIPEnumeration {
#define VALIDATION_AUTHORITY_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(NISTCMVP,	0x2) \
	b(CommonCriteria,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, VALIDATION_AUTHORITY_TYPE_LIST)
	KMIPValidationAuthorityType(uint32_t eValue);
};

class KMIPValidationType : public KMIPEnumeration {
#define VALIDATION_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(Hardware,	0x2) \
	b(Software,	0x3) \
	b(Firmware,	0x4) \
	b(Hybrid,	0x5) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, VALIDATION_TYPE_LIST)
	KMIPValidationType(uint32_t eValue);
};

class KMIPProfileName : public KMIPEnumeration {
#define PROFILE_NAME_LIST(a,b) \
        b(Unknown,0)\
	b(BaselineServerBasicKMIPV1_2,	0x1) \
	b(BaselineServerTLSV1_2KMIPV1_2,	0x2) \
	b(BaselineClientBasicKMIPV1_2,	0x3) \
	b(BaselineClientTLSV1_2KMIPV1_2,	0x4) \
	b(CompleteServerBasicKMIPV1_2,	0x5) \
	b(CompleteServerTLSV1_2KMIPV1_2,	0x6) \
	b(TapeLibraryClientKMIPV1_0,	0x7) \
	b(TapeLibraryClientKMIPV1_1,	0x8) \
	b(TapeLibraryClientKMIPV1_2,	0x9) \
	b(TapeLibraryServerKMIPV1_0,	0x0000000A) \
	b(TapeLibraryServerKMIPV1_1,	0x0000000B) \
	b(TapeLibraryServerKMIPV1_2,	0x0000000C) \
	b(SymmetricKeyLifecycleClientKMIPV1_0,	0x0000000D) \
	b(SymmetricKeyLifecycleClientKMIPV1_1,	0x0000000E) \
	b(SymmetricKeyLifecycleClientKMIPV1_2,	0x0000000F) \
	b(SymmetricKeyLifecycleServerKMIPV1_0,	0x10) \
	b(SymmetricKeyLifecycleServerKMIPV1_1,	0x11) \
	b(SymmetricKeyLifecycleServerKMIPV1_2,	0x12) \
	b(AsymmetricKeyLifecycleClientKMIPV1_0,	0x13) \
	b(AsymmetricKeyLifecycleClientKMIPV1_1,	0x14) \
	b(AsymmetricKeyLifecycleClientKMIPV1_2,	0x15) \
	b(AsymmetricKeyLifecycleServerKMIPV1_0,	0x16) \
	b(AsymmetricKeyLifecycleServerKMIPV1_1,	0x17) \
	b(AsymmetricKeyLifecycleServerKMIPV1_2,	0x18) \
	b(BasicCryptographicClientKMIPV1_2,	0x19) \
	b(BasicCryptographicServerKMIPV1_2,	0x0000001A) \
	b(AdvancedCryptographicClientKMIPV1_2,	0x0000001B) \
	b(AdvancedCryptographicServerKMIPV1_2,	0x0000001C) \
	b(RNGCryptographicClientKMIPV1_2,	0x0000001D) \
	b(RNGCryptographicServerKMIPV1_2,	0x0000001E) \
	b(BasicSymmetricKeyFoundryClientKMIPV1_0,	0x0000001F) \
	b(IntermediateSymmetricKeyFoundryClientKMIPV1_0,	0x20) \
	b(AdvancedSymmetricKeyFoundryClientKMIPV1_0,	0x21) \
	b(BasicSymmetricKeyFoundryClientKMIPV1_1,	0x22) \
	b(IntermediateSymmetricKeyFoundryClientKMIPV1_1,	0x23) \
	b(AdvancedSymmetricKeyFoundryClientKMIPV1_1,	0x24) \
	b(BasicSymmetricKeyFoundryClientKMIPV1_2,	0x25) \
	b(IntermediateSymmetricKeyFoundryClientKMIPV1_2,	0x26) \
	b(AdvancedSymmetricKeyFoundryClientKMIPV1_2,	0x27) \
	b(SymmetricKeyFoundryServerKMIPV1_0,	0x28) \
	b(SymmetricKeyFoundryServerKMIPV1_1,	0x29) \
	b(SymmetricKeyFoundryServerKMIPV1_2,	0x0000002A) \
	b(OpaqueManagedObjectStoreClientKMIPV1_0,	0x0000002B) \
	b(OpaqueManagedObjectStoreClientKMIPV1_1,	0x0000002C) \
	b(OpaqueManagedObjectStoreClientKMIPV1_2,	0x0000002D) \
	b(OpaqueManagedObjectStoreServerKMIPV1_0,	0x0000002E) \
	b(OpaqueManagedObjectStoreServerKMIPV1_1,	0x0000002F) \
	b(OpaqueManagedObjectStoreServerKMIPV1_2,	0x30) \
	b(SuiteBMinLOS_128ClientKMIPV1_0,	0x31) \
	b(SuiteBMinLOS_128ClientKMIPV1_1,	0x32) \
	b(SuiteBMinLOS_128ClientKMIPV1_2,	0x33) \
	b(SuiteBMinLOS_128ServerKMIPV1_0,	0x34) \
	b(SuiteBMinLOS_128ServerKMIPV1_1,	0x35) \
	b(SuiteBMinLOS_128ServerKMIPV1_2,	0x36) \
	b(SuiteBMinLOS_192ClientKMIPV1_0,	0x37) \
	b(SuiteBMinLOS_192ClientKMIPV1_1,	0x38) \
	b(SuiteBMinLOS_192ClientKMIPV1_2,	0x39) \
	b(SuiteBMinLOS_192ServerKMIPV1_0,	0x0000003A) \
	b(SuiteBMinLOS_192ServerKMIPV1_1,	0x0000003B) \
	b(SuiteBMinLOS_192ServerKMIPV1_2,	0x0000003C) \
	b(StorageArrayWithSelfEncryptingDriveClientKMIPV1_0,	0x0000003D) \
	b(StorageArrayWithSelfEncryptingDriveClientKMIPV1_1,	0x0000003E) \
	b(StorageArrayWithSelfEncryptingDriveClientKMIPV1_2,	0x0000003F) \
	b(StorageArrayWithSelfEncryptingDriveServerKMIPV1_0,	0x40) \
	b(StorageArrayWithSelfEncryptingDriveServerKMIPV1_1,	0x41) \
	b(StorageArrayWithSelfEncryptingDriveServerKMIPV1_2,	0x42) \
	b(HTTPSClientKMIPV1_0,	0x43) \
	b(HTTPSClientKMIPV1_1,	0x44) \
	b(HTTPSClientKMIPV1_2,	0x45) \
	b(HTTPSServerKMIPV1_0,	0x46) \
	b(HTTPSServerKMIPV1_1,	0x47) \
	b(HTTPSServerKMIPV1_2,	0x48) \
	b(JSONClientKMIPV1_0,	0x49) \
	b(JSONClientKMIPV1_1,	0x0000004A) \
	b(JSONClientKMIPV1_2,	0x0000004B) \
	b(JSONServerKMIPV1_0,	0x0000004C) \
	b(JSONServerKMIPV1_1,	0x0000004D) \
	b(JSONServerKMIPV1_2,	0x0000004E) \
	b(XMLClientKMIPV1_0,	0x0000004F) \
	b(XMLClientKMIPV1_1,	0x50) \
	b(XMLClientKMIPV1_2,	0x51) \
	b(XMLServerKMIPV1_0,	0x52) \
	b(XMLServerKMIPV1_1,	0x53) \
	b(XMLServerKMIPV1_2,	0x54) \
	b(BaselineServerBasicKMIPV1_3,	0x55) \
	b(BaselineServerTLSV1_2KMIPV1_3,	0x56) \
	b(BaselineClientBasicKMIPV1_3,	0x57) \
	b(BaselineClientTLSV1_2KMIPV1_3,	0x58) \
	b(CompleteServerBasicKMIPV1_3,	0x59) \
	b(CompleteServerTLSV1_2KMIPV1_3,	0x0000005A) \
	b(TapeLibraryClientKMIPV1_3,	0x0000005B) \
	b(TapeLibraryServerKMIPV1_3,	0x0000005C) \
	b(SymmetricKeyLifecycleClientKMIPV1_3,	0x0000005D) \
	b(SymmetricKeyLifecycleServerKMIPV1_3,	0x0000005E) \
	b(AsymmetricKeyLifecycleClientKMIPV1_3,	0x0000005F) \
	b(AsymmetricKeyLifecycleServerKMIPV1_3,	0x60) \
	b(BasicCryptographicClientKMIPV1_3,	0x61) \
	b(BasicCryptographicServerKMIPV1_3,	0x62) \
	b(AdvancedCryptographicClientKMIPV1_3,	0x63) \
	b(AdvancedCryptographicServerKMIPV1_3,	0x64) \
	b(RNGCryptographicClientKMIPV1_3,	0x65) \
	b(RNGCryptographicServerKMIPV1_3,	0x66) \
	b(BasicSymmetricKeyFoundryClientKMIPV1_3,	0x67) \
	b(IntermediateSymmetricKeyFoundryClientKMIPV1_3,	0x68) \
	b(AdvancedSymmetricKeyFoundryClientKMIPV1_3,	0x69) \
	b(SymmetricKeyFoundryServerKMIPV1_3,	0x0000006A) \
	b(OpaqueManagedObjectStoreClientKMIPV1_3,	0x0000006B) \
	b(OpaqueManagedObjectStoreServerKMIPV1_3,	0x0000006C) \
	b(SuiteBMinLOS_128ClientKMIPV1_3,	0x0000006D) \
	b(SuiteBMinLOS_128ServerKMIPV1_3,	0x0000006E) \
	b(SuiteBMinLOS_192ClientKMIPV1_3,	0x0000006F) \
	b(SuiteBMinLOS_192ServerKMIPV1_3,	0x70) \
	b(StorageArrayWithSelfEncryptingDriveClientKMIPV1_3,	0x71) \
	b(StorageArrayWithSelfEncryptingDriveServerKMIPV1_3,	0x72) \
	b(HTTPSClientKMIPV1_3,	0x73) \
	b(HTTPSServerKMIPV1_3,	0x74) \
	b(JSONClientKMIPV1_3,	0x75) \
	b(JSONServerKMIPV1_3,	0x76) \
	b(XMLClientKMIPV1_3,	0x77) \
	b(XMLServerKMIPV1_3,	0x78) \
	b(BaselineServerBasicKMIPV1_4,	0x79) \
	b(BaselineServerTLSV1_2KMIPV1_4,	0x0000007A) \
	b(BaselineClientBasicKMIPV1_4,	0x0000007B) \
	b(BaselineClientTLSV1_2KMIPV1_4,	0x0000007C) \
	b(CompleteServerBasicKMIPV1_4,	0x0000007D) \
	b(CompleteServerTLSV1_2KMIPV1_4,	0x0000007E) \
	b(TapeLibraryClientKMIPV1_4,	0x0000007F) \
	b(TapeLibraryServerKMIPV1_4,	0x80) \
	b(SymmetricKeyLifecycleClientKMIPV1_4,	0x81) \
	b(SymmetricKeyLifecycleServerKMIPV1_4,	0x82) \
	b(AsymmetricKeyLifecycleClientKMIPV1_4,	0x83) \
	b(AsymmetricKeyLifecycleServerKMIPV1_4,	0x84) \
	b(BasicCryptographicClientKMIPV1_4,	0x85) \
	b(BasicCryptographicServerKMIPV1_4,	0x86) \
	b(AdvancedCryptographicClientKMIPV1_4,	0x87) \
	b(AdvancedCryptographicServerKMIPV1_4,	0x88) \
	b(RNGCryptographicClientKMIPV1_4,	0x89) \
	b(RNGCryptographicServerKMIPV1_4,	0x0000008A) \
	b(BasicSymmetricKeyFoundryClientKMIPV1_4,	0x0000008B) \
	b(IntermediateSymmetricKeyFoundryClientKMIPV1_4,	0x0000008C) \
	b(AdvancedSymmetricKeyFoundryClientKMIPV1_4,	0x0000008D) \
	b(SymmetricKeyFoundryServerKMIPV1_4,	0x0000008E) \
	b(OpaqueManagedObjectStoreClientKMIPV1_4,	0x0000008F) \
	b(OpaqueManagedObjectStoreServerKMIPV1_4,	0x90) \
	b(SuiteBMinLOS_128ClientKMIPV1_4,	0x91) \
	b(SuiteBMinLOS_128ServerKMIPV1_4,	0x92) \
	b(SuiteBMinLOS_192ClientKMIPV1_4,	0x93) \
	b(SuiteBMinLOS_192ServerKMIPV1_4,	0x94) \
	b(StorageArrayWithSelfEncryptingDriveClientKMIPV1_4,	0x95) \
	b(StorageArrayWithSelfEncryptingDriveServerKMIPV1_4,	0x96) \
	b(HTTPSClientKMIPV1_4,	0x97) \
	b(HTTPSServerKMIPV1_4,	0x98) \
	b(JSONClientKMIPV1_4,	0x99) \
	b(JSONServerKMIPV1_4,	0x0000009A) \
	b(XMLClientKMIPV1_4,	0x0000009B) \
	b(XMLServerKMIPV1_4,	0x0000009C) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, PROFILE_NAME_LIST)
	KMIPProfileName(uint32_t eValue);
};

class KMIPUnwrapMode : public KMIPEnumeration {
#define UNWRAP_MODE_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(Processed,	0x2) \
	b(NotProcessed,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, UNWRAP_MODE_LIST)
	KMIPUnwrapMode(uint32_t eValue);
};

class KMIPDestroyAction : public KMIPEnumeration {
#define DESTROY_ACTION_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(KeyMaterialDeleted,	0x2) \
	b(KeyMaterialShredded,	0x3) \
	b(MetaDataDeleted,	0x4) \
	b(MetaDataShredded,	0x5) \
	b(Deleted,	0x6) \
	b(Shredded,	0x7) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, DESTROY_ACTION_LIST)
	KMIPDestroyAction(uint32_t eValue);
};

class KMIPShreddingAlgorithm : public KMIPEnumeration {
#define SHREDDING_ALGORITHM_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(Cryptographic,	0x2) \
	b(Unsupported,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, SHREDDING_ALGORITHM_LIST)
	KMIPShreddingAlgorithm(uint32_t eValue);
};

class KMIPRNGMode : public KMIPEnumeration {
#define RNG_MODE_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(SharedInstantiation,	0x2) \
	b(NonSharedInstantiation,	0x3) \
	a(NumValues)

	DECLARE_KMIPENUM_LIST(VALUE, RNG_MODE_LIST)
	KMIPRNGMode(uint32_t eValue);
};

class KMIPClientRegistrationMethod : public KMIPEnumeration {
#define CLIENT_REGISTRATION_METHOD_LIST(a,b) \
        b(Unknown,0)\
	b(Unspecified,	0x1) \
	b(ServerPreGenerated,	0x2) \
	b(ServerOnDemand,	0x3) \
	b(ClientGenerated,	0x4) \
	b(ClientRegistered,	0x5) \
	a(NumValues)


	DECLARE_KMIPENUM_LIST(VALUE, CLIENT_REGISTRATION_METHOD_LIST)
	KMIPClientRegistrationMethod(uint32_t eValue);
};

class KMIPKeyWrapType : public KMIPEnumeration {
#define KEY_WRAP_TYPE_LIST(a,b) \
        b(Unknown,0)\
	b(NotWrapped,	0x1) \
	b(AsRegistered,	0x2) \
	a(NumValues)


	DECLARE_KMIPENUM_LIST(VALUE, KEY_WRAP_TYPE_LIST)
	KMIPKeyWrapType(uint32_t eValue);
};

class KMIPMaskGenerator : public KMIPEnumeration {
#define MASK_GENERATOR_LIST(a,b) \
        b(Unknown,0)\
	b(MFG1,	0x1) \
	a(NumValues)


	DECLARE_KMIPENUM_LIST(VALUE, MASK_GENERATOR_LIST)
	KMIPMaskGenerator(uint32_t eValue);
};




#endif
