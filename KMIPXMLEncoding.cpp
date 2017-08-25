/* Copyright (C) 2017 Alexander Downey */

#include <sstream>
#include <pugixml.hpp>

#include "KMIPXMLEncoding.h"
#include "KMIPUtils.h"
#include "KMIPDefs.h"
#include "KMIPStruct.h"
#include "KMIPAttribute.h"

KMIPXMLEncoding::KMIPXMLEncoding() {}

bool encodeKMIP(KMIPField *pkf, pugi::xml_node &node) {
    bool bOK = pkf;
    if (bOK) {
        pugi::xml_attribute attr;
        std::string sName;
        if (KMIPUtils::isTagKnown(pkf->getTag())) {
            sName = KMIPUtils::TagToString(pkf->getTag());
            node.set_name(sName.c_str());
        } else {
            node.set_name("TTLV");
            attr = node.append_attribute("tag");
            std::stringstream ss;
            ss << std::hex << pkf->getTag();
            attr.set_value(ss.str().c_str());
        }
        attr = node.append_attribute("type");
        attr.set_value(KMIPUtils::TypeToString(pkf->getType()).c_str());
        if (pkf->getType() == kmip::TypeStructure) {
            KMIPStruct *pkst = dynamic_cast<KMIPStruct *>(pkf);
            if (pkst) {
                for (auto spkf : pkst->getFields()) {
                    pugi::xml_node nodeChild = node.append_child("TTLV");
                    bOK = ::encodeKMIP(spkf.get(), nodeChild);
                    if (!bOK) break;
                }
            } else {
                bOK = false;
            }
        } else {
            attr = node.append_attribute("value");
            attr.set_value(pkf->getXMLValue().c_str());
        }
    }

    return bOK;
}

std::string KMIPXMLEncoding::encodeKMIP(KMIPField *pkf) const {
    pugi::xml_document doc;
    if (pkf) {
        pugi::xml_node node = doc.append_child("TTLV");
        ::encodeKMIP(pkf, node);
    }
    std::stringstream ss;
    doc.save(ss);
    return ss.str();
}

KMIPFieldUP decodeKMIPSingleField(const KMIPXMLEncoding &kxe, const pugi::xml_node &node, int iTagAV = kmip::TagAttributeValue);
bool decodeKMIPStruct(const KMIPXMLEncoding &kxe, KMIPStruct *pkst, pugi::xml_node &node) {
    bool bOK = pkst;
    if (bOK) {
        int iTagAV = kmip::TagAttributeValue;
        while (node) {
            KMIPFieldUP upkf = ::decodeKMIPSingleField(kxe, node, iTagAV);
            if (upkf) {
                if (upkf->getTag() == kmip::TagAttributeName) {
                    iTagAV = KMIPAttribute::getNameTag(upkf->getValueString());
                    if (iTagAV == kmip::TagCustomAttribute) {
                        iTagAV = kmip::TagAttributeValue;
                    }
                }
                pkst->addField(KMIPFieldSP(upkf.release()));
                node = node.next_sibling();
            } else {
                bOK = false;
            }
        }
    }

    return bOK;
}

KMIPFieldUP decodeKMIPSingleField(const KMIPXMLEncoding &kxe, const pugi::xml_node &node, int iTagAV) {
    KMIPFieldUP upkf;
    if (node) {
        bool bAV = false;
        std::string sTag;
        int iTag = kmip::TagUnknown;
        pugi::xml_attribute attr = node.attribute("tag");
        if (attr) {
            sTag = attr.as_string();
            try {
                iTag = std::stoi(sTag.c_str(), nullptr, 16);
            } catch (std::invalid_argument e) {
                iTag = kmip::TagUnknown;
            }
        } else {
            sTag = node.name();
            iTag = KMIPUtils::TagFromString(sTag);
        }

        if (iTag == kmip::TagAttributeValue) {
            iTag = iTagAV;
            bAV = true;
        }

        std::string sType;
        int iType;
        attr = node.attribute("type");
        if (attr) {
            sType = attr.as_string();
            iType = KMIPUtils::TypeFromString(sType);
            if (iType == kmip::TypeUnknown) {
                try {
                    iType = std::stoi(sType.c_str(), nullptr, 16);
                } catch (std::invalid_argument e) {
                    iType = kmip::TypeUnknown;
                }
            }
        } else {
            iType = kmip::TypeStructure;
        }

        upkf = KMIPUtils::createField(iTag, iType);
        if (upkf) {
            upkf->forceAttributeValue(bAV);
            if (iType == kmip::TypeStructure) {
                pugi::xml_node nodeChild = node.first_child();
                ::decodeKMIPStruct(kxe, dynamic_cast<KMIPStruct *>(upkf.get()), nodeChild);
            } else {
                attr = node.attribute("value");
                if (attr) {
                    kxe.decodeKMIPSingleField(upkf.get(), attr.as_string());
                }
            }
        }
    }

    return upkf;
}

KMIPFieldUP KMIPXMLEncoding::decodeKMIP(std::string sField, std::string &sExtra) const {
    KMIPFieldUP upkf;
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_string(sField.c_str());
    if (res) {
        upkf = ::decodeKMIPSingleField(*this, doc.first_child());
    }

    return upkf;
}

bool KMIPXMLEncoding::decodeKMIPStruct(KMIPStruct *pkst, const std::string &sFields) const {
}

bool KMIPXMLEncoding::decodeKMIPSingleField(KMIPField *pkf, const std::string &sValue) const {
    bool bOK = pkf;
    if (pkf) {
        bOK = pkf->setValueFromXML(sValue);
    }

    return bOK;
}
