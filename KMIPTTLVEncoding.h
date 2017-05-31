#ifndef _KMIPTTLVENCODING_H
#define _KMIPTTLVENCODING_H

#include "KMIPEncoding.h"
class KMIPStruct;

class KMIPTTLVEncoding : public KMIPEncoding {
    public:
        using KMIPEncoding::decodeKMIP;
        virtual KMIPFieldUP decodeKMIP(std::string sField, std::string &sExtra) const;
        virtual std::string encodeKMIP(KMIPField *pkf) const;
        static unsigned long int binaryToInt(const std::string &s);
        static std::string intToBinary(unsigned long int iNumber, unsigned int iBytes);
        static std::string getBuffer(unsigned int iLength);
        bool decodeKMIPStruct(KMIPStruct *pkst, const std::string &sFields) const;
        bool decodeKMIPSingleField(KMIPField *pkf, const std::string &sValue) const;
        static std::string encodeTagTypeLength(int iTag, int iType, kmipsize_t iLength);

};


#endif
