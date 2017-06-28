/* Copyright (C) 2017 Alexander Downey */
#include "KMIPMessageExtension.h"
#include "KMIPNumber.h"
#include "KMIPString.h"
KMIPVendorExtension::KMIPVendorExtension() : KMIPStruct(kmip::TagVendorExtension) {}
KMIPMessageExtension::KMIPMessageExtension() : KMIPStruct(kmip::TagMessageExtension) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPMessageExtension, TextString, std::string, VendorIdentification, kmip::TagVendorIdentification);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPMessageExtension, Boolean, bool, CriticalityIndicator, kmip::TagCriticalityIndicator);
        IMPLEMENT_GET_SET_FIELD(KMIPMessageExtension, KMIPVendorExtension, VendorExtension, kmip::TagVendorExtension);
