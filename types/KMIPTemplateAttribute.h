/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPTEMPLATEATTRIBUTE_H
#define _KMIPTEMPLATEATTRIBUTE_H

#include "KMIPStruct.h"

class KMIPName;
class KMIPAttribute;
class KMIPTemplateAttributeStruct : public KMIPStruct {
    public:
        DECLARE_GET_ADD_FIELDS(KMIPAttribute, Attribute);
        DECLARE_GET_ADD_FIELDS(KMIPName, Name);
    protected:
        KMIPTemplateAttributeStruct(int iTag);
};


class KMIPTemplateAttribute : public KMIPTemplateAttributeStruct {
    public:
        KMIPTemplateAttribute();
};

class KMIPCommonTemplateAttribute : public KMIPTemplateAttributeStruct {
    public:
        KMIPCommonTemplateAttribute();
};


class KMIPPrivateKeyTemplateAttribute : public KMIPTemplateAttributeStruct {
    public:
        KMIPPrivateKeyTemplateAttribute();
};

class KMIPPublicKeyTemplateAttribute : public KMIPTemplateAttributeStruct {
    public:
        KMIPPublicKeyTemplateAttribute();
};

#endif
