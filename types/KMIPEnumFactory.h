/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPENUMFACTORY_H
#define _KMIPENUMFACTORY_H

#include "KMIPFactory.h"
//#include "KMIPEnumeration.h"

class KMIPEnumeration;
class KMIPEnumFactory : public KMIPFactory {
    public:
        KMIPEnumFactory() : KMIPFactory() {}
        virtual ~KMIPEnumFactory() {}
        //virtual KMIPFieldUP createField(int iTag) const;
        virtual std::unique_ptr<KMIPField> createField(int iTag) const;
        //KMIPEnumerationUP createEnumeration(int iTag, uint32_t eValue = 0) const;
        std::unique_ptr<KMIPEnumeration> createEnumeration(int iTag, uint32_t eValue = 0) const;
};


#endif
