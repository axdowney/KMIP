/* Copyright (C) 2017 Alexander Downey */
#include "KMIPOpaqueObject.h"
#include "KMIPDefs.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"

KMIPOpaqueObject::KMIPOpaqueObject() : KMIPManagedObject(kmip::TagOpaqueObject) {}
KMIPOpaqueObject::KMIPOpaqueObject(uint32_t eType, const std::string &sValue) : KMIPManagedObject(kmip::TagOpaqueObject) {
    setOpaqueDataType(eType);
    setOpaqueDataValue(sValue);
}
int KMIPOpaqueObject::getObjectType() const {
    return KMIPObjectType::OpaqueObject;
}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPOpaqueObject, Enumeration, uint32_t, OpaqueDataType, kmip::TagOpaqueDataType);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPOpaqueObject, ByteString, std::string, OpaqueDataValue, kmip::TagOpaqueDataValue);
