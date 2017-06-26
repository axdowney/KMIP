/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPKEYBLOCK_H
#define _KMIPKEYBLOCK_H

#include "KMIPStruct.h"
class KMIPKeyWrappingData;
class KMIPKeyMaterial;
class KMIPAttribute;


class KMIPKeyValue : public KMIPStruct {
    public:
        KMIPKeyValue();
        DECLARE_GET_SET_FIELD(KMIPField, KeyMaterial);
        DECLARE_GET_SET_FIELD(KMIPKeyMaterial, KeyMaterialStruct);
        DECLARE_GET_SET_FIELD_VALUE(std::string, KeyMaterialString);

        DECLARE_GET_ADD_FIELDS(KMIPAttribute, Attribute);
};



class KMIPKeyBlock : public KMIPStruct {
    public:
        KMIPKeyBlock();
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, KeyFormatType);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, KeyCompressionType);
        DECLARE_GET_SET_FIELD(KMIPField, KeyValue);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, CryptographicAlgorithm);
        DECLARE_GET_SET_FIELD_VALUE(int, CryptographicLength);
        DECLARE_GET_SET_FIELD(KMIPKeyWrappingData, KeyWrappingData);

        DECLARE_GET_SET_FIELD_VALUE(std::string, KeyValueString);
        DECLARE_GET_SET_FIELD(KMIPKeyValue, KeyValueStruct);
};

#endif
