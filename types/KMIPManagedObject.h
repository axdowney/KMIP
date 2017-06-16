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
        bool hasAttribute(const std::string &sName, int iIndex) const;
        bool hasAttribute(const std::string &sName) const;

        bool addAttribute(KMIPAttribute *pka);
        bool modifyAttribute(const std::string &sName, int iIndex, std::shared_ptr<KMIPField> spkfValue);
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
    protected:
        KMIPManagedObject(int iTag);
        std::map<std::string, std::map<int, std::shared_ptr<KMIPAttribute> > > mapNameToMapIndexToAttribute;

};

#endif
