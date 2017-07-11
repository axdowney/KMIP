/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMANAGEDOBJECT_H
#define _KMIPMANAGEDOBJECT_H

#include <string>
#include <map>
#include <memory>

#include "KMIPStruct.h"

class KMIPAttribute;
class KMIPManagedObject : public KMIPStruct {
    public:
        virtual int getObjectType() const;
        std::map<std::string, std::map<int, std::shared_ptr<KMIPAttribute> > > getAttributeMap();
        std::shared_ptr<KMIPAttribute> getAttribute(const std::string &sName, int iIndex = 0) const;

        template<typename T,typename V>
        bool findAttributeValue(const std::string &sName, int iIndex, V &val) const;

        template<typename T,typename V>
        V getAttributeValue(const std::string &sName, int iIndex, const V &val) const;

        template<typename T>
        std::shared_ptr<T> getAttributeValueField(const std::string &sName, int iIndex);

        template<typename T,typename V>
        bool setAttributeValue(const std::string &sName, int iIndex, V &val) const;

        bool hasAttribute(const std::string &sName, int iIndex) const;
        bool hasAttribute(const std::string &sName) const;

        bool addAttribute(KMIPAttribute *pka);
        bool modifyAttribute(const std::string &sName, int iIndex, std::shared_ptr<KMIPField> spkfValue, bool bAdd = false);
        bool deleteAttribute(const std::string &sName, int iIndex = 0);
        bool deleteAllAttributes(const std::string &sName = "");

        int getNextIndex(const std::string &sName) const;

        static bool isAttributeAddable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer);
        static bool isAttributeModifiable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer);
        static bool isAttributeDeletable(int iObjectType, const std::string &sName, int iIndex, int iOperation, bool bServer);

        bool isAttributeAddable(const std::string &sName, int iIndex, KMIPField *pkfValue, int iOperation, bool bServer) const;
        bool isAttributeModifiable(const std::string &sName, int iIndex, KMIPField *pkfValue, int iOperation, bool bServer) const;
        bool isAttributeDeletable(const std::string &sName, int iIndex, int iOperation, bool bServer) const;

        bool isAttributeAddable(KMIPAttribute *pka, int iOperation, bool bServer) const;
        bool isAttributeModifiable(KMIPAttribute *pka, int iOperation, bool bServer) const;
        bool isAttributeDeletable(KMIPAttribute *pka, int iOperation, bool bServer) const;

        std::string getUniqueID() const;
        bool setUniqueID(const std::string &sID);

    protected:
        KMIPManagedObject(int iTag);
        std::map<std::string, std::map<int, std::shared_ptr<KMIPAttribute> > > mapNameToMapIndexToAttribute;
        std::shared_ptr<KMIPAttribute> getAttributePrivate(const std::string &sName, int iIndex = 0) const;

};

typedef std::unique_ptr<KMIPManagedObject> KMIPManagedObjectUP;
typedef std::shared_ptr<KMIPManagedObject> KMIPManagedObjectSP;

template<typename T,typename V>
bool KMIPManagedObject::findAttributeValue(const std::string &sName, int iIndex, V &val) const {
    std::shared_ptr<KMIPAttribute> spAttr = getAttributePrivate(sName, iIndex);
    bool bRet = spAttr;
    if (spAttr) {
        bRet = std::dynamic_pointer_cast<KMIPStruct>(spAttr)->findChildValue<T>(kmip::TagAttributeValue, val);
    }

    return bRet;
}

template<typename T,typename V>
V KMIPManagedObject::getAttributeValue(const std::string &sName, int iIndex, const V &val) const {
    V valRet = V();
    if (!findAttributeValue<T>(sName, iIndex, valRet)) {
        valRet = val;
    }

    return valRet;
}

template<typename T>
std::shared_ptr<T> KMIPManagedObject::getAttributeValueField(const std::string &sName, int iIndex) {
    std::shared_ptr<T> spRet;
    std::shared_ptr<KMIPAttribute> spAttr = getAttributePrivate(sName, iIndex);
    if (spAttr) {
        spRet = std::dynamic_pointer_cast<KMIPStruct>(spAttr)->getChildValue<T>(kmip::TagAttributeValue);
    }

    return spRet;
}

template<typename T,typename V>
bool KMIPManagedObject::setAttributeValue(const std::string &sName, int iIndex, V &val) const {
    std::shared_ptr<T> spkf = getAttributeValueField<T>(sName, iIndex);
    if (spkf) {
        spkf->setValue(val);
    } else {
        spkf.reset(KMIPUtils::createField());
    }
}

#endif
