/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPAQUEOBJECT_H
#define _KMIPOPAQUEOBJECT_H

#include "KMIPStruct.h"

class KMIPOpaqueObject : public KMIPStruct {
    public:
        KMIPOpaqueObject();
        KMIPOpaqueObject(uint32_t eType, const std::string &sValue);
        virtual int getObjectType() const;
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, OpaqueDataType);
        DECLARE_GET_SET_FIELD_VALUE(std::string, OpaqueDataValue);
};


#endif
