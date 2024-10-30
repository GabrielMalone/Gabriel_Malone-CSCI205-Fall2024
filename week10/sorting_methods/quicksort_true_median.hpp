#ifndef TRUEMEDIAN
#define TRUEMEDIAN

#include "insertionSort.hpp"
#include "helper_methods/validate_sort.hpp"
#include "helper_methods/qsort_partition.hpp"


using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// QUICK SORT TUKEYs 
//-------------------------------------------------------------------------------------------------------
void quicksort_true_median(vector<int> &avector, int first, int last , bool print, sortData& sData){
	int splitpoint = 0;	                                                 // partition splitpoint index
    //----------------------------------------------------------------------------------------------------
    if (first < last) {		                            // if there is more than one element in the vector
        sData.comparisons ++ ;
		splitpoint = partition(avector, first, last, print, sData, false, false, true);       // partition 
		quicksort_true_median(avector, first, splitpoint - 1, print, sData);		         // lower half
		quicksort_true_median(avector, splitpoint + 1, last, print, sData);		             // upper half
    //----------------------------------------------------------------------------------------------------
	} else {
        if (print){                                                                    // graphical output
            printTowers(avector,100);
        }
    }
    //----------------------------------------------------------------------------------------------------
}

#endif