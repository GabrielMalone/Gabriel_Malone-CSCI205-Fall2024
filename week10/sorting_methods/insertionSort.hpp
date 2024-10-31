#ifndef INSERTIONSORT
#define INSERTIONSORT

#include <vector>
#include "../backend/sort_data.hpp"

void insertionSort(std::vector<int>& vector, int start, int end, bool print, sortData& s){
	for (int index = start; index < end; index ++) {
		int current = vector[index];					// remember current item
		int pos = index;								// need current position to move towards front
		while (pos > 0 && vector[pos - 1] > current) {	// while not at front and current item is less than previous
			vector[pos] = vector[pos - 1];				// shift by 1 spot
			pos--; 										// keep moving towards front of vector
			s.array_accesses ++ ;
			if (print)
				printTowers(vector, vector[pos]);						
		}
		vector[pos] = current;							// place current item in opened spot
		s.comparisons ++ ; 	
	}
	if (print)
		printTowers(vector, 100);
}

#endif 