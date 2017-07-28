/* Copyright (C) 2017 Alexander Downey */
#include "KMIPMessageStatus.h"
#include "KMIPHeader.h"
#include "KMIPBatchItem.h"
#include "KMIPProtocolVersion.h"
#include "KMIPEnumeration.h"

KMIPMessageStatus::KMIPMessageStatus() : iMajor(), iMinor(), iMax(0), bAsync(false), bAttCapIndicator(false), eErrContOpt(KMIPBatchErrorContinuationOption::Stop) {}
KMIPMessageStatus::KMIPMessageStatus(std::shared_ptr<KMIPHeader> spheader) : KMIPMessageStatus() {
    if (spheader) {
        std::shared_ptr<KMIPProtocolVersion> spkpv = spheader->getProtocolVersion();
        if (spkpv) {
            setVersionMajor(spkpv->getProtocolVersionMajor());
            setVersionMinor(spkpv->getProtocolVersionMinor());
        }

        iMax = spheader->getMaximumResponseSize();
        bAsync = spheader->getAsynchronousIndicator();
        bAttCapIndicator = spheader->getAttestationCapableIndicator();
    }
}

bool KMIPMessageStatus::addSuccess(std::shared_ptr<KMIPBatchItem> spkbi, KMIPStructSP spkstResponsePayload) {
    bool bOK = spkbi && spkstResponsePayload;

    return bOK;
}

bool KMIPMessageStatus::addFailure(std::shared_ptr<KMIPBatchItem> spkbi, int32_t eReason, const std::string &sMessage) {
}

