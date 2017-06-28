/* Copyright (C) 2017 Alexander Downey */
#include "KMIPTemplate.h"
#include "KMIPAttribute.h"
#include "KMIPEnumeration.h"


KMIPTemplate::KMIPTemplate() : KMIPManagedObject(kmip::TagTemplate) {}
int KMIPTemplate::getObjectType() const {
    return KMIPObjectType::Template;
}
        IMPLEMENT_GET_ADD_FIELDS(KMIPTemplate, KMIPAttribute, Attribute, kmip::TagAttribute);
