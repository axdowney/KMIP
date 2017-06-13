/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPSTRUCT_H
#define _KMIPSTRUCT_H

#include "KMIPField.h"
#include "KMIPFieldOrder.h"
#include "KMIPDefs.h"
#include "DateTime.h"
#include "KMIPUtils.h"

#include <list>
#include <memory>

class KMIPStruct : public KMIPField {
    public:
        explicit KMIPStruct(int iTag);
        bool addField(const std::shared_ptr<KMIPField> &spkf);
        bool addOrderedField(const std::shared_ptr<KMIPField> &spkf, bool bReplace = true);
        bool removeField(int iTag);
        bool removeField(int iTag, int iIndex);
        std::list<std::shared_ptr<KMIPField> > getFields() const;

        bool setOrderedInteger(int iTag, int iVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedLongInteger(int iTag, long int liVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedBigInteger(int iTag, const std::string &sVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedEnumeration(int iTag, uint32_t uiVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedBoolean(int iTag, bool bVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedTextString(int iTag, const std::string &sVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedByteString(int iTag, const std::string &sVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedDateTime(int iTag, const DateTime &dtVal, int iIndex = 0, bool bCreate = true);
        bool setOrderedInterval(int iTag, uint32_t uiVal, int iIndex = 0, bool bCreate = true);


        virtual kmipsize_t calculateLength() const;
        virtual kmipsize_t setCalculatedLength();

        bool hasOrder() const;
        bool isOrdered() const;
        virtual bool isValid() const;

        size_t getFieldNumber(int iTag = kmip::TagUnknown, int iType = kmip::TypeUnknown) const;
        
        template<typename t>
        std::shared_ptr<t> getChild(int iTag, int iType = kmip::TypeUnknown, int iIndex = 0);
        
        template<typename t>
        std::shared_ptr<const t> getChild(int iTag, int iType = kmip::TypeUnknown, int iIndex = 0) const;
        
        template<typename t>
        std::list<std::shared_ptr<t> > getChildren(int iTag = kmip::TagUnknown, int iType = kmip::TypeUnknown);

        template<typename t, typename v>
        v getChildValue(int iTag, const v &val, int iIndex = 0) const;

        template<typename t, typename v>
        bool findChildValue(int iTag, v &val, int iIndex = 0) const;

        template<typename t, typename v>
        bool setChildValue(int iTag, const v &val, int iIndex = 0);

        template<typename t, typename v>
        bool addOrderedChild(int iTag, int iType, const v &val);

        virtual std::string getTTLVValue() const;
    protected:
        std::list<std::shared_ptr<KMIPField> > listFields;
        KMIPFieldOrder *pkfo;
};


template<typename t>
std::shared_ptr<t> KMIPStruct::getChild(int iTag, int iType, int iIndex) {
    std::shared_ptr<t> spkfRet;
    int iCount = 0;
    for (auto spkf : listFields) {
        if (spkf && spkf->getTag() == iTag && (iType == kmip::TypeUnknown || spkf->getType() == iType)) {
            spkfRet = std::dynamic_pointer_cast<t>(spkf);
            if (spkfRet) {
                if (iIndex < 0 || iCount == iIndex) {
                    break;
                } else {
                    ++iCount;
                }
            }
        }
    }

    return spkfRet;
}

template<typename t>
std::shared_ptr<const t> KMIPStruct::getChild(int iTag, int iType, int iIndex) const {
    std::shared_ptr<const t> spkfRet;
    int iCount = 0;
    for (auto spkf : listFields) {
        if (spkf && spkf->getTag() == iTag && (iType == kmip::TypeUnknown || spkf->getType() == iType)) {
            spkfRet = std::dynamic_pointer_cast<const t>(spkf);
            if (spkfRet) {
                if (iIndex < 0 || iCount == iIndex) {
                    break;
                } else {
                    ++iCount;
                }
            }
        }
    }

    return spkfRet;
}

template<typename t>
std::list<std::shared_ptr<t> > KMIPStruct::getChildren(int iTag, int iType) {
    std::shared_ptr<t> spkfRet;
    std::list<std::shared_ptr<t> > listRet;
    for (auto spkf : listFields) {
        if (spkf && (iTag == kmip::TagUnknown || spkf->getTag() == iTag) && (iType == kmip::TypeUnknown || spkf->getType() == iType)) {
            spkfRet = std::dynamic_pointer_cast<t>(spkf);
            if (spkfRet) {
                listRet.push_back(spkfRet);
            }
        }
    }

    return listRet;
}

template<typename t, typename v>
bool KMIPStruct::findChildValue(int iTag, v &val, int iIndex) const {
    std::shared_ptr<const t> spkfRet = getChild<t>(iTag, kmip::TypeUnknown, iIndex);
    if (spkfRet) {
        val = spkfRet->getValue();
    }

    return static_cast<bool>(spkfRet);
}

template<typename t, typename v>
v KMIPStruct::getChildValue(int iTag, const v &valDefault, int iIndex) const {
    v valRet = valDefault;
    findChildValue<t>(iTag, valRet, iIndex);
    return valRet;
}

template<typename t, typename v>
bool KMIPStruct::setChildValue(int iTag, const v &val, int iIndex) {
    std::shared_ptr<t> spkfRet =  getChild<t>(iTag, kmip::TypeUnknown, iIndex);
    if (spkfRet) {
        spkfRet->setValue(val);
    }

    return static_cast<bool>(spkfRet);
}

template<typename t, typename v>
bool KMIPStruct::addOrderedChild(int iTag, int iType, const v &val) {
    KMIPFieldSP spkf(KMIPUtils::createField(iTag, iType).release());
    std::shared_ptr<t> spkChild = std::dynamic_pointer_cast<t>(spkf);
    bool bOK = static_cast<bool>(spkChild);
    if (bOK) {
        spkChild->setValue(val);
        bOK = addOrderedField(spkf);
    }

    return bOK;
}

typedef KMIPStruct KMIPStructure;
typedef std::unique_ptr<KMIPStruct> KMIPStructUP;
typedef std::shared_ptr<KMIPStruct> KMIPStructSP;

#endif
