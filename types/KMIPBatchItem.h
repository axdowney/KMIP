/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPBATCHITEM_H
#define _KMIPBATCHITEM_H

#include "KMIPStruct.h"

class KMIPMessageExtension;
class KMIPBatchItem : public KMIPStruct {
    public:
        KMIPBatchItem();
        bool copyFields(std::shared_ptr<KMIPBatchItem> spkbi);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, Operation);
        DECLARE_GET_SET_FIELD_VALUE(std::string, UniqueBatchItemID);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, ResultStatus);
        DECLARE_GET_SET_FIELD_VALUE(uint32_t, ResultReason);
        DECLARE_GET_SET_FIELD_VALUE(std::string, ResultMessage);
        DECLARE_GET_SET_FIELD_VALUE(std::string, AsynchronousCorrelationValue);
        DECLARE_GET_SET_FIELD(KMIPStruct, ResponsePayload);
        DECLARE_GET_SET_FIELD(KMIPStruct, RequestPayload);
        DECLARE_GET_SET_FIELD(KMIPMessageExtension, MessageExtension);
};


#endif
