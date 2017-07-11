/* Copyright (C) 2017 Alexander Downey */
#include "KMIPDatabaseRaw.h"
#include "SQLQuery.h"
#include "SQLResult.h"
#include "KMIPAttribute.h"
#include "KMIPUtils.h"
#include "HexUtils.h"
#include "KMIPManagedObject.h"
#include "KMIPTTLVEncoding.h"


KMIPDatabaseRaw::KMIPDatabaseRaw(const std::string &sDatabase) : KMIPDatabase(sDatabase) {
}

DBAttributeMap KMIPDatabaseRaw::getAttributes(const std::list<std::string> &listIDs) {
    DBAttributeMap mapRet;
    bool bOK = (spconn && spconn->is_open()) || connect(sDatabaseStr);
    if (bOK) {
        std::string sQuery = "SELECT * FROM Attributes WHERE uniqueid IN (";
        std::string sSet;
        for (auto sID : listIDs) {
            if (!sSet.empty()) {
                sSet += ",";
            }

            sSet += spconn->quote_name(sID);
        }

        sQuery += sSet + ");";

        auto res = runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
        for (auto tuple : res) {
            std::shared_ptr<KMIPAttribute> spattr(new KMIPAttribute);
            std::string sUniqueID;
            std::string sName;
            int iIndex = 0;
            int iType = kmip::TypeTextString;
            std::string sValue;
            tuple[0].to(sUniqueID);
            tuple[1].to(sName);
            tuple[2].to(iIndex);
            tuple[3].to(sValue);
            tuple[4].to(iType);
            spattr->setName(sName);
            spattr->setIndex(iIndex);
            std::shared_ptr<KMIPField> spkf = KMIPUtils::createField(KMIPAttribute::getNameTag(sName), iType);
            spkf->setValueFromTTLV(HexUtils::hexDecode(sValue));
            spattr->setValue(spkf);
            mapRet[sUniqueID].push_back(spattr);
        }
    }

    return mapRet;
}

DBObjectMap KMIPDatabaseRaw::getObjects(const std::list<std::string> &listIDs) {
    DBObjectMap mapRet;
    bool bOK = (spconn && spconn->is_open()) || connect(sDatabaseStr);
    if (bOK) {
        std::string sQuery = "SELECT * FROM managedobject WHERE uniqueid IN (";
        std::string sSet;
        for (auto sID : listIDs) {
            if (!sSet.empty()) {
                sSet += ",";
            }

            sSet += spconn->quote_name(sID);
        }

        sQuery += sSet + ");";

        auto res = runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
        DBAttributeMap mapAttrs;
        if (res.getSuccess()) {
            mapAttrs = getAttributes(listIDs);
        }

        for (auto tuple : res) {
            std::string sUniqueID;
            std::string sValue;
            tuple[0].to(sUniqueID);
            tuple[1].to(sValue);
            KMIPFieldSP spkf(KMIPTTLVEncoding().decodeKMIP(HexUtils::hexDecode(sValue)).release());
            std::shared_ptr<KMIPManagedObject> spko = std::static_pointer_cast<KMIPManagedObject>(spkf);
            mapRet[sUniqueID].push_back(spko);
            for (auto attr : mapAttrs[sUniqueID]) {
                spko->addAttribute(attr.get());
            }
        }
    }

    return mapRet;
}

int KMIPDatabaseRaw::deleteAttributes(const std::list<std::string> &listIDs) {
    int iRet = 0;
    bool bOK = (spconn && spconn->is_open()) || connect(sDatabaseStr);
    if (bOK) {
        std::string sQuery = "DELETE FROM attributes WHERE uniqueid IN (";
        std::string sSet;
        for (auto sID : listIDs) {
            if (!sSet.empty()) {
                sSet += ",";
            }

            sSet += spconn->quote_name(sID);
        }

        sQuery += sSet + ");";

        auto res = runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
        if (res.getSuccess()) {
            iRet = res.affected_rows();
        } else {
            iRet = -1;
        }
    }

    return iRet;
}

int KMIPDatabaseRaw::deleteObjects(const std::list<std::string> &listIDs) {
    int iRet = 0;
    bool bOK = deleteAttributes(listIDs) >= 0;
    if (bOK) {
        std::string sQuery = "DELETE FROM managedobject WHERE uniqueid IN (";
        std::string sSet;
        for (auto sID : listIDs) {
            if (!sSet.empty()) {
                sSet += ",";
            }

            sSet += spconn->quote_name(sID);
        }

        sQuery += sSet + ");";

        auto res = runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
        if (res.getSuccess()) {
            iRet = res.affected_rows();
        } else {
            iRet = -1;
        }
    }

    return iRet;
}

int KMIPDatabaseRaw::addObjects(const std::list<std::shared_ptr<KMIPManagedObject> > &listObjects) {
    int iRet = 0;
    bool bOK = (spconn && spconn->is_open()) || connect(sDatabaseStr);
    if (bOK) {
        KMIPTTLVEncoding kttlve;
        std::string sQuery = "INSERT INTO managedobject VALUES ";
        for (auto spko : listObjects) {
            if (spko) {
                sQuery += "(" + spko->getUniqueID() + "," + kttlve.encodeKMIP(spko.get()) + "),";
            }
        }

        if (sQuery.back() == ',') {
            sQuery.back() = ';';
        } else {
            sQuery += ";";
        }

        auto res = runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
        if (res.getSuccess()) {
            iRet = res.affected_rows();
        } else {
            iRet = -1;
        }

        sQuery = "INSERT INTO attributes VALUES ";
        for (auto spko : listObjects) {
            if (spko) {
                std::string sID = spko->getUniqueID();
                for (auto nameIter : spko->getAttributeMap()) {
                    for (auto indexIter : nameIter.second) {
                        KMIPFieldSP spkf = indexIter.second->getValue();
                        std::string sValue = spkf ? HexUtils::hexEncode(spkf->getTTLVValue()) : std::string();
                        std::string sType = spkf ? std::to_string(spkf->getType()) : std::to_string(kmip::TypeTextString);
                        sQuery += "(" + sID + "," + indexIter.second->getName() + "," + std::to_string(indexIter.second->getIndex()) + "," + sValue + "," + sValue +  "),";
                    }
                }
            }
        }

        if (sQuery.back() == ',') {
            sQuery.back() = ';';
        } else {
            sQuery += ";";
        }

        runQuery(std::shared_ptr<SQLQuery>(new SQLQueryRaw(sQuery)));
    }

    return iRet;
}

std::list<std::string> KMIPDatabaseRaw::locate(const std::list<std::shared_ptr<KMIPAttribute> > &listAttributes,
        int iMaxItems, int iOffset, int iStorageStatusMask, uint32_t iObjectGroupMember) {}
