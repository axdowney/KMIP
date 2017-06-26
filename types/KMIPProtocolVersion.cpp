/* Copyright (C) 2017 Alexander Downey */
#include "KMIPProtocolVersion.h"
#include "KMIPNumber.h"


KMIPProtocolVersion::KMIPProtocolVersion() : KMIPStruct(kmip::TagProtocolVersion) {}
KMIPProtocolVersion::KMIPProtocolVersion(int iMajor, int iMinor) : KMIPStruct(kmip::TagProtocolVersion) {
    setProtocolVersionMinor(iMajor);
    setProtocolVersionMinor(iMinor);
}
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPProtocolVersion, Integer, int, ProtocolVersionMajor, kmip::TagProtocolVersionMajor);
        IMPLEMENT_GET_SET_FIELD_VALUE(KMIPProtocolVersion, Integer, int, ProtocolVersionMinor, kmip::TagProtocolVersionMinor);
