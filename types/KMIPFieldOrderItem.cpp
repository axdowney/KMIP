#include "KMIPFieldOrderItem.h"

KMIPFieldOrderItem::KMIPFieldOrderItem(int iTag, int iType, int iMin, int iMax) : vecItems(4,0) {
    vecItems[ItemTag] = iTag;
    vecItems[ItemType] = iType;
    vecItems[ItemMin] = iMin;
    vecItems[ItemMax] = iMax;
}

int KMIPFieldOrderItem::getItem(KMIPFieldOrderItem::Item eItem) {
    int iRet = ItemError;
    if (iRet > ItemError && iRet < ItemLast) {
        iRet = vecItems[eItem];
    }

    return iRet;
}

int KMIPFieldOrderItem::getTag() {
    return getItem(ItemTag);
}

int KMIPFieldOrderItem::getType() {
    return getItem(ItemType);
}

int KMIPFieldOrderItem::getMin() {
    return getItem(ItemMin);
}

int KMIPFieldOrderItem::getMax() {
    return getItem(ItemMax);
}
