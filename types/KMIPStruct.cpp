#include "KMIPStruct.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"
#include "KMIPNumber.h"
#include "KMIPString.h"
#include "KMIPEnumeration.h"
#include "KMIPDateTime.h"

KMIPStruct::KMIPStruct(int iTag) : KMIPField(iTag, kmip::TypeStructure) {
    pkfo = KMIPUtils::getKMIPFieldOrder(iTag, 0);
}

bool KMIPStruct::addField(const std::shared_ptr<KMIPField> &spkf) {
    this->listFields.push_back(spkf);
    return true;
}

bool KMIPStruct::addFields(const std::list<std::shared_ptr<KMIPField> > &listFields) {
    this->listFields.insert(this->listFields.end(), listFields.begin(), listFields.end());
    return true;
}

bool KMIPStruct::copyFields(const std::list<std::shared_ptr<KMIPField> > &listFields) {
    for (auto spkf : listFields) {
        if (spkf) {
            KMIPFieldSP spkfCopy = spkf->cloneShared();
            if (spkfCopy) {
                this->listFields.push_back(spkfCopy);
            }
        }
    }

    return true;
}

KMIPField *KMIPStruct::clone() const {
    KMIPStruct *pkst = clone2<KMIPStruct, KMIPField>();
    if (pkst) {
        pkst->copyFields(this->listFields);
    }

    return pkst;
}

bool KMIPStruct::addOrderedField(const std::shared_ptr<KMIPField> &spkf, bool bReplace) {
    bool bOK = static_cast<bool>(spkf);
    if (hasOrder()) {
        auto iterOrder = pkfo->begin();
        for (; iterOrder != pkfo->end(); ++iterOrder) {
            if (iterOrder->tagMatches(spkf->getTag()) && iterOrder->typeMatches(spkf->getType())) {
                break;
            }
        }

        if (iterOrder != pkfo->end() && iterOrder->getMax() > 0) {
            auto iterOrderPrev = pkfo->begin();
            auto iterField = listFields.begin();
            while (iterField != listFields.end()) {
                if (iterOrderPrev->tagMatches((*iterField)->getTag())
                        && iterOrderPrev->typeMatches((*iterField)->getType())) {
                    ++iterField;
                } else {
                    if (iterOrderPrev == iterOrder) {
                        break;
                    }

                    ++iterOrderPrev;
                }
            }

            int iCount = 0;
            while (iterField != listFields.end() && (*iterField)->getTag() == spkf->getTag()
                    && (*iterField)->getType() == spkf->getType() && iCount < iterOrder->getMax()) {
                ++iterField;
                ++iCount;
            }

            if (iCount < iterOrder->getMax()) {
                listFields.insert(iterField, spkf);
            } else if (bReplace) {
                --iterField;
                *iterField = spkf;
            } else {
                bOK = false;
            }
        } else {
            bOK = false;
        }
    } else {
        addField(spkf);
    }

    return bOK;
}

bool KMIPStruct::removeField(int iTag) {
    listFields.remove_if(
            [iTag](std::shared_ptr<KMIPField> &spkf) { return spkf->getTag() == iTag; }
            );
    return true;
}

bool KMIPStruct::removeField(int iTag, int iIndex) {
    bool bOK = iIndex >= 0;
    int iCount = 0;
    if (bOK) {
        auto iter = listFields.begin();
        bOK = false;
        while (iter != listFields.end()) {
            if ((*iter)->getTag() == iTag) {
                if (iCount == iIndex) {
                    listFields.erase(iter++);
                    bOK = true;
                    break;
                } else {
                    ++iter;
                    ++iCount;
                }
            } else {
                ++iter;
            }
        }
    }

    return bOK;
}

bool KMIPStruct::removeFieldBack(int iTag, int iIndex) {
    bool bOK = iIndex >= 0;
    int iCount = 0;
    if (bOK) {
        auto iter = listFields.rbegin();
        bOK = false;
        while (iter != listFields.rend()) {
            if ((*iter)->getTag() == iTag) {
                if (iCount == iIndex) {
                    ++iter;
                    listFields.erase(iter.base());
                    bOK = true;
                    break;
                } else {
                    ++iter;
                    ++iCount;
                }
            } else {
                ++iter;
            }
        }
    }

    return bOK;
}

void KMIPStruct::clear() {
    listFields.clear();
}

std::list<std::shared_ptr<KMIPField> > KMIPStruct::getFields() const {
    return listFields;
}

kmipsize_t KMIPStruct::calculateLength() const {
    kmipsize_t iRet = 0;
    for (auto pkf : listFields) {
        iRet += kmip::kiMinFieldSize + KMIPUtils::getTotalLength(pkf->calculateLength());
    }

    return iRet;
}

kmipsize_t KMIPStruct::setCalculatedLength() {
    kmipsize_t iRet = 0;
    for (auto pkf : listFields) {
        iRet += kmip::kiMinFieldSize + KMIPUtils::getTotalLength(pkf->setCalculatedLength());
    }

    setLength(iRet);

    return iRet;
}

bool KMIPStruct::hasOrder() const {
    return static_cast<bool>(pkfo);
}

bool KMIPStruct::isOrdered() const {
    bool bOK = hasOrder();
    if (bOK) {
        auto iterField = listFields.begin();
        auto iterOrder = pkfo->begin();
        int iCount = 0;
        while (iterField != listFields.end() && iterOrder != pkfo->end()) {
            if (!(*iterField)) {
                bOK = false;
                break;
            }

            if (iterOrder->getTag() == (*iterField)->getTag() &&
                    (iterOrder->getType() == (*iterField)->getType()
                     || iterOrder->getType() == kmip::TypeUnknown)) {
                ++iCount;
                if (iCount > iterOrder->getMax()) {
                    bOK = false;
                    break;
                }

                ++iterField;
            } else {
                if (iCount < iterOrder->getMin()) {
                    bOK = false;
                    break;
                }

                ++iterOrder;
                iCount = 0;
            }
        }

        bOK = bOK && iterField == listFields.end();
        if (bOK && iterOrder != pkfo->end()) {
            while (iterOrder != pkfo->end()) {
                if (iterOrder->getMin() > 0) {
                    bOK = false;
                    break;
                }

                ++iterOrder;
            }
        }
    }

    return bOK;
}

bool KMIPStruct::isValid() const {
    bool bOK = true;
    for (auto pkf : listFields) {
        bOK = pkf && pkf->isValid();
        if (!bOK) {
            break;
        }
    }

    return bOK && (!hasOrder() || isOrdered());
}

bool KMIPStruct::operator==(const KMIPField &kfRight) const {
    const KMIPStruct *pkst = dynamic_cast<const KMIPStruct *>(&kfRight);
    return pkst && operator==(*pkst);
}

bool KMIPStruct::operator==(const KMIPStruct &kfRight) const {
    bool bRet = this->KMIPField::operator==(kfRight) && listFields.size() == kfRight.listFields.size();
    if (bRet) {
        auto listLeft = listFields.begin();
        auto listRight = kfRight.listFields.begin();
        for (; listLeft != listFields.end() && bRet; ++listRight, ++listLeft) {
            if (!(*listRight) || !(*listLeft)) {
                bRet = false;
            } else {
                bRet = *(*listRight) == *(*listLeft);
            }
        }
    }

    return bRet;
}

size_t KMIPStruct::getFieldNumber(int iTag, int iType) const {
    size_t tRet = 0;
    if (iTag == kmip::TagUnknown && iType == kmip::TypeUnknown) {
        tRet = listFields.size();
    } else {
        for (auto spkf : listFields) {
            if (spkf && (iTag  == kmip::TagUnknown  || spkf->getTag()  == iTag)
                     && (iType == kmip::TypeUnknown || spkf->getType() == iType)) {
                ++tRet;
            }
        }
    }

    return tRet;
}


bool KMIPStruct::setOrderedInteger(int iTag, int iVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPInteger>(iTag, iVal);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPInteger>(iTag, kmip::TypeInteger, iVal);
#if 0
        KMIPFieldSP spkf(KMIPUtils::createField(iTag, kmip::TypeInteger).release());
        std::shared_ptr<KMIPInteger> spki = std::static_pointer_cast<KMIPInteger>(spkf);
        if (spki) {
            spki->setValue(iVal);
            bOK = addOrderedField(spki);
        }
#endif
    }

    return bOK;
}

bool KMIPStruct::setOrderedLongInteger(int iTag, long int liVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPLongInteger>(iTag, liVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPLongInteger>(iTag, kmip::TypeLongInteger, liVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedBigInteger(int iTag, const std::string &sVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPBigInteger>(iTag, sVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPBigInteger>(iTag, kmip::TypeBigInteger, sVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedEnumeration(int iTag, uint32_t uiVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPEnumeration>(iTag, uiVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPEnumeration>(iTag, kmip::TypeEnumeration, uiVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedBoolean(int iTag, bool bVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPBoolean>(iTag, bVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPBoolean>(iTag, kmip::TypeBoolean, bVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedTextString(int iTag, const std::string &sVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPTextString>(iTag, sVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPTextString>(iTag, kmip::TypeTextString, sVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedByteString(int iTag, const std::string &sVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPByteString>(iTag, sVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPByteString>(iTag, kmip::TypeByteString, sVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedDateTime(int iTag, const DateTime &dtVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPDateTime>(iTag, dtVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPDateTime>(iTag, kmip::TypeDateTime, dtVal);
    }

    return bOK;
}

bool KMIPStruct::setOrderedInterval(int iTag, uint32_t uiVal, int iIndex, bool bCreate) {
    bool bOK = setChildValue<KMIPInterval>(iTag, uiVal, iIndex);
    if (!bOK && bCreate) {
        bOK = addOrderedChild<KMIPInterval>(iTag, kmip::TypeInterval, uiVal);
    }

    return bOK;
}

bool KMIPStruct::setValueFromTTLV(const std::string &sValue) {
    return KMIPTTLVEncoding().decodeKMIPStruct(this, sValue);
}

std::string KMIPStruct::getTTLVValue() const {
    std::string sRet;
    std::string sValue;
    for (auto pkf : listFields) {
        sValue = pkf->getTTLVValue();
        kmipsize_t iRet = pkf->getType() == kmip::TypeStructure ? sValue.size() : pkf->calculateLength();
        sRet += KMIPTTLVEncoding::encodeTagTypeLength(pkf->getTag(), pkf->getType(), iRet) + sValue;
    }
    
    return sRet;
}
