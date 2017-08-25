#include <string>
#include <gtest/gtest.h>

#include "KMIPTestDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPField.h"
#include "KMIPUtils.h"
#include "HexUtils.h"
#include "KMIPDatabaseRaw.h"
#include "KMIPCertificate.h"
#include "KMIPAttribute.h"
#include "KMIPString.h"
#include "KMIPMessageHandler.h"
#include "KMIPMessage.h"
#include "KMIPHeader.h"
#include "KMIPAuthentication.h"
#include "KMIPBatchItem.h"
#include "KMIPEnumeration.h"
#include "KMIPAttribute.h"
#include "KMIPAttributeNumbers.h"
#include "KMIPKey.h"

TEST(KMIPCreate, test1) {
    std::cerr << "ARGC " << KMIPTestGlobals::argc << std::endl;
    std::shared_ptr<KMIPDatabaseRaw> spkdr(new KMIPDatabaseRaw("dbname = kmip user = alexander password = postgres host = /var/run/postgresql port = 5432 requiressl = 1"));
    KMIPMessageHandler kmh(spkdr);
    std::shared_ptr<KMIPRequestMessage> spkMessage(new KMIPRequestMessage);
    std::shared_ptr<KMIPRequestHeader> spkHeader(new KMIPRequestHeader);
    spkHeader->setProtocolVersion(kmip::kiVersionMajor, kmip::kiVersionMinor);
    spkHeader->setAuthentication(std::shared_ptr<KMIPAuthentication>(new KMIPAuthentication));
    spkHeader->setBatchCount(1);
    spkMessage->setRequestHeader(spkHeader);
    std::shared_ptr<KMIPBatchItem> spkBatchItem(new KMIPBatchItem);
    spkBatchItem->setOperation(KMIPOperation::Create);
    KMIPStructSP spkst(new KMIPStruct(kmip::TagRequestPayload));
    spkst->setOrderedEnumeration(kmip::TagObjectType, KMIPObjectType::SymmetricKey);
    std::shared_ptr<KMIPTemplateAttribute> spkta(new KMIPTemplateAttribute());
    spkta->addField(std::shared_ptr<KMIPField>(new KMIPAttribute(
                    KMIPAttribute::getNameFromTag(kmip::TagCryptographicAlgorithm), 0, KMIPFieldSP(new KMIPCryptographicAlgorithm(KMIPCryptographicAlgorithm::DES3)))));
    spkta->addField(std::shared_ptr<KMIPField>(new KMIPAttribute(
                    KMIPAttribute::getNameFromTag(kmip::TagCryptographicLength), 0, KMIPFieldSP(new KMIPCryptographicLength(112)))));
    spkst->addField(spkta);
    spkBatchItem->setRequestPayload(spkst);
    spkMessage->addBatchItem(spkBatchItem);


    std::shared_ptr<KMIPResponseMessage> spkrmRes = kmh.handleMessage(spkMessage);
    std::shared_ptr<KMIPBatchItem> spkbi = spkrmRes->getBatchItem();
    ASSERT_TRUE(spkbi.get());
    EXPECT_EQ(spkbi->getResultStatus(), KMIPResultStatus::Success);
    if (spkbi->getResultStatus() != KMIPResultStatus::Success) {
        std::cerr << "KMIP Message Error " << spkbi->getResultReason() << "  " << spkbi->getResultMessage() << std::endl;
    }
    KMIPStructSP spkstResPay = spkbi->getResponsePayload();
    ASSERT_TRUE(spkstResPay.get());
    ASSERT_FALSE(spkstResPay->getChildValue<KMIPTextString>(kmip::TagUniqueIdentifier, std::string()).empty());
}
