#ifndef SHELLSORTBASIC
#define SHELLSORTBASIC

#include "helper_methods/insertionSortGap.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSortBasic(std::vector<int>& vector, char type){
	unsigned long long comparisons = 0;
    unsigned long long array_accesses = 0;
	int gap = vector.size() / 2; // first gap will be (size / 2)
	while (gap > 0) {
		for (int start = 0; start < gap; start++) {
			sortData s = gapInsertionSort(vector, start, gap);
			array_accesses += s.array_accesses;
			comparisons += s.comparisons;
        }
		gap /= 2; // subsequent gaps (size/4), (size/8) . . . etc
	}
    return sortData(type, vector.size(), array_accesses, comparisons);
}

#endif