#include <string>
#include <gtest/gtest.h>

#include "KMIPTTLVEncoding.h"
#include "KMIPField.h"
#include "KMIPUtils.h"
#include "HexUtils.h"
#include "KMIPDatabaseRaw.h"
#include "KMIPCertificate.h"
#include "KMIPAttribute.h"
#include "KMIPString.h"

TEST(KMIPDatabase, test1) {
    KMIPDatabaseRaw kdr("dbname = kmip user = alexander password = postgres host = /var/run/postgresql port = 5432 requiressl = 1");
    std::shared_ptr<KMIPCertificate> spkcert(new KMIPCertificate());
    std::string sID = "ID 1";
    EXPECT_TRUE(spkcert->setUniqueID(sID));
    std::shared_ptr<KMIPAttribute> spka = spkcert->getAttribute(KMIPAttribute::getNameFromTag(kmip::TagUniqueIdentifier), 0);
    ASSERT_TRUE(spka.get());
    EXPECT_EQ(sID, spka->getChildValue<KMIPTextString>(kmip::TagAttributeValue, std::string()));
    EXPECT_EQ(sID, spkcert->getUniqueID());
    std::list<std::shared_ptr<KMIPManagedObject> > listObjects;
    listObjects.push_back(spkcert);
    EXPECT_EQ(listObjects.size(), kdr.addObjects(listObjects));
    std::list<std::string> listIDs;
    listIDs.push_back(sID);
    DBObjectMap dbom = kdr.getObjects(listIDs);
    EXPECT_TRUE(static_cast<bool>(dbom[sID].front()));
    if (static_cast<bool>(dbom[sID].front())) {
        EXPECT_EQ(sID, dbom[sID].front()->getUniqueID());
    }
    EXPECT_TRUE(kdr.deleteObjects(listIDs));
    EXPECT_TRUE(kdr.disconnect());
}
