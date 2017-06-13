#include <string>
#include <gtest/gtest.h>

#include "KMIPAttribute.h"
#include "KMIPEnumeration.h"
#include "KMIPUtils.h"

TEST(KMIPStructTests, OrderTest) {
    KMIPAttribute ka;
    EXPECT_TRUE(ka.hasOrder());
    EXPECT_FALSE(ka.isOrdered());
    EXPECT_FALSE(ka.isValid());
    EXPECT_TRUE(ka.setIndex(0));
    EXPECT_TRUE(ka.setName("Object Type"));
    KMIPFieldSP spkf(new KMIPObjectType(KMIPObjectType::Certificate));

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
