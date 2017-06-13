/* Copyright (C) 2017 Alexander Downey */
#include "KMIPAttribute.h"
#include "KMIPString.h"
#include "KMIPNumber.h"
#include "KMIPDefs.h"


KMIPAttribute::KMIPAttribute() : KMIPStruct(kmip::TagAttribute) {}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldUP upkfValue) : KMIPAttribute(sName, iIndex, upkfValue.release()) {
}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPField *pkfValue) : KMIPAttribute(sName, iIndex, KMIPFieldSP(pkfValue)) {
}

KMIPAttribute::KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldSP spkfValue) : KMIPStruct(kmip::TagAttribute) {
    setName(sName);
    setIndex(iIndex);
    setValue(spkfValue);
}

std::string KMIPAttribute::getName() const {
    return getChildValue<KMIPTextString>(kmip::TagAttributeName, std::string());
}

bool KMIPAttribute::setName(const std::string &sNewName) {
    return setOrderedTextString(kmip::TagAttributeName, sNewName);
}

int KMIPAttribute::getIndex() const {
    return getChildValue<KMIPInteger>(kmip::TagAttributeIndex, 0);
}

bool KMIPAttribute::setIndex(int iNewIndex) {
    return setOrderedInteger(kmip::TagAttributeIndex, iNewIndex);
}

KMIPFieldSP KMIPAttribute::getValue() {
    return getChild<KMIPField>(kmip::TagAttributeValue);
}

KMIPFieldSPK KMIPAttribute::getValue() const {
    return getChild<KMIPField>(kmip::TagAttributeValue);
}

bool KMIPAttribute::setValue(KMIPFieldSP spkfValue) {
    spkfValue->forceAttributeValue(true);
    return addOrderedField(spkfValue);
}
