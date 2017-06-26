#include "KMIPFieldOrderItem.h"
#include "KMIPDefs.h"

KMIPFieldOrderItem::KMIPFieldOrderItem(int iTag, int iType, int iMin, int iMax) : vecItems({iTag, iType, iMin, iMax}) {
}

KMIPFieldOrderItem::KMIPFieldOrderItem(int iTag, const std::set<int> &setTypes, int iMin, int iMax) : vecItems({iTag, kmip::TypeMulti, iMin, iMax}), setTypes(setTypes) {
}

int KMIPFieldOrderItem::getItem(KMIPFieldOrderItem::Item eItem) const {
    int iRet = ItemError;
    if (eItem > ItemError && eItem < ItemLast) {
        iRet = vecItems[eItem];
    }

    return iRet;
}

int KMIPFieldOrderItem::getTag() const {
    return getItem(ItemTag);
}

int KMIPFieldOrderItem::getType() const {
    return getItem(ItemType);
}

int KMIPFieldOrderItem::getMin() const {
    return getItem(ItemMin);
}

int KMIPFieldOrderItem::getMax() const {
    return getItem(ItemMax);
}

bool KMIPFieldOrderItem::tagMatches(int iTag) const {
    return getTag() == iTag || getTag() == kmip::TagUnknown;
}

bool KMIPFieldOrderItem::typeMatches(int iType) const {
    return getType() == iType || getType() == kmip::TypeUnknown
        || getType() == kmip::TypeMulti && setTypes.find(iType) != setTypes.end();
}
