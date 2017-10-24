/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMESSAGEHANDLER_H
#define _KMIPMESSAGEHANDLER_H

#include <memory>

#include "KMIPDatabase.h"
#include "KMIPMessage.h"
#include "KMIPMessageStatus.h"

class KMIPAuthentication;
class KMIPBatchItem;
class KMIPMessageHandler {
    public:
        KMIPMessageHandler();
        KMIPMessageHandler(std::shared_ptr<KMIPDatabase> spkd);
        std::shared_ptr<KMIPResponseMessage> handleMessage(std::shared_ptr<KMIPRequestMessage> spkMessage);
        bool authenticate(std::shared_ptr<KMIPAuthentication> spka);
        void setDatabase(std::shared_ptr<KMIPDatabase> spkd);
        bool handleBatch(KMIPMessageStatus &kms, const std::list<std::shared_ptr<KMIPBatchItem> > &listBatchItems);
        bool handleBatchItem(KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem>  spBatchItem);

    protected:
        std::shared_ptr<KMIPDatabase> spkd;
        std::string sPlaceHolder;
};



#endif
