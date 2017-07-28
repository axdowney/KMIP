/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPERATIONHANDLER_H
#define _KMIPOPERATIONHANDLER_H

#include <memory>

#include "KMIPEnumeration.h"
#include "KMIPDatabase.h"
#include "KMIPStruct.h"

class KMIPOperationHandler : protected KMIPOperation {
    public:
        virtual KMIPStructSP handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPStructSP &spksRequest) const=0;

    protected:
        KMIPOperationHandler(int32_t eOperation) : KMIPOperation(eOperation) {}
};


#endif
