#ifndef INSERTIONSORTGAP
#define INSERTIONSORTGAP

#include "../../backend/print_graph.hpp"
#include "../../backend/sort_data.hpp"

#include <vector>
// ---------------------------------------------------------------------------------------------------------------------------
// modified insertion sort helper to work with gaps for the shell sort
// same logic as the insertion but allows larger jumps
// ---------------------------------------------------------------------------------------------------------------------------
sortData gapInsertionSort(std::vector<int>& avector, int start, int gap, bool print) {
	//------------------------------------------------------------------------------------------------------------------------
	unsigned long long array_accesses = 0;																	// data collection
	unsigned long long comparisons = 0;
	//------------------------------------------------------------------------------------------------------------------------
	for (size_t i = start + gap; i < avector.size(); i += gap) {
		comparisons ++ ; 
		int current	= avector[i];					            								     // remember current item
		int pos	= i;
		//--------------------------------------------------------------------------------------------------------------------
		while (pos >= gap && avector[pos - gap] > current) {      // while not at front and current item is less than previous
			avector[pos] = avector[pos - gap];			        									   // shift by "gap" spots
			if (print){
				printTowers(avector, avector[pos]);
				printTowers(avector, avector[pos - gap]);
			}
			pos -= gap;							                								// decrease position by "gap"
			array_accesses ++ ;
		}
		//--------------------------------------------------------------------------------------------------------------------
		avector[pos] = current;							        						  // place current item in opened spot
		//--------------------------------------------------------------------------------------------------------------------
	}
	//------------------------------------------------------------------------------------------------------------------------
	if (print)																							   // graphical output
		printTowers(avector, 100);
	//------------------------------------------------------------------------------------------------------------------------
	return sortData('x', 0, array_accesses, comparisons);
	//------------------------------------------------------------------------------------------------------------------------
}

#endif