/* Copyright (C) 2017 Alexander Downey */
#include "KMIPManagedObject.h"
#include "KMIPEnumeration.h"
#include "KMIPAttribute.h"
#include "KMIPAttributeRule.h"
#include "KMIPString.h"


KMIPManagedObject::KMIPManagedObject(int iTag) : KMIPStruct(iTag) {
}

int KMIPManagedObject::getObjectType() const {
    return KMIPObjectType::Unknown;
}

std::map<std::string, std::map<int, std::shared_ptr<KMIPAttribute> > > KMIPManagedObject::getAttributeMap() {
    return mapNameToMapIndexToAttribute;
}

std::shared_ptr<KMIPAttribute> KMIPManagedObject::getAttribute(const std::string &sName, int iIndex) const {
    std::shared_ptr<KMIPAttribute> spka = getAttributePrivate(sName, iIndex);
    return spka ? spka->cloneShared<KMIPAttribute>() : spka;
}

std::shared_ptr<KMIPAttribute> KMIPManagedObject::getAttributePrivate(const std::string &sName, int iIndex) const {
    std::shared_ptr<KMIPAttribute> spka;
    auto nameIter = mapNameToMapIndexToAttribute.find(sName);
    if (nameIter != mapNameToMapIndexToAttribute.end()) {
        auto indexIter = nameIter->second.find(iIndex);
        if (indexIter != nameIter->second.end()) {
            spka = indexIter->second;
        }
    }

    return spka;
}

bool KMIPManagedObject::hasAttribute(const std::string &sName, int iIndex) const {
    auto nameIter = mapNameToMapIndexToAttribute.find(sName);
    return nameIter != mapNameToMapIndexToAttribute.end() && nameIter->second.find(iIndex) != nameIter->second.end();
}

bool KMIPManagedObject::hasAttribute(const std::string &sName) const {
    auto nameIter = mapNameToMapIndexToAttribute.find(sName);
    return nameIter != mapNameToMapIndexToAttribute.end() && !nameIter->second.empty();
}

bool KMIPManagedObject::addAttribute(KMIPAttribute *pka) {
    bool bRet = pka && !hasAttribute(pka->getName(), pka->getIndex());
    if (bRet) {
        std::shared_ptr<KMIPAttribute> spka = pka->cloneShared<KMIPAttribute>();
        if (spka) {
            mapNameToMapIndexToAttribute[pka->getName()][pka->getIndex()] = spka;
        } else {
            bRet = false;
        }
    }

    return bRet;
}

bool KMIPManagedObject::modifyAttribute(const std::string &sName, int iIndex, KMIPFieldSP spkfValue, bool bAdd) {
    bool bRet = static_cast<bool>(spkfValue);
    if (bRet) {
        std::shared_ptr<KMIPAttribute> spka = getAttributePrivate(sName, iIndex);
        if (spka) {
            bRet = spka->setValue(spkfValue);
        } else if (bAdd) {
            spka.reset(new KMIPAttribute(sName, iIndex, spkfValue));
            mapNameToMapIndexToAttribute[sName][iIndex] = spka;
        } else {
            bRet = false;
        }
    }

    return bRet;
}

bool KMIPManagedObject::deleteAttribute(const std::string &sName, int iIndex) {
    bool bRet = false;
    std::shared_ptr<KMIPAttribute> spka;
    auto nameIter = mapNameToMapIndexToAttribute.find(sName);
    if (nameIter != mapNameToMapIndexToAttribute.end()) {
        auto indexIter = nameIter->second.find(iIndex);
        if (indexIter != nameIter->second.end()) {
            nameIter->second.erase(indexIter);
            bRet = true;
            if (nameIter->second.empty()) {
                mapNameToMapIndexToAttribute.erase(nameIter);
            }
        }
    }

    return bRet;
}

int KMIPManagedObject::getNextIndex(const std::string &sName) const {
    int iRet = 0;
    auto nameIter = mapNameToMapIndexToAttribute.find(sName);
    if (nameIter != mapNameToMapIndexToAttribute.end()) {
        if (!nameIter->second.empty()) {
            iRet = nameIter->second.rbegin()->first + 1;
        }
    }

    return iRet;
}

/* In general */
bool KMIPManagedObject::isAttributeAddable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer) {
    std::shared_ptr<KMIPAttributeRule> spkar = KMIPUtils::getAttributeRule(KMIPAttribute::getNameTag(sName));
    return spkar && spkar->isAttributeAddable(iObjectType, iObjectType, iOperation, bServer);
}

bool KMIPManagedObject::isAttributeModifiable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer) {
    std::shared_ptr<KMIPAttributeRule> spkar = KMIPUtils::getAttributeRule(KMIPAttribute::getNameTag(sName));
    return spkar && spkar->isAttributeModifiable(iObjectType, iObjectType, iOperation, bServer);
}

bool KMIPManagedObject::isAttributeDeletable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer) {
    std::shared_ptr<KMIPAttributeRule> spkar = KMIPUtils::getAttributeRule(KMIPAttribute::getNameTag(sName));
    return spkar && spkar->isAttributeDeletable(iObjectType, iObjectType, iOperation, bServer);
}

/* In particular */
bool KMIPManagedObject::isAttributeAddable(const std::string &sName, int iIndex, KMIPField *pkfValue, int iOperation, bool bServer) const {
    return pkfValue && isAttributeAddable(getObjectType(), sName, iIndex, iOperation, bServer)
        && !hasAttribute(sName, iIndex);
}
        
bool KMIPManagedObject::isAttributeModifiable(const std::string &sName, int iIndex, KMIPField *pkfValue, int iOperation, bool bServer) const {
    return pkfValue && isAttributeModifiable(getObjectType(), sName, iIndex, iOperation, bServer) && hasAttribute(sName, iIndex);
}
        
bool KMIPManagedObject::isAttributeDeletable(const std::string &sName, int iIndex, int iOperation, bool bServer) const {
    return isAttributeDeletable(getObjectType(), sName, iIndex, iOperation, bServer) && hasAttribute(sName, iIndex);
}

/* Particular Object and Attribute */        
bool KMIPManagedObject::isAttributeAddable(KMIPAttribute *pka, int iOperation, bool bServer) const {
    return pka && isAttributeAddable(pka->getName(), pka->getIndex(), pka->getValue().get(), iOperation, bServer);
}

bool KMIPManagedObject::isAttributeModifiable(KMIPAttribute *pka, int iOperation, bool bServer) const {
    return pka && isAttributeModifiable(pka->getName(), pka->getIndex(), pka->getValue().get(), iOperation, bServer);
}
        
bool KMIPManagedObject::isAttributeDeletable(KMIPAttribute *pka, int iOperation, bool bServer) const {
    return pka && isAttributeDeletable(pka->getName(), pka->getIndex(), iOperation, bServer);
}

std::string KMIPManagedObject::getUniqueID() const {
    return getAttributeValue<KMIPTextString>(KMIPAttribute::getNameFromTag(kmip::TagUniqueIdentifier),0,std::string());
}

bool KMIPManagedObject::setUniqueID(const std::string &sID) {
    return setAttributeValue<KMIPTextString>(KMIPAttribute::getNameFromTag(kmip::TagUniqueIdentifier), 0, sID);
}
