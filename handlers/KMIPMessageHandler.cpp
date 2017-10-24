/* Copyright (C) 2017 Alexander Downey */
#include "KMIPMessageHandler.h"
#include "KMIPMessageStatus.h"
#include "KMIPHeader.h"
#include "KMIPMessage.h"
#include "KMIPEnumeration.h"
#include "KMIPBatchItem.h"


//Operations
#include "KMIPOperationCreate.h"
#include "KMIPOperationDestroy.h"

KMIPMessageHandler::KMIPMessageHandler() {}
KMIPMessageHandler::KMIPMessageHandler(std::shared_ptr<KMIPDatabase> spkd) : spkd(spkd) {}
std::shared_ptr<KMIPResponseMessage> KMIPMessageHandler::handleMessage(std::shared_ptr<KMIPRequestMessage> spkMessage) {
    bool bOK = spkMessage.get();
    KMIPMessageStatus kms;
    std::shared_ptr<KMIPHeader> spheader;
    std::list<std::shared_ptr<KMIPBatchItem> > listBatchItems;

    if (bOK) {
        spheader = spkMessage->getHeader();
        bOK = spheader.get();
        kms.setFromHeader(spheader);
    }

    if (bOK) {
        listBatchItems = spkMessage->getBatchItems();
    }

    if (bOK && !authenticate(spheader->getAuthentication())) {
        for (auto spBatchItem : listBatchItems) {
            kms.addFailure(spBatchItem, KMIPResultReason::PermissionDenied, "Access denied");
        }
    }

    if (bOK) {
        kms.setPlaceHolderID(sPlaceHolder);
        bOK = handleBatch(kms, listBatchItems);
    }

    return kms.createMessage();
}

bool KMIPMessageHandler::authenticate(std::shared_ptr<KMIPAuthentication> spka) {
    return spka.get();
}

void KMIPMessageHandler::setDatabase(std::shared_ptr<KMIPDatabase> spkd) {
    this->spkd = spkd;
}

bool KMIPMessageHandler::handleBatch(KMIPMessageStatus &kms, const std::list<std::shared_ptr<KMIPBatchItem> > &listBatchItems) {
    bool bOK = true;
    if (kms.getBatchErrorContOpt() == KMIPBatchErrorContinuationOption::Undo) {
        bOK = spkd->beginWork();
    }

    if (bOK) {
        for (auto spBatchItem : listBatchItems) {
            bOK = handleBatchItem(kms, spBatchItem);
            if (!bOK && kms.getBatchErrorContOpt() != KMIPBatchErrorContinuationOption::Continue) {
                break;
            }
        }

        if (kms.getBatchErrorContOpt() == KMIPBatchErrorContinuationOption::Undo) {
            spkd->endWork(bOK);
            if (!bOK) {
                kms.undo();
            } else if (!kms.getPlaceHolderID().empty()) {
                sPlaceHolder = kms.getPlaceHolderID();
            }
        }
    }   

    return bOK;
}

bool KMIPMessageHandler::handleBatchItem(KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem>  spBatchItem) {
    bool bOK = spBatchItem.get();
    if (bOK) {
        switch (spBatchItem->getOperation()) {
            case KMIPOperation::Create:{
                    KMIPOperationCreate koCreate;
                    bOK = koCreate.handleRequest(spkd, kms, spBatchItem);
                }
                break;
            case KMIPOperation::Destroy:{
                    KMIPOperationDestroy koDestroy;
                    bOK = koDestroy.handleRequest(spkd, kms, spBatchItem);
                }
                break;
            default:
                bOK = false;
                kms.addFailure(spBatchItem, KMIPResultReason::IllegalOperation, "Illegal operation");
                break;
        }
    }

    return bOK;
}
