/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPDATABASERAW_H
#define _KMIPDATABASERAW_H

#include <map>
#include <string>

#include "KMIPDatabase.h"

class KMIPDatabaseRaw : public KMIPDatabase {
    public:
        KMIPDatabaseRaw(const std::string &sDatabase);

        virtual DBAttributeMap getAttributes(const std::list<std::string> &listIDs);
        virtual DBObjectMap getObjects(const std::list<std::string> &listIDs);

        virtual int deleteAttributes(const std::list<std::string> &listIDs);
        virtual int deleteObjects(const std::list<std::string> &listIDs);

        virtual int addObjects(const std::list<std::shared_ptr<KMIPManagedObject> > &listObjects);

        virtual std::list<std::string> locate(const std::list<std::shared_ptr<KMIPAttribute> > &listAttributes, int iMaxItems, int iOffset, int iStorageStatusMask, uint32_t iObjectGroupMember);
        virtual std::string getNextID(int iMOType);

    protected:
        std::map<int, long int> mapTypeToID;
};

#endif
