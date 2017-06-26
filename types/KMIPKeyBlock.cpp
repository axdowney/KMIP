/* Copyright (C) 2017 Alexander Downey */
#include "KMIPKeyBlock.h"
#include "KMIPKeyMaterial.h"
#include "KMIPKeyWrappingData.h"
#include "KMIPAttribute.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"



KMIPKeyValue::KMIPKeyValue() : KMIPStruct(kmip::TagKeyValue) {}
        IMPLEMENT_GET_SET_FIELD(KMIPKeyValue, KMIPField, KeyMaterial, kmip::TagKeyMaterial);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyValue, KMIPKeyMaterial, KeyMaterialStruct, kmip::TagKeyMaterial);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyValue, ByteString, std::string, KeyMaterialString, kmip::TagKeyMaterial);
        IMPLEMENT_GET_ADD_FIELDS(KMIPKeyValue, KMIPAttribute, Attribute, kmip::TagAttribute);

KMIPKeyBlock::KMIPKeyBlock() : KMIPStruct(kmip::TagKeyBlock) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyBlock, Enumeration, uint32_t, KeyFormatType, kmip::TagKeyFormatType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyBlock, Enumeration, uint32_t, KeyCompressionType, kmip::TagKeyCompressionType);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyBlock, KMIPField, KeyValue, kmip::TagKeyValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyBlock, Enumeration, uint32_t, CryptographicAlgorithm, kmip::TagCryptographicAlgorithm);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyBlock, Integer, int, CryptographicLength, kmip::TagCryptographicLength);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyBlock, KMIPKeyWrappingData, KeyWrappingData, kmip::TagKeyWrappingData);

        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPKeyBlock, ByteString, std::string, KeyValueString, kmip::TagKeyValue);
        IMPLEMENT_GET_SET_FIELD(KMIPKeyBlock, KMIPKeyValue, KeyValueStruct, kmip::TagKeyValue);
