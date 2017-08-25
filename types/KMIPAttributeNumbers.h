/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTENUMBERS_H
#define _KMIPATTRIBUTENUMBERS_H

#include "KMIPNumber.h"

class KMIPCryptographicLength : public KMIPInteger {
    public:
        KMIPCryptographicLength(int iVal) : KMIPInteger(kmip::TagCryptographicLength, iVal) {}
};

class KMIPLeaseTime : public KMIPInterval {
    public:
        KMIPLeaseTime(uint32_t uiVal) : KMIPInterval(kmip::TagLeaseTime, uiVal) {}
};

class KMIPFresh : public KMIPBoolean {
    public:
        KMIPFresh(bool bVal) : KMIPBoolean(kmip::TagFresh, bVal) {}
};

class KMIPKeyValuePresent : public KMIPBoolean {
    public:
        KMIPKeyValuePresent(bool bVal) : KMIPBoolean(kmip::TagKeyValuePresent, bVal) {}
};

class KMIPSensitive : public KMIPBoolean {
    public:
        KMIPSensitive(bool bVal) : KMIPBoolean(kmip::TagSensitive, bVal) {}
};

class KMIPAlwaysSensitive : public KMIPBoolean {
    public:
        KMIPAlwaysSensitive(bool bVal) : KMIPBoolean(kmip::TagAlwaysSensitive, bVal) {}
};

class KMIPExtractable : public KMIPBoolean {
    public:
        KMIPExtractable(bool bVal) : KMIPBoolean(kmip::TagExtractable, bVal) {}
};

class KMIPNeverExtractable : public KMIPBoolean {
    public:
        KMIPNeverExtractable(bool bVal) : KMIPBoolean(kmip::TagNeverExtractable, bVal) {}
};


#endif
