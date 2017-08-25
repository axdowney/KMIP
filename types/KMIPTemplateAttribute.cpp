/* Copyright (C) 2017 Alexander Downey */
#include "KMIPTemplateAttribute.h"
#include "KMIPAttribute.h"
#include "KMIPAttributeStructs.h"



        IMPLEMENT_GET_ADD_FIELDS(KMIPTemplateAttributeStruct, KMIPAttribute, Attribute, kmip::TagAttribute);
        IMPLEMENT_GET_ADD_FIELDS(KMIPTemplateAttributeStruct, KMIPName, Name, kmip::TagName);
KMIPTemplateAttributeStruct::KMIPTemplateAttributeStruct(int iTag) : KMIPStruct(iTag) {}
KMIPTemplateAttribute::KMIPTemplateAttribute() : KMIPTemplateAttributeStruct(kmip::TagTemplateAttribute) {}
KMIPCommonTemplateAttribute::KMIPCommonTemplateAttribute() : KMIPTemplateAttributeStruct(kmip::TagCommonTemplateAttribute) {}
KMIPPrivateKeyTemplateAttribute::KMIPPrivateKeyTemplateAttribute() : KMIPTemplateAttributeStruct(kmip::TagPrivateKeyTemplateAttribute) {}
KMIPPublicKeyTemplateAttribute::KMIPPublicKeyTemplateAttribute() : KMIPTemplateAttributeStruct(kmip::TagPublicKeyTemplateAttribute) {}
