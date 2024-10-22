#ifndef INSERTIONSORTGAP
#define INSERTIONSORTGAP

#include <vector>
// ---------------------------------------------------------------------------------------------------------------------------
// modified insertion sort helper to work with gaps for the shell sort
// same logic as the insertion but allows larger jumps
// ---------------------------------------------------------------------------------------------------------------------------
sortData gapInsertionSort(std::vector<int>& avector, int start, int gap) {
	//---------------------------------------------------------------------------
	unsigned long long array_accesses = 0;
	unsigned long long comparisons = 0;
	//---------------------------------------------------------------------------
	for (unsigned int i = start + gap; i < avector.size(); i += gap) {
		comparisons ++ ; 
		int current	= avector[i];					            // remember current item
		int pos	= i;							                // need current position to move towards front
		//---------------------------------------------------------------------------
		while (pos >= gap && avector[pos - gap] > current) {    // while not at front and current item is less than previous
			avector[pos] = avector[pos - gap];			        // shift by "gap" spots
			pos -= gap;							                // decrease position by "gap"
			array_accesses ++ ;
		}
		//---------------------------------------------------------------------------
		avector[pos] = current;							        // place current item in opened spot
		//---------------------------------------------------------------------------
	}
	//---------------------------------------------------------------------------
	return sortData('x', 0, array_accesses, comparisons);
}

#endif