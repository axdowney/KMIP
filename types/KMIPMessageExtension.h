/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMESSAGEEXTENSION_H
#define _KMIPMESSAGEEXTENSION_H

#include "KMIPStruct.h"

class KMIPVendorExtension : public KMIPStruct {
    public:
        KMIPVendorExtension();
};

class KMIPMessageExtension : public KMIPStruct {
    public:
        KMIPMessageExtension();
        DECLARE_GET_SET_FIELD_VALUE(std::string, VendorIdentification);
        DECLARE_GET_SET_FIELD_VALUE(bool, CriticalityIndicator);
        DECLARE_GET_SET_FIELD(KMIPVendorExtension, VendorExtension);
};

#endif
