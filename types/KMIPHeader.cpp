/* Copyright (C) 2017 Alexander Downey */
#include "KMIPHeader.h"
#include "KMIPProtocolVersion.h"
#include "KMIPAuthentication.h"
#include "KMIPCredential.h"
#include "KMIPEnumeration.h"
#include "KMIPDateTime.h"
#include "KMIPString.h"


        IMPLEMENT_GET_SET_FIELD(KMIPHeader, KMIPProtocolVersion, ProtocolVersion, kmip::TagProtocolVersion);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Integer, int, MaximumResponseSize, kmip::TagMaximumResponseSize);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, TextString, std::string, ClientCorrelationValue, kmip::TagClientCorrelationValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, TextString, std::string, ServerCorrelationValue, kmip::TagServerCorrelationValue);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Boolean, bool, AsynchronousIndicator, kmip::TagAsynchronousIndicator);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Boolean, bool, AttestationCapableIndicator, kmip::TagAttestationCapableIndicator);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Enumeration, uint32_t, AttestationType, kmip::TagAttestationType);
        IMPLEMENT_GET_SET_FIELD(KMIPHeader, KMIPAuthentication, Authentication, kmip::TagAuthentication);
        IMPLEMENT_GET_SET_FIELD_VALUE_DEFAULT(KMIPHeader, Enumeration, uint32_t, BatchErrorContinuationOption, kmip::TagBatchErrorContinuationOption, KMIPBatchErrorContinuationOption::Stop);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Boolean, bool, BatchOrderOption, kmip::TagBatchOrderOption);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, DateTime, DateTime, TimeStamp, kmip::TagTimeStamp);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPHeader, Integer, int, BatchCount, kmip::TagBatchCount); 
        IMPLEMENT_GET_SET_FIELD(KMIPHeader, KMIPNonce, Nonce, kmip::TagNonce);
KMIPHeader::KMIPHeader(int iTag) : KMIPStruct(iTag) {}
KMIPRequestHeader::KMIPRequestHeader() : KMIPHeader(kmip::TagRequestHeader) {}
KMIPResponseHeader::KMIPResponseHeader() : KMIPHeader(kmip::TagResponseHeader) {}
