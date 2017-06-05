/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPBITMASK_H
#define _KMIPBITMASK_H

#include <vector>

#include "KMIPNumber.h"
#include "EnumMacros.h"

class KMIPBitMask : public KMIPInteger {
    public:
        KMIPBitMask(int iTag, int iVal = int(), int iFullMask = -1);
        virtual bool isValid() const;
        int getFullMask() const;
        std::vector<int> splitFlags() const;
        virtual std::string getFlagName(int iFlag) const;

    protected:
        int iFullMask;
};

class KMIPCryptographicUsageMask : public KMIPBitMask {
#define CRYPTOGRAPHIC_USAGE_MASK_LIST(a,b) \
        b(None, 0x0) \
	b(Sign,	0x1) \
	b(Verify,	0x2) \
	b(Encrypt,	0x4) \
	b(Decrypt,	0x8) \
	b(WrapKey,	0x10) \
	b(UnwrapKey,	0x20) \
	b(Export,	0x40) \
	b(MACGenerate,	0x80) \
	b(MACVerify,	0x100) \
	b(DeriveKey,	0x200) \
	b(ContentCommitment,	0x400) \
	b(KeyAgreement,	0x800) \
	b(CertificateSign,	0x1000) \
	b(CRLSign,	0x2000) \
	b(GenerateCryptogram,	0x4000) \
	b(ValidateCryptogram,	0x8000) \
	b(TranslateEncrypt,	0x10000) \
	b(TranslateDecrypt,	0x20000) \
	b(TranslateWrap,	0x40000) \
	b(TranslateUnwrap,	0x80000) \
        b(FullMask,             0xFFFFF)

	DECLARE_ENUM_LIST(VALUE, CRYPTOGRAPHIC_USAGE_MASK_LIST)
	KMIPCryptographicUsageMask(int iVal);
        virtual std::string getFlagName(int iFlag) const;
};

class KMIPStorageStatusMask : public KMIPBitMask {
#define STORAGE_STATUS_MASK_LIST(a,b) \
        b(None,                 0x0) \
	b(OnLineStorage,	0x1) \
	b(ArchivalStorage,	0x2) \
        b(FullMask,             0x3)

	DECLARE_ENUM_LIST(VALUE, STORAGE_STATUS_MASK_LIST)
	KMIPStorageStatusMask(int iVal);
        virtual std::string getFlagName(int iFlag) const;
};


#endif
