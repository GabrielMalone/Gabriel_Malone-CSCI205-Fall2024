#ifndef SWAP
#define SWAP

#include <vector>

// helper function to swap two vector elements
template <typename T>
void swap(std::vector<T>& vec, int a, int b){
	T temp	    = vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}

#endif