/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPERATIONCREATE_H
#define _KMIPOPERATIONCREATE_H

#include "KMIPOperationHandler.h"

class KMIPOperationCreate : public KMIPOperationHandler {
    public:
        KMIPOperationCreate();
        virtual bool handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const;
};


#endif
