#include <gtest/gtest.h>
#include "KMIPTestDefs.h"
//#include "KMIPTTLVEncodingTests.cpp"

int main (int ac, char* av[]) {
  testing::InitGoogleTest(&ac, av);
  KMIPTestGlobals::argc = ac;
  KMIPTestGlobals::argv = av;
  return RUN_ALL_TESTS();
}
