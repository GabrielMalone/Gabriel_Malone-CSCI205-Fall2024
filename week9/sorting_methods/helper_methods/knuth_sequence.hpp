#ifndef KNUTH
#define KNUTH

#include <vector>
#include <cmath>

std::vector<int> knuth (int size){
 	std::vector<int> gap_sequence;
	int h = 1;
	while(h <= size / 3){ // 1/3 of the list size
		gap_sequence.insert(gap_sequence.begin(), h);
		h = h*3 + 1; 	// increase h
	}
	return gap_sequence;
}

#endif