#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>

#include "KMIPDateTime.h"
#include "KMIPDefs.h"
#include "DateTime.h"
#include "KMIPUtils.h"

#include "KMIPXMLEncoding.h"

TEST(KMIPXMLEncoding, DecodeEncode) {
    std::string sFile = "./test/KMIPXMLTest1.xml";
    std::ifstream t(sFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string sXML_In = buffer.str();
    std::string sExtra;
    KMIPXMLEncoding kxe;
    KMIPFieldUP upkf = kxe.decodeKMIP(sXML_In, sExtra);
    ASSERT_TRUE(upkf.get());
    std::cerr << "XML Decoded :" << KMIPUtils::printFieldString(upkf.get()) << std::endl;
    std::string sXML_Out = kxe.encodeKMIP(upkf.get());
    std::cerr << "XML Encoded :" << sXML_Out << std::endl;
    KMIPFieldUP upkf2 = kxe.decodeKMIP(sXML_Out, sExtra);
    ASSERT_TRUE(upkf2.get());
    std::cerr << "XML Decoded Again :" << KMIPUtils::printFieldString(upkf2.get()) << std::endl;
    EXPECT_TRUE(*upkf == *upkf2);
    EXPECT_EQ(*upkf, *upkf2);
}
