/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPUTILS_H
#define _KMIPUTILS_H

#include <map>
#include <string>
#include "KMIPField.h"
#include "KMIPFieldOrder.h"
//#include "KMIPAttributeRule.h"

class KMIPFactory;
class KMIPFieldOrders;
class KMIPAttributeRule;
class KMIPUtils {
    public:
        static KMIPFieldUP createField(int iTag, int iType);
        static KMIPFieldOrder *getKMIPFieldOrder(int iTag, int iType);
        static std::shared_ptr<KMIPAttributeRule> getAttributeRule(int iTag);
        static bool isTagUnknown(int iTag);
        static bool isTagReserved(int iTag);
        static bool isTagExtension(int iTag);
        static bool isTagKnown(int iTag);
        static std::string TagToString(int iTag);
        static std::string TypeToString(int iType);
        static unsigned int getTotalLength(unsigned int iLength);
        static std::string printFieldString(const KMIPField *pkf, int iDepth);

    protected:
        static const std::map<int, std::string> mapTagToString;
        static std::map<int, std::shared_ptr<KMIPFactory> > mapKMIPFactories;
        static std::shared_ptr<KMIPFieldOrders> spkfos;
        static const std::map<int, std::shared_ptr<KMIPAttributeRule> > mapTagToRule;

};


#endif
