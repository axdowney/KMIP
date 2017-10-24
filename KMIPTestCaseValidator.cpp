/* Copyright (C) 2017 Alexander Downey */
#include <fstream>
#include <sstream>
#include "KMIPTestCaseValidator.h"
#include "KMIPDefs.h"
#include "KMIPXMLUtils.h"
#include "KMIPField.h"
#include "KMIPStruct.h"

KMIPTestCaseValidator::KMIPTestCaseValidator() {}
bool KMIPTestCaseValidator::loadXMLFile(const std::string &sExpected) {
    std::ifstream t(sExpected);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string sXML_In = buffer.str();
    return loadXML(sXML_In);
}

bool KMIPTestCaseValidator::loadXML(const std::string &sExpected) {
    return doc.load_string(sExpected.c_str());
}

bool KMIPTestCaseValidator::matchesExpected(const KMIPField *pkf) {
    return matchesExpected(pkf, doc.first_child());
}

bool KMIPTestCaseValidator::matchesExpected(const KMIPField *pkf, const pugi::xml_node &node) {
    bool bOK = pkf && node;
    if (bOK) {
        int iTag = KMIPXMLUtils::getTag(node);
        int iType = KMIPXMLUtils::getType(node);
        bOK = pkf->getTag() == iTag
            & pkf->getType() == iType;
        if (bOK) {
            if (iType != kmip::TypeStructure) {
                std::string sValue = KMIPXMLUtils::getValue(node);
                if (!sValue.empty()) {
                    if (sValue[0] == '$') {
                        auto mapIter = mapPlaceHolderCache.find(sValue);
                        if (mapIter == mapPlaceHolderCache.end()) {
                            mapPlaceHolderCache[sValue] = pkf->getXMLValue();
                        } else {
                            sValue = mapIter->second;
                        }
                    }

                    KMIPFieldSP spkf = pkf->cloneShared();
                    bOK = spkf->setValueFromXML(sValue) && *spkf == *pkf;
                } else {
                    const KMIPStruct *pkst = dynamic_cast<const KMIPStruct *>(pkf);
                    if (pkst) {
                        pugi::xml_node nodeChild = node.first_child();
                        for (auto pkfc : pkst->getChildren<KMIPField>()) {
                            if (!matchesExpected(pkfc.get(), nodeChild)) {
                                bOK = false;
                                break;
                            }
                            nodeChild = nodeChild.next_sibling();
                        }
                    }
                }
            }
        }
    }

    return bOK;
}

void KMIPTestCaseValidator::clear() {
    mapPlaceHolderCache.clear();
}
