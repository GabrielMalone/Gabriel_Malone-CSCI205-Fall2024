#ifndef SWAP
#define SWAP

#include <vector>

// helper function to swap two vector elements
void swap(std::vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}

#endif