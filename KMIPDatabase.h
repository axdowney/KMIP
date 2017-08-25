/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPDATABASE_H
#define _KMIPDATABASE_H

#include <string>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>

#include "DatabaseObject.h"
#include "KMIPTemplateAttribute.h"


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
        virtual int addObject(std::shared_ptr<KMIPManagedObject> spObject) {
            std::list<std::shared_ptr<KMIPManagedObject> > listObjects;
            listObjects.push_back(spObject);
            return addObjects(listObjects);
        }

        virtual std::list<std::string> locate(const std::list<std::shared_ptr<KMIPAttribute> > &listAttributes, int iMaxItems, int iOffset, int iStorageStatusMask, uint32_t iObjectGroupMember)=0;

        virtual std::string getNextID(int iMOType)=0;

        virtual std::string makeID(int iMOType) const {
            std::stringstream ss;
            ss << std::setw(getIDTypeWidth()) << std::setfill('0') << iMOType;
            return ss.str();
        }

        virtual std::string makeID(int iMOType, long int liID) const {
            return makeID(iMOType) + std::to_string(liID);
        }

        virtual bool getIDParts(const std::string &sID, int &iMOType, long int &liID) const {
            bool bRet = sID.size() > getIDTypeWidth();
            if (bRet) {
                iMOType = std::stoi(sID.substr(0, getIDTypeWidth()));
                liID = std::stol(sID.substr(getIDTypeWidth()));
            }

            return bRet;
        }

        virtual bool gatherAttributes(std::shared_ptr<KMIPTemplateAttribute> spkta, std::list<std::shared_ptr<KMIPAttribute> > &listAttributes) {
            if (spkta) {
                listAttributes = spkta->getAttributes();
            }

            return true;
        }

    protected:
        std::string sDatabaseStr;
        virtual int getIDTypeWidth() const {return 3;}
};


#endif
