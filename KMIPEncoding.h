#ifndef _KMIPENCODING_H
#define _KMIPENCODING_H

#include "KMIPField.h"

class KMIPEncoding {
    public:
        virtual std::string encodeKMIP(KMIPField *pkf) const=0;
        virtual KMIPFieldUP decodeKMIP(std::string sField, std::string &sExtra) const=0;
        virtual KMIPFieldUP decodeKMIP(const std::string &sField) const {
            std::string sExtra;
            return decodeKMIP(sField, sExtra);
        }

        std::string encodeKMIP(const KMIPFieldSP &spkf) const {
            return encodeKMIP(spkf.get());
        }

        std::string encodeKMIP(const KMIPFieldUP &upkf) const {
            return encodeKMIP(upkf.get());
        }
};


#endif
