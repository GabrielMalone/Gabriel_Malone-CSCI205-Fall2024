#ifndef SHELLSORTBASIC
#define SHELLSORTBASIC

#include "helper_methods/insertionSortGap.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSortBasic(std::vector<int>& vector, char type){
	int comparisons = 0;
    int swaps = 0;
	int gap = vector.size() / 2; // first gap will be (size / 2)
	while (gap > 0) {
		for (int start = 0; start < gap; start++) {
			sortData s = gapInsertionSort(vector, start, gap);
			swaps += s.swaps;
			comparisons += s.comparisons;
        }
		gap /= 2; // subsequent gaps (size/4), (size/8) . . . etc
	}
    return sortData(type, vector.size(), swaps, comparisons);
}

#endif