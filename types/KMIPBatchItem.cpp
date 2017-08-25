/* Copyright (C) 2017 Alexander Downey */
#include "KMIPBatchItem.h"
#include "KMIPMessageExtension.h"
#include "KMIPEnumeration.h"
#include "KMIPString.h"


KMIPBatchItem::KMIPBatchItem() : KMIPStruct(kmip::TagBatchItem) {}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, Enumeration, uint32_t, Operation, kmip::TagOperation);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, ByteString, std::string, UniqueBatchItemID, kmip::TagUniqueBatchItemID);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, Enumeration, uint32_t, ResultStatus, kmip::TagResultStatus);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, Enumeration, uint32_t, ResultReason, kmip::TagResultReason);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, TextString, std::string, ResultMessage, kmip::TagResultMessage);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPBatchItem, ByteString, std::string, AsynchronousCorrelationValue, kmip::TagAsynchronousCorrelationValue);
        IMPLEMENT_GET_SET_FIELD(KMIPBatchItem, KMIPStruct, ResponsePayload, kmip::TagResponsePayload);
        IMPLEMENT_GET_SET_FIELD(KMIPBatchItem, KMIPStruct, RequestPayload, kmip::TagRequestPayload);
        IMPLEMENT_GET_SET_FIELD(KMIPBatchItem, KMIPMessageExtension, MessageExtension, kmip::TagMessageExtension);

bool KMIPBatchItem::copyFields(std::shared_ptr<KMIPBatchItem> spkbi) {
    bool bRet = spkbi.get();

    if (bRet) {
        setOperation(spkbi->getOperation());
        std::string sID;
        if (spkbi->findChildValue<KMIPByteString>(kmip::TagUniqueBatchItemID, sID)) {
            setUniqueBatchItemID(sID);
        }

        if (spkbi->findChildValue<KMIPByteString>(kmip::TagAsynchronousCorrelationValue, sID)) {
            setAsynchronousCorrelationValue(sID);
        }
    }

    return bRet;
}
