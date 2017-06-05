#include "KMIPStruct.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

KMIPStruct::KMIPStruct(int iTag) : KMIPField(iTag, kmip::TypeStructure) {
    pkfo = KMIPUtils::getKMIPFieldOrder(iTag, 0);
}

bool KMIPStruct::addField(const std::shared_ptr<KMIPField> &spkf) {
    this->listFields.push_back(spkf);
}

bool KMIPStruct::removeField(int iTag) {
    listFields.remove_if(
            [iTag](std::shared_ptr<KMIPField> &spkf) { return spkf->getTag() == iTag; }
            );
    /*
    auto iter = listFields.begin();
    while (iter != listFields.end()) {
        if ((*iter)->getTag() == iTag) {
            listFields.erase(iter++);
        } else {
            ++iter;
        }
    }
    */
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

            if (iterOrder->getTag() == (*iterField)->getTag()
                    && iterOrder->getType() == (*iterField)->getType()) {
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

        bOK = bOK && iterField == listFields.end() && iterOrder == pkfo->end();
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
