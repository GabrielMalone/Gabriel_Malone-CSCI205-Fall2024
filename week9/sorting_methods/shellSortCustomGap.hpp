#ifndef SHELLSORTCUSTOMGAPS
#define SHELLSORTCUSTOMGAPS

#include "helper_methods/insertionSortGap.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSortCustomGaps(std::vector<int>& vector, std::vector<int>& gaps, char type, bool print){
    unsigned long long array_accesses = 0;
    unsigned long long comparisons = 0;
	for (size_t i = 0 ; i < gaps.size(); i ++ ){
        size_t gap = gaps[i];
        for (size_t start = 0; start < gap; start++) {
            sortData s = gapInsertionSort(vector, start, gap, print);
			array_accesses += s.array_accesses;
			comparisons += s.comparisons;
        }
    }
    return sortData(type, vector.size(), array_accesses, comparisons);
}
#endif