/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMESSAGE_H
#define _KMIPMESSAGE_H

#include "KMIPStruct.h"

class KMIPHeader;
class KMIPRequestHeader;
class KMIPResponseHeader;
class KMIPBatchItem;
class KMIPMessage : public KMIPStruct {
    public:
        bool isRequest() const;
        std::shared_ptr<KMIPHeader> getHeader();
        std::shared_ptr<const KMIPHeader> getHeader() const;
        DECLARE_GET_ADD_FIELDS(KMIPBatchItem, BatchItem);
    protected:
        KMIPMessage(int iTag);
};

class KMIPRequestMessage : public KMIPMessage {
    public:
        KMIPRequestMessage();
        DECLARE_GET_SET_FIELD(KMIPRequestHeader, RequestHeader);
};

class KMIPResponseMessage : public KMIPMessage {
    public:
        KMIPResponseMessage();
        DECLARE_GET_SET_FIELD(KMIPResponseHeader, ResponseHeader);
};


#endif
