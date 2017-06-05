/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPFACTORY_H
#define _KMIPFACTORY_H

#include <memory>

class KMIPField;
class KMIPFactory {
    public:
        KMIPFactory() {}
        virtual ~KMIPFactory() {}
        virtual std::unique_ptr<KMIPField> createField(int iTag) const;
};


#endif
