/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPPROTOCOLVERSION_H
#define _KMIPPROTOCOLVERSION_H

#include "KMIPStruct.h"

class KMIPProtocolVersion : public KMIPStruct {
    public:
        KMIPProtocolVersion();
        KMIPProtocolVersion(int iMajor, int iMinor);
        DECLARE_GET_SET_FIELD_VALUE(int, ProtocolVersionMajor);
        DECLARE_GET_SET_FIELD_VALUE(int, ProtocolVersionMinor);
};


#endif
