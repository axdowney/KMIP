/* Copyright (C) 2017 Alexander Downey */

#include "KMIPFieldOrders.h"

KMIPFieldOrders::KMIPFieldOrders() {
}


KMIPFieldOrder *KMIPFieldOrders::getKMIPFieldOrder(int iTag, int iType) {
    KMIPFieldOrder *pkfo = nullptr;
    auto mapKFOByType = mapKFOs.find(iTag);
    if (mapKFOByType != mapKFOs.end()) {
        auto iterKFO = mapKFOByType->second.find(iType);
        if (iterKFO != mapKFOByType->second.end()) {
            pkfo = &(iterKFO->second);
        }
    }

    return pkfo;
}
