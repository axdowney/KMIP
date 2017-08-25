/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPERATIONHANDLER_H
#define _KMIPOPERATIONHANDLER_H

#include <memory>

#include "KMIPEnumeration.h"
#include "KMIPDatabase.h"
#include "KMIPStruct.h"
#include "KMIPBatchItem.h"
#include "KMIPMessageStatus.h"
#include "KMIPMessageHandler.h"

class KMIPOperationHandler : protected KMIPOperation {
    public:
        virtual bool handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const=0;

    protected:
        KMIPOperationHandler(int32_t eOperation) : KMIPOperation(eOperation) {}
};


#endif
