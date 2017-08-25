/* Copyright (C) 2017 Alexander Downey */
#include "KMIPXMLUtils.h"
#include "KMIPDefs.h"
#include "KMIPUtils.h"

int KMIPXMLUtils::getTag(const pugi::xml_node &node) {
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

    return iTag;
}

int KMIPXMLUtils::getType(const pugi::xml_node &node) {
    std::string sType;
    int iType;
    pugi::xml_attribute attr = node.attribute("type");
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

    return iType;
}

std::string KMIPXMLUtils::getValue(const pugi::xml_node &node) {
    pugi::xml_attribute attr = node.attribute("value");
    return attr ? attr.as_string() : std::string();
}
