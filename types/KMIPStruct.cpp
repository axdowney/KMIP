#include "KMIPStruct.h"
#include "KMIPDefs.h"
#include "KMIPTTLVEncoding.h"
#include "KMIPUtils.h"

KMIPStruct::KMIPStruct(int iTag) : KMIPField(iTag, kmip::TypeStructure) {}

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
