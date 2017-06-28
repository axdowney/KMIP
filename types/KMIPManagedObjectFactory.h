/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMANAGEDOBJECTFACTORY_H
#define _KMIPMANAGEDOBJECTFACTORY_H

#include "KMIPFactory.h"

class KMIPManagedObject;
class KMIPManagedObjectFactory : public KMIPFactory {
    public:
        KMIPManagedObjectFactory() : KMIPFactory() {}
        virtual ~KMIPManagedObjectFactory() {}
        virtual std::unique_ptr<KMIPField> createField(int iTag) const;
        std::unique_ptr<KMIPManagedObject> createObject(int iTag) const;
};


#endif
