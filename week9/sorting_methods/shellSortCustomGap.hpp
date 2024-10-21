#ifndef SHELLSORTCUSTOMGAPS
#define SHELLSORTCUSTOMGAPS

#include "helper_methods/insertionSortGap.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSortCustomGaps(std::vector<int>& vector, std::vector<int>& gaps, char type){
    int swaps = 0;
	for (int i = 0 ; i < gaps.size(); i ++ ){
        int gap = gaps[i];
        for (int start = 0; start < gap; start++) {
            swaps += gapInsertionSort(vector, start, gap);
        }
    }
    return sortData(type, vector.size(), swaps);
}
#endif