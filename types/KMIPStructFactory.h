/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPSTRUCTFACTORY_H
#define _KMIPSTRUCTFACTORY_H

#include "KMIPFactory.h"

class KMIPStruct;
class KMIPStructFactory : public KMIPFactory {
    public:
        KMIPStructFactory() : KMIPFactory() {}
        virtual ~KMIPStructFactory() {}
        virtual std::unique_ptr<KMIPField> createField(int iTag) const;
        std::unique_ptr<KMIPStruct> createStructure(int iTag) const;
};


#endif
