/* Copyright (C) 2017 Alexander Downey */

#include "KMIPStructFactory.h"
#include "KMIPStruct.h"
#include "KMIPAttribute.h"

KMIPFieldUP KMIPStructFactory::createField(int iTag) const {
    return createStructure(iTag);
}

KMIPStructUP KMIPStructFactory::createStructure(int iTag) const {
    KMIPStructUP upkst;
    switch(iTag) {
        case kmip::TagAttribute:
            upkst.reset(new KMIPAttribute());
            break;
        default:
            upkst.reset(new KMIPStruct(iTag));
            break;
    }

    return upkst;
}

