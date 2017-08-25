#include <string>
#include <gtest/gtest.h>

#include "KMIPTTLVEncoding.h"
#include "KMIPField.h"
#include "KMIPUtils.h"
#include "HexUtils.h"
#include "KMIPTestDefs.h"

TEST(KMIPTTLVEncoding, test1) {
    std::string sHexMessage = "42007801000000904200770100000048420069010000002042006a02000000040000000100000000"
        "42006b020000000400000000000000004200500200000004000001000000000042000d0200000004"
        "000000010000000042000f010000003842005c050000000400000018000000004200790100000020"
        "4200740500000004000000010000000042007405000000040000000200000000";
    std::string sMessage = HexUtils::hexDecode(sHexMessage);
    KMIPTTLVEncoding kmipttlve;
    KMIPFieldUP upkf = kmipttlve.decodeKMIP(sMessage);
    std::string sLog = KMIPUtils::printFieldString(upkf.get(), 0);
    std::cerr << sLog;
    EXPECT_TRUE(static_cast<bool>(upkf)) << sLog;
    std::string sField = kmipttlve.encodeKMIP(upkf.get());
    std::string sHexField = HexUtils::hexEncode(sField, false);
    EXPECT_EQ(sMessage, sField);
    EXPECT_EQ(sHexMessage, sHexField);
}

TEST(KMIPTTLVEncoding, test2) {
    if (KMIPTestGlobals::argc > 1) {
        std::string sHex = KMIPTestGlobals::argv[1];
        std::string sMessage = HexUtils::hexDecode(sHex);
        KMIPTTLVEncoding kmipttlve;
        KMIPFieldUP upkf = kmipttlve.decodeKMIP(sMessage);

        ASSERT_TRUE(upkf.get());
        std::string sLog = KMIPUtils::printFieldString(upkf.get(), 0);
        std::cerr << sLog;
    }
}
