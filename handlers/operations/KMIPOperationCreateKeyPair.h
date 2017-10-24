/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPOPERATIONCREATEKEYPAIR_H
#define _KMIPOPERATIONCREATEKEYPAIR_H

#include "KMIPOperationHandler.h"

class KMIPOperationCreateKeyPair : public KMIPOperationHandler {
    public:
        KMIPOperationCreateKeyPair();
        virtual bool handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const;
        static bool generateKeyPair(int iAlg, int iBits, std::string &sPriv, std::string &sPub, int iQLength, int iCurve);
};


#endif
