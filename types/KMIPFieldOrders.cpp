/* Copyright (C) 2017 Alexander Downey */

#include "KMIPFieldOrders.h"
#include "KMIPDefs.h"

KMIPFieldOrders::KMIPFieldOrders() {
    mapKFOs[kmip::TagAttribute][0] = {
        KMIPFieldOrderItem(kmip::TagAttributeName, kmip::TypeTextString, 1),
        KMIPFieldOrderItem(kmip::TagAttributeIndex, kmip::TypeInteger),
        KMIPFieldOrderItem(kmip::TagAttributeValue, kmip::TypeUnknown)
    };
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
