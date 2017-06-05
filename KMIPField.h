#ifndef _KMIPFIELD_H
#define _KMIPFIELD_H

#include <string>
#include <memory>

typedef int64_t kmipsize_t;
class KMIPField {
    public:
        KMIPField(int iTag, int iType);
        int getTag() const;
        int getType() const;
        int getLength() const;

        void setLength(kmipsize_t iLength);
        virtual kmipsize_t calculateLength() const;
        virtual kmipsize_t setCalculatedLength();
        virtual std::string getValueString() const;

        virtual bool isValid() const;

        virtual bool setValueFromTTLV(const std::string &sValue);
        virtual std::string getTTLVValue() const;

        static const kmipsize_t kiInvalidLength = -1;
    private:
        int iTag;
        int iType;
        kmipsize_t iLength;
        std::string sField;
};

typedef std::shared_ptr<KMIPField> KMIPFieldSP;
typedef std::unique_ptr<KMIPField> KMIPFieldUP;

#endif
