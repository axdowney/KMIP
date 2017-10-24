/* Copyright (C) 2017 Alexander Downey */
#include </usr/include/openssl/aes.h>
#include <openssl/des.h>
#include <cstdlib>
#include <crypto++/aes.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/des.h>
#include "KMIPOperationDestroy.h"
#include "KMIPAttribute.h"
#include "KMIPKey.h"
#include "KMIPEnumeration.h"
#include "KMIPKeyBlock.h"
#include "KMIPString.h"
#include "HexUtils.h"
#include "KMIPDatabase.h"


KMIPOperationDestroy::KMIPOperationDestroy() : KMIPOperationHandler(KMIPOperation::Destroy) {}

bool KMIPOperationDestroy::handleRequest(std::shared_ptr<KMIPDatabase> spkd, KMIPMessageStatus &kms, std::shared_ptr<KMIPBatchItem> spkbi) const {
    bool bOK = spkd && spkbi;
    KMIPStructSP spkst;
    if (bOK) {
        spkst = spkbi->getRequestPayload();
        if (!spkst) {
            bOK = false;
            kms.addFailure(spkbi, KMIPResultReason::InvalidMessage, "Request Payload not found.");
        }
    }

    std::string sID;
    if (spkst) {
        std::shared_ptr<KMIPTextString> spID = spkst->getChild<KMIPTextString>(kmip::TagUniqueIdentifier);
        if (spID) {
            sID = spID->getValue();
        } else {
            bOK = false;
        }
    }

    if (bOK) {
        std::list<std::string> listIDs = {sID};
        bOK = spkd->deleteObjects(listIDs) == listIDs.size();
        if (!bOK) {
            kms.addFailure(spkbi, KMIPResultReason::GeneralFailure, "Could not destroy objects.");
        }
    }

    if (bOK) {
        KMIPStructSP spkst(new KMIPStruct(kmip::TagResponsePayload));
        spkst->setOrderedTextString(kmip::TagUniqueIdentifier, sID);
        kms.addSuccess(spkbi, spkst);
    }

    return bOK;
}
