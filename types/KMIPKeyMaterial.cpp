/* Copyright (C) 2017 Alexander Downey */
#include "KMIPKeyMaterial.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"

KMIPKeyMaterial::KMIPKeyMaterial() : KMIPStruct(kmip::TagKeyMaterial) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, ByteString, std::string, Key, kmip::TagKey);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, P, kmip::TagP);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, Q, kmip::TagQ);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, G, kmip::TagG);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, X, kmip::TagX);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, Y, kmip::TagY);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, J, kmip::TagJ);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, Modulus, kmip::TagModulus);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, PrivateExponent, kmip::TagPrivateExponent);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, PublicExponent, kmip::TagPublicExponent);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, PrimeExponentP, kmip::TagPrimeExponentP);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, PrimeExponentQ, kmip::TagPrimeExponentQ);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, CRTCoefficient, kmip::TagCRTCoefficient);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, Enumeration, uint32_t, RecommendedCurve, kmip::TagRecommendedCurve);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, D, kmip::TagD);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyMaterial, BigInteger, std::string, QString, kmip::TagQString);
