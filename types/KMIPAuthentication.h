/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPAUTHENTICATION_H
#define _KMIPAUTHENTICATION_H

#include "KMIPStruct.h"

class KMIPCredential;
class KMIPAuthentication : public KMIPStruct {
    public:
        KMIPAuthentication();
        DECLARE_GET_ADD_FIELDS(KMIPCredential, Credential);
};


#endif
