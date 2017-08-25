/* Copyright (C) 2017 Alexander Downey */
#include "KMIPMessage.h"
#include "KMIPHeader.h"
#include "KMIPBatchItem.h"

bool KMIPMessage::isRequest() const {
    return getTag() == kmip::TagRequestMessage;
}

std::shared_ptr<KMIPHeader> KMIPMessage::getHeader() {
    return isRequest() ? getChild<KMIPHeader>(kmip::TagRequestHeader) :
        getChild<KMIPHeader>(kmip::TagResponseHeader);
}

std::shared_ptr<const KMIPHeader> KMIPMessage::getHeader() const {
    return isRequest() ? getChild<KMIPHeader>(kmip::TagRequestHeader) :
        getChild<KMIPHeader>(kmip::TagResponseHeader);
}

IMPLEMENT_GET_ADD_FIELDS(KMIPMessage, KMIPBatchItem, BatchItem, kmip::TagBatchItem);

KMIPMessage::KMIPMessage(int iTag) : KMIPStruct(iTag) {}
KMIPRequestMessage::KMIPRequestMessage() : KMIPMessage(kmip::TagRequestMessage) {}
        IMPLEMENT_GET_SET_FIELD(KMIPRequestMessage, KMIPRequestHeader, RequestHeader, kmip::TagRequestHeader);
KMIPResponseMessage::KMIPResponseMessage() : KMIPMessage(kmip::TagResponseMessage) {}
        IMPLEMENT_GET_SET_FIELD(KMIPResponseMessage, KMIPResponseHeader, ResponseHeader, kmip::TagResponseHeader);
