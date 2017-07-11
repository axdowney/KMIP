/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPDATABASE_H
#define _KMIPDATABASE_H

#include <string>
#include <list>
#include <map>
#include <memory>

#include "DatabaseObject.h"


class KMIPManagedObject;
class KMIPAttribute;
typedef std::map<std::string, std::list<std::shared_ptr<KMIPAttribute> > > DBAttributeMap;
typedef std::map<std::string, std::list<std::shared_ptr<KMIPManagedObject> > > DBObjectMap;
class KMIPDatabase : public DatabaseObject {
    public:
        explicit KMIPDatabase(const std::string &sDatabase = "") : sDatabaseStr(sDatabase) {}
        virtual DBAttributeMap getAttributes(const std::list<std::string> &listIDs)=0;
        virtual DBObjectMap getObjects(const std::list<std::string> &listIDs)=0;

        virtual int deleteAttributes(const std::list<std::string> &listIDs)=0;
        virtual int deleteObjects(const std::list<std::string> &listIDs)=0;

        virtual int addObjects(const std::list<std::shared_ptr<KMIPManagedObject> > &listObjects)=0;

        virtual std::list<std::string> locate(const std::list<std::shared_ptr<KMIPAttribute> > &listAttributes, int iMaxItems, int iOffset, int iStorageStatusMask, uint32_t iObjectGroupMember)=0;

    protected:
        std::string sDatabaseStr;
};


#endif
