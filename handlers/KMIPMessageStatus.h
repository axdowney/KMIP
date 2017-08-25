/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPMESSAGESTATUS_H
#define _KMIPMESSAGESTATUS_H

#include <cstdint>

#include "CommonMacros.h"
#include "KMIPMessage.h"

class KMIPBatchItem;
class KMIPHeader;
class KMIPMessageStatus {
    public:
        KMIPMessageStatus();
        KMIPMessageStatus(std::shared_ptr<KMIPHeader> spheader);

        bool addSuccess(std::shared_ptr<KMIPBatchItem> spkbi, KMIPStructSP spkstResponsePayload);
        bool addFailure(std::shared_ptr<KMIPBatchItem> spkbi, int32_t eReason, const std::string &sMessage);
        void undo();
        void clear();
        std::shared_ptr<KMIPResponseMessage> createMessage() const;

        void setFromHeader(std::shared_ptr<KMIPHeader> spheader);
        GETSET(VersionMajor, int, iMajor);
        GETSET(VersionMinor, int, iMinor);
        GETSET(MaxResponseSize, int, iMax);
        GETSET(AsynchronousIndicator, bool, bAsync);
        GETSET(AttCapInd, bool, bAttCapIndicator);
        GETSET(BatchErrorContOpt, int32_t, eErrContOpt);

    protected:
        KMIPResponseMessage krm;

};


#endif
