#ifndef _KMIPFIELDORDERITEM_H
#define _KMIPFIELDORDERITEM_H

#include <vector>
#include <set>


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
        KMIPFieldOrderItem(int iTag, const std::set<int> &setTypes, int iMin = 0, int iMax = 1);

        int getItem(Item eItem) const;
        int getTag() const;
        int getType() const;
        int getMin() const;
        int getMax() const;

        bool tagMatches(int iTag) const;
        bool typeMatches(int iType) const;

    protected:
        std::vector<int> vecItems;
        std::set<int> setTypes;
};


#endif
