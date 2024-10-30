#ifndef MEDIANOFTHREE
#define MEDIANOFTHREE

#include <vector>
#include "../../backend/bubblesort.hpp"
#include "validate_sort.hpp"

using namespace std;

int MO3(vector<int>& v, int left, int right, sortData& s){

 	int center = (left + right) / 2;		// find center
	swap(v[left], v[center]);			// get ready to sort the three
	s.array_accesses +=2 ;
	s.comparisons ++ ;
	if( v[left] > v[right] ){			
		swap(v[left], v[right]);	
		s.array_accesses +=2 ;
	}
	s.comparisons ++ ;
	if(v[center] > v[right] ){			// look at center and right
		s.array_accesses +=2 ;
		swap(v[center], v[right]);		// swap if necessary
	}
	swap(v[center], v[right]);			// put pivot on right
	s.array_accesses +=2 ;
	return v[right];					// return pivot value

}

#endif 