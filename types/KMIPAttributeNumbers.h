/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPATTRIBUTENUMBERS_H
#define _KMIPATTRIBUTENUMBERS_H

#include "KMIPNumber.h"

class KMIPCryptographicLength : public KMIPInteger {
};

class KMIPLeaseTime : public KMIPInterval {
};

class KMIPFresh : public KMIPBoolean {
};

class KMIPKeyValuePresent : public KMIPBoolean {
};

class KMIPSensitive : public KMIPBoolean {
};

class KMIPAlwaysSensitive : public KMIPBoolean {
};

class KMIPExtractable : public KMIPBoolean {
};

class KMIPNeverExtractable : public KMIPBoolean {
};


#endif
