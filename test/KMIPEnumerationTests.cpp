#include <string>
#include <gtest/gtest.h>

#include "KMIPEnumeration.h"

TEST(KMIPEnumeration, EnumToString) {
    KMIPCredentialType kct(KMIPCredentialType::UsernameAndPassword);
    EXPECT_EQ(kct.VALUEToString(KMIPCredentialType::UsernameAndPassword), "UsernameAndPassword");
    EXPECT_EQ(kct.VALUEToString(KMIPCredentialType::Device), "Device");
    EXPECT_EQ(kct.VALUEToString(KMIPCredentialType::Attestation), "Attestation");
    EXPECT_EQ(kct.VALUEToString(KMIPCredentialType::Unknown), "Unknown");
    EXPECT_EQ(kct.VALUEToString(static_cast<KMIPCredentialType::VALUE>(KMIPCredentialType::Unknown - 1)), "");

    EXPECT_EQ(kct.VALUEFromString("UsernameAndPassword"), KMIPCredentialType::UsernameAndPassword);
    EXPECT_EQ(kct.VALUEFromString("Device"), KMIPCredentialType::Device);
    EXPECT_EQ(kct.VALUEFromString("Attestation"), KMIPCredentialType::Attestation);
    EXPECT_EQ(kct.VALUEFromString(""), KMIPCredentialType::Unknown);
}
