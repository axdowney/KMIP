/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPTEMPLATE_H
#define _KMIPTEMPLATE_H

#include "KMIPManagedObject.h"

class KMIPAttribute;
class KMIPTemplate : public KMIPManagedObject {
    public:
        KMIPTemplate();
        virtual int getObjectType() const;
        DECLARE_GET_ADD_FIELDS(KMIPAttribute, Attribute);
};

#endif
