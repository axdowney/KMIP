/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMESSAGEHANDLER_H
#define _KMIPMESSAGEHANDLER_H

#include <memory>

#include "KMIPDatabase.h"
#include "KMIPMessage.h"


class KMIPMessageHandler {
    public:
        KMIPMessageHandler();
        KMIPMessageHandler(std::shared_ptr<KMIPDatabase> spkd);
        std::shared_ptr<KMIPResponseMessage> handleMessage(std::shared_ptr<KMIPRequestMessage> spkMessage);
};



#endif
