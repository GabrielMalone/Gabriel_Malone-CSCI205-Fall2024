#ifndef INSERTIONSORTGAP
#define INSERTIONSORTGAP

#include <vector>
// ---------------------------------------------------------------------------------------------------------------------------
// modified insertion sort helper to work with gaps for the shell sort
// same logic as the insertion but allows larger jumps
// ---------------------------------------------------------------------------------------------------------------------------
void gapInsertionSort(std::vector<int>& avector, int start, int gap) {
	for (unsigned int i = start + gap; i < avector.size(); i += gap) {
		int current	= avector[i];					            // remember current item
		int pos	= i;							                // need current position to move towards front
		while (pos >= gap && avector[pos - gap] > current) {    // while not at front and current item is less than previous
			avector[pos] = avector[pos - gap];			        // shift by "gap" spots
			pos -= gap;							                // decrease position by "gap"
		}
		avector[pos] = current;							        // place current item in opened spot
	}
}

#endif