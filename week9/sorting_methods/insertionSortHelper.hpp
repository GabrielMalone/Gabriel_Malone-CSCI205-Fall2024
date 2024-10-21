#ifndef INSERTIONSORT_HELPER
#define INSERTIONSORT_HELPER

#include <vector>
#include "../backend/sort_data.hpp"

int insertionSortHelper(std::vector<int>& vector, int start, int gap){
	int swaps = 0;
	for (unsigned int i = start + gap; i < vector.size(); i += gap) {
		int current		= vector[i];					// remember current item
		int pos			= i;							// need current position to move towards front
		while (pos >= gap && vector[pos - gap] > current) { // while not at front and current item is less than previous
			vector[pos] = vector[pos - gap];			// shift by "gap" spots
			pos		 	-= gap;							// decrease position by "gap"
			swaps ++ ;
		}
		vector[pos] = current;							// place current item in opened spot
	}
	return swaps;
}

#endif 