#ifndef INSERTIONSORT
#define INSERTIONSORT

#include <vector>
#include "../backend/sort_data.hpp"

sortData insertionSort(std::vector<int>& vector, char type, bool print){
    unsigned long long swaps = 0;
	unsigned long long comparisons = 0;
	for (size_t index = 1; index < vector.size(); index ++) {
		int current = vector[index];					// remember current item
		int pos = index;								// need current position to move towards front
		while (pos > 0 && vector[pos - 1] > current) {	// while not at front and current item is less than previous
			vector[pos] = vector[pos - 1];				// shift by 1 spot
			pos--; 										// keep moving towards front of vector
			swaps ++ ;
			if (print)
				printTowers(vector, vector[pos]);						
		}
		vector[pos] = current;							// place current item in opened spot
		comparisons ++ ; 	
	}
	if (print)
		printTowers(vector, 100);
    return sortData(type, vector.size(), swaps, comparisons);
}

#endif 