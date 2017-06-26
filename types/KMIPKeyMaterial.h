/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPKEYMATERIAL_H
#define _KMIPKEYMATERIAL_H
#include "KMIPStruct.h"

class KMIPKeyMaterial : public KMIPStruct {
    public:
        KMIPKeyMaterial();
        DECLARE_GET_SET_FIELD_VALUE(std::string, Key);
        DECLARE_GET_SET_FIELD_VALUE(std::string, P);
        DECLARE_GET_SET_FIELD_VALUE(std::string, Q);
        DECLARE_GET_SET_FIELD_VALUE(std::string, G);
        DECLARE_GET_SET_FIELD_VALUE(std::string, X);
        DECLARE_GET_SET_FIELD_VALUE(std::string, Y);
        DECLARE_GET_SET_FIELD_VALUE(std::string, J);
        DECLARE_GET_SET_FIELD_VALUE(std::string, Modulus);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PrivateExponent);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PublicExponent);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PrimeExponentP);
        DECLARE_GET_SET_FIELD_VALUE(std::string, PrimeExponentQ);
        DECLARE_GET_SET_FIELD_VALUE(std::string, CRTCoefficient);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, RecommendedCurve);
        DECLARE_GET_SET_FIELD_VALUE(std::string, D);
        DECLARE_GET_SET_FIELD_VALUE(std::string, QString);
};



#endif
