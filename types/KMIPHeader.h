/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPHEADER_H
#define _KMIPHEADER_H

#include "KMIPStruct.h"
#include "DateTime.h"

class KMIPProtocolVersion;
class KMIPAuthentication;
class KMIPHeader : public KMIPStruct {
    public:
        DECLARE_GET_SET_FIELD(KMIPProtocolVersion, ProtocolVersion);
        DECLARE_GET_SET_FIELD_VALUE(int, MaximumResponseSize);
        DECLARE_GET_SET_FIELD_VALUE(std::string, ClientCorrelationValue);
        DECLARE_GET_SET_FIELD_VALUE(std::string, ServerCorrelationValue);
        DECLARE_GET_SET_FIELD_VALUE(bool, AsynchronousIndicator);
        DECLARE_GET_SET_FIELD_VALUE(bool, AttestationCapableIndicator);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, AttestationType);
        DECLARE_GET_SET_FIELD(KMIPAuthentication, Authentication);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, BatchErrorContinuationOption);
        DECLARE_GET_SET_FIELD_VALUE(bool, BatchOrderOption);
        DECLARE_GET_SET_FIELD_VALUE(DateTime, TimeStamp);
        DECLARE_GET_SET_FIELD_VALUE(int, BatchCount);
    protected:
        KMIPHeader(int iTag);
};

#endif
