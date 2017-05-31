/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPSTRUCT_H
#define _KMIPSTRUCT_H

#include "KMIPField.h"

#include <list>
#include <memory>

class KMIPStruct : public KMIPField {
    public:
        explicit KMIPStruct(int iTag);
        bool addField(const std::shared_ptr<KMIPField> &spkf);
        bool removeField(int iTag);
        std::list<std::shared_ptr<KMIPField> > getFields() const;

        virtual kmipsize_t calculateLength() const;
        virtual kmipsize_t setCalculatedLength();
        
        virtual std::string getTTLVValue() const;
    protected:
        std::list<std::shared_ptr<KMIPField> > listFields;
};


#endif
