/* Copyright (C) 2017 Alexander Downey */
#ifndef _KMIPFIELDORDERS_H
#define _KMIPFIELDORDERS_H

#include <map>

#include "KMIPFieldOrder.h"
#include "KMIPFieldOrderItem.h"

class KMIPFieldOrders {
    public:
        KMIPFieldOrders();
        KMIPFieldOrder *getKMIPFieldOrder(int iTag, int iType = 0);
    protected:
        std::map<int, std::map<int, KMIPFieldOrder> > mapKFOs;
};

#endif
