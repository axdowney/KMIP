/* Copyright (C) 2017 Alexander Downey */
#include <pugixml.hpp>
#include <vtkm/exec/ConnectivityPermuted.h>
class KMIPXMLUtils {
    public:
        static int getTag(const pugi::xml_node &node);
        static int getType(const pugi::xml_node &node);
        static std::string getValue(const pugi::xml_node &node);
};
