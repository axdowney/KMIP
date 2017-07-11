#include <string>
#include <gtest/gtest.h>

#include "KMIPTTLVEncoding.h"
#include "KMIPField.h"
#include "KMIPUtils.h"
#include "HexUtils.h"
#include "KMIPDatabaseRaw.h"

TEST(KMIPDatabase, test1) {
    KMIPDatabaseRaw kdr("dbname = kmip user = alexander password = postgres host = /var/run/postgresql port = 5432 requiressl = 1");
    EXPECT_TRUE(kdr.connect());
}
