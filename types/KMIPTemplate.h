/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPTEMPLATE_H
#define _KMIPTEMPLATE_H

#include "KMIPStruct.h"

class KMIPAttribute;
class KMIPTemplate : public KMIPStruct {
    public:
        KMIPTemplate();
        virtual int getObjectType() const;
        DECLARE_GET_ADD_FIELDS(KMIPAttribute, Attribute);
};

#endif
