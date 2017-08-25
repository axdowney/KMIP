/* Copyright (C) 2017 Alexander Downey */
#include "KMIPEncoding.h"

class KMIPField;
class KMIPStruct;
class KMIPXMLEncoding : public KMIPEncoding {
    public:
        KMIPXMLEncoding();
        virtual std::string encodeKMIP(KMIPField *pkf) const;
        virtual KMIPFieldUP decodeKMIP(std::string sField, std::string &sExtra) const;
        bool decodeKMIPStruct(KMIPStruct *pkst, const std::string &sFields) const;
        bool decodeKMIPSingleField(KMIPField *pkf, const std::string &sValue) const;
};
