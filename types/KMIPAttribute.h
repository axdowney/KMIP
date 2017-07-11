/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTE_H
#define _KMIPATTRIBUTE_H

#include <string>
#include <map>

#include "KMIPStruct.h"

class KMIPAttributeRule;
class KMIPAttribute : public KMIPStruct {
    public:
        KMIPAttribute();
        KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldUP upkfValue);
        KMIPAttribute(const std::string &sName, int iIndex, KMIPField *pkfValue);
        KMIPAttribute(const std::string &sName, int iIndex, KMIPFieldSP spkfValue);

        std::string getName() const;
        bool setName(const std::string &sNewName);
        int getIndex() const;
        bool setIndex(int iNewIndex);
        KMIPFieldSP getValue();
        KMIPFieldSPK getValue() const;

        template<typename T, typename V>
        V getValue(const V &val) const;

        bool setValue(KMIPFieldSP spkfValue);

        static int getNameTag(const std::string &sName);
        int getNameTag() const;
        static std::string getNameFromTag(int iTag);
        static std::shared_ptr<KMIPAttributeRule> getRuleFromName(const std::string &sName);
        std::shared_ptr<KMIPAttributeRule> getRuleFromName() const;


        static const std::map<std::string, int> mapNameToTag;
};


template<typename T, typename V>
V KMIPAttribute::getValue(const V &val) const {
    return getChildValue<T>(kmip::TagAttributeValue, val);
}



#endif
