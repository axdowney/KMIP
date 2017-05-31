#ifndef _KMIPFIELDORDERITEM_H
#define _KMIPFIELDORDERITEM_H

#include <vector>


class KMIPFieldOrderItem {
    public:
        enum Item {
            ItemError = -1,
            ItemTag = 0,
            ItemType,
            ItemMin,
            ItemMax,
            ItemLast,
        };

        KMIPFieldOrderItem(int iTag, int iType, int iMin = 0, int iMax = 1);

        int getItem(Item eItem);
        int getTag();
        int getType();
        int getMin();
        int getMax();

    protected:
        std::vector<int> vecItems;
};


#endif
