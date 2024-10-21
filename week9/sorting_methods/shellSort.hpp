#ifndef SHELLSORT
#define SHELLSORT

#include "insertionSortHelper.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSort(std::vector<int>& vector, char type){
    int swaps;
	int gap = vector.size() / 2; // first gap will be (size / 2)
	while (gap > 0) {
		for (int start = 0; start < gap; start++) 
			swaps = insertionSortHelper(vector, start, gap);
		gap /= 2; // subsequent gaps (size/4), (size/8) . . . etc
	}
    return sortData(type, vector.size(), swaps);
}

#endif