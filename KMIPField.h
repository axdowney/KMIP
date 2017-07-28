#ifndef _KMIPFIELD_H
#define _KMIPFIELD_H

#include <string>
#include <memory>

#include "PointerUtils.h"

typedef int64_t kmipsize_t;
class KMIPField;

typedef std::shared_ptr<KMIPField> KMIPFieldSP;
typedef std::unique_ptr<KMIPField> KMIPFieldUP;
typedef std::weak_ptr<KMIPField>   KMIPFieldWP;

typedef std::shared_ptr<const KMIPField> KMIPFieldSPK;
typedef std::unique_ptr<const KMIPField> KMIPFieldUPK;
typedef std::weak_ptr<const KMIPField>   KMIPFieldWPK;


class KMIPField {
    public:
        KMIPField(int iTag, int iType);
        virtual ~KMIPField();
        int getTag() const;
        int getType() const;
        int getLength() const;

        void setLength(kmipsize_t iLength);
        virtual kmipsize_t calculateLength() const;
        virtual kmipsize_t setCalculatedLength();
        virtual std::string getValueString() const;
        virtual bool setValueFromString(const std::string &sValue);

        int getTrueTag() const;
        bool isAttributeValueForced() const;
        bool forceAttributeValue(bool bForce = true);

        template<typename t>
        bool hasEqualValue(const KMIPField &kfRight) const;
        virtual bool operator==(const KMIPField &kfRight) const;
        virtual bool isValid() const;
        virtual KMIPFieldSP cloneShared() const;
        virtual KMIPFieldUP cloneUnique() const;

        template <typename t>
        std::shared_ptr<t> cloneShared() const;
        template <typename t>
        std::unique_ptr<t> cloneUnique() const;

        virtual bool setValueFromTTLV(const std::string &sValue);
        virtual std::string getTTLVValue() const;
        virtual std::string getTTLVValueTrim() const;

        static const kmipsize_t kiInvalidLength = -1;

    protected:
        virtual KMIPField *clone() const;

        template <typename t>
        t *clone1() const;

        template <typename t, typename v>
        t *clone2() const;

    private:
        int iTag;
        int iType;
        kmipsize_t iLength;
        std::string sField;
        bool bAttributeValue;
};


template<typename t>
bool KMIPField::hasEqualValue(const KMIPField &kfRight) const {
    const t *pkfRight = dynamic_cast<const t*>(&kfRight);
    const t *pkfLeft = dynamic_cast<const t*>(this);
    return pkfLeft != nullptr && pkfRight != nullptr
        && pkfLeft->getValue() == pkfRight->getValue();
}


template <typename t>
t *KMIPField::clone1() const {
    KMIPField *pkf = clone();
    t *tRet = dynamic_cast<t *>(pkf);
    if (!tRet) {
        delete pkf;
    }

    return tRet;
}

template <typename t, typename v>
t *KMIPField::clone2() const {
    KMIPField *pkf = v::clone();
    t *tRet = dynamic_cast<t *>(pkf);
    if (!tRet) {
        delete pkf;
    }

    return tRet;
}

template <typename t>
std::shared_ptr<t> KMIPField::cloneShared() const {
    return std::dynamic_pointer_cast<t>(cloneShared());
}

template <typename t>
std::unique_ptr<t> KMIPField::cloneUnique() const {
    std::unique_ptr<t> upt;
    KMIPFieldUP upkf = cloneUnique();
    dynamic_pointer_move(upt, upkf);
    return upt;
}

#endif
