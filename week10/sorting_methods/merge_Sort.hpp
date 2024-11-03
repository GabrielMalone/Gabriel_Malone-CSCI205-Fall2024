#ifndef MERGE_SORT
#define MERGE_SORT


#include "helper_methods/validate_sort.hpp"
#include "helper_methods/merge.hpp"
#include "../backend/sort_data.hpp"
#include <vector>

using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// MERGE SORT
//-------------------------------------------------------------------------------------------------------
vector<int> mergeSort(vector<int>& avector, sortData& s, bool print) {
	// if ( avector.size() <= 15){
	// 	s.call_stack_depth -- ;
    //     insertionSort(avector, 0, avector.size(), print, s);  
    //     return avector;      
    // } 
	s.call_stack_depth ++ ;
	if (s.call_stack_depth > s.max_depth){
       		s.max_depth = s.call_stack_depth;
    }	
	int size = avector.size();															// get vector size
	if (size>1) {																// base case, range of 1 is sorted
		int mid = size/2;															// calculate mid point
		// split vector at midpoint: auxiliary memory created. These are new vectors
		vector<int> lefthalf(avector.begin(),avector.begin()+mid);
		vector<int> righthalf(avector.begin()+mid,avector.begin()+size);
		// merge sort the halves
		lefthalf  = mergeSort(lefthalf,s,print);				  // recursive call to mergeSort the left half
		righthalf = mergeSort(righthalf,s,print);				 // recursive call to mergeSort the right half
		merge(avector, lefthalf, righthalf,s, print); 	 // merge sorted sub vectors back into original vector
	}
	s.call_stack_depth -- ;
	return avector;
}

#endif