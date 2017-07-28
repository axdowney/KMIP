#include <string>
#include <gtest/gtest.h>

#include "KMIPAttribute.h"
#include "KMIPEnumeration.h"
#include "KMIPUtils.h"
#include "KMIPString.h"
#include "KMIPDateTime.h"

TEST(KMIPStructTests, OrderTest) {
    KMIPAttribute ka;
    EXPECT_TRUE(ka.hasOrder());
    EXPECT_FALSE(ka.isOrdered());
    EXPECT_FALSE(ka.isValid());
    EXPECT_TRUE(ka.setIndex(0));
    EXPECT_TRUE(ka.setName("Object Type"));
    KMIPFieldSP spkf(new KMIPObjectType(KMIPObjectType::Certificate));
    spkf.reset(new KMIPObjectType(KMIPObjectType::Certificate));


    EXPECT_TRUE(ka.isOrdered());
    EXPECT_TRUE(ka.isValid());

    EXPECT_TRUE(ka.setValue(spkf));
    EXPECT_TRUE(ka.isOrdered());
    EXPECT_TRUE(ka.isValid());

    auto listFields = ka.getChildren<KMIPField>();
    EXPECT_EQ(3, listFields.size());
    auto iter = listFields.begin();
    ASSERT_NE(iter, listFields.end());
    EXPECT_EQ(kmip::TagAttributeName, (*iter)->getTag()) << KMIPUtils::TagToString((*iter)->getTag());
    ++iter;
    ASSERT_NE(iter, listFields.end());
    EXPECT_EQ(kmip::TagAttributeIndex, (*iter)->getTag()) << KMIPUtils::TagToString((*iter)->getTag());
    ++iter;
    ASSERT_NE(iter, listFields.end());
    EXPECT_EQ(kmip::TagAttributeValue, (*iter)->getTag()) << KMIPUtils::TagToString((*iter)->getTag());

    EXPECT_TRUE(ka.setIndex(1));
    EXPECT_EQ(3, ka.getFieldNumber());
    EXPECT_EQ(1, ka.getIndex());
}

TEST(KMIPStructTests, CopyTest) {
    KMIPInteger ki(kmip::TagAttributeValue, 5);
    std::shared_ptr<KMIPInteger> spki = ki.cloneShared<KMIPInteger>();
    EXPECT_EQ(ki.getValue(), spki->getValue());

    KMIPTextString ks(kmip::TagAttributeValue, "Hello");
    std::shared_ptr<KMIPTextString> spks = ks.cloneShared<KMIPTextString>();
    EXPECT_EQ(ks.getValue(), spks->getValue());

    
    KMIPDateTime kdt(kmip::TagAttributeValue);
    std::shared_ptr<KMIPDateTime> spkdt = kdt.cloneShared<KMIPDateTime>();
    EXPECT_EQ(kdt.getValue(), spkdt->getValue());

    KMIPStruct kst(kmip::TagAttributeValue);
    kst.addField(spki);
    kst.addField(spks);
    kst.addField(spkdt);
    std::shared_ptr<KMIPStruct> spkst = kst.cloneShared<KMIPStruct>();
    ASSERT_TRUE(spkst.get());
    auto listFields = kst.getFields();
    auto listFieldsCopy = spkst->getFields();
    auto iterFields = listFields.begin();
    auto iterFieldsCopy = listFieldsCopy.begin();
    EXPECT_EQ(3, listFields.size());
    EXPECT_EQ(3, listFieldsCopy.size());
    for (; iterFields != listFields.end(); ++iterFields, ++iterFieldsCopy) {
        EXPECT_EQ(*(*iterFields), *(*iterFieldsCopy));
    }
    EXPECT_TRUE(kst == *spkst);
    EXPECT_EQ(kst, *spkst);
}
