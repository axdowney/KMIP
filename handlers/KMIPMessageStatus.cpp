/* Copyright (C) 2017 Alexander Downey */
#include "KMIPMessageStatus.h"
#include "KMIPHeader.h"
#include "KMIPBatchItem.h"
#include "KMIPProtocolVersion.h"
#include "KMIPEnumeration.h"

KMIPMessageStatus::KMIPMessageStatus() : iMajor(), iMinor(), iMax(0), bAsync(false), bAttCapIndicator(false), eErrContOpt(KMIPBatchErrorContinuationOption::Stop) {
    krm.setResponseHeader(std::shared_ptr<KMIPResponseHeader>(new KMIPResponseHeader()));
}

KMIPMessageStatus::KMIPMessageStatus(std::shared_ptr<KMIPHeader> spheader) : KMIPMessageStatus() {
    setFromHeader(spheader);
}

void KMIPMessageStatus::setFromHeader(std::shared_ptr<KMIPHeader> spheader) {
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
    if (bOK) {
        std::shared_ptr<KMIPBatchItem> spkbiResponse(new KMIPBatchItem);
        spkbiResponse->copyFields(spkbi);
        spkbiResponse->setResponsePayload(spkstResponsePayload->cloneShared<KMIPStruct>());
        spkbiResponse->setResultStatus(KMIPResultStatus::Success);
        krm.addBatchItem(spkbiResponse);
    }

    return bOK;
}

bool KMIPMessageStatus::addFailure(std::shared_ptr<KMIPBatchItem> spkbi, int32_t eReason, const std::string &sMessage) {
    bool bOK = spkbi.get();
    if (bOK) {
        std::shared_ptr<KMIPBatchItem> spkbiResponse(new KMIPBatchItem);
        spkbiResponse->copyFields(spkbi);
        spkbi->setResultReason(eReason);
        spkbi->setResultMessage(sMessage);
        spkbiResponse->setResultStatus(KMIPResultStatus::OperationFailed);
        krm.addBatchItem(spkbiResponse);
    }

    return bOK;
}

void KMIPMessageStatus::undo() {
    std::list<std::shared_ptr<KMIPBatchItem> > listBatchItems = krm.getChildren<KMIPBatchItem>(kmip::TagBatchItem);
    for (auto spkbi : listBatchItems) {
        if (spkbi->getResultStatus() == KMIPResultStatus::Success) {
            spkbi->setResultStatus(KMIPResultStatus::OperationUndone);
        }
    }
}

void KMIPMessageStatus::clear() {
    krm.removeField(kmip::TagBatchItem);
}

std::shared_ptr<KMIPResponseMessage> KMIPMessageStatus::createMessage() const {
    std::shared_ptr<KMIPResponseMessage> spkrm = krm.cloneShared<KMIPResponseMessage>();

    std::shared_ptr<KMIPResponseHeader> spkrh = spkrm->getResponseHeader();
    if (!spkrh) {
        spkrh.reset(new KMIPResponseHeader());
        spkrm->setResponseHeader(spkrh);
    }

    spkrh->setProtocolVersion(getVersionMajor(), getVersionMinor());
    spkrh->setTimeStamp(DateTime());
    spkrh->setBatchCount(spkrm->getFieldNumber(kmip::TagBatchItem));
    return spkrm;
}
