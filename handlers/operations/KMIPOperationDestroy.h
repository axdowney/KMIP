/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPERATIONDESTROY_H
#define _KMIPOPERATIONDESTROY_H

#include "KMIPOperationHandler.h"

class KMIPOperationDestroy : public KMIPOperationHandler {
    public:
        KMIPOperationDestroy();
        virtual bool handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const;
};


#endif
