/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPTESTCASEVALIDATOR_H
#define _KMIPTESTCASEVALIDATOR_H

#include <string>
#include <map>
#include <pugixml.hpp>

class KMIPField;
class KMIPTestCaseValidator {
    public:
        KMIPTestCaseValidator();
        bool loadXMLFile(const std::string &sExpected);
        bool loadXML(const std::string &sExpected);
        bool matchesExpected(const KMIPField *pkf);
        bool matchesExpected(const KMIPField *pkf, const pugi::xml_node &node);
        void clear();

    protected:
        std::map<std::string, std::string> mapPlaceHolderCache;
        pugi::xml_document doc;
};


#endif
