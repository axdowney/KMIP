/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTE_H
#define _KMIPATTRIBUTE_H

#include <string>

#include "KMIPStruct.h"

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
        bool setValue(KMIPFieldSP spkfValue);

};



#endif
