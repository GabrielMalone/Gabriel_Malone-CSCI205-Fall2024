#ifndef QSORT_NTHER
#define QSORT_NTHER

#include "insertionSort.hpp"
#include "helper_methods/validate_sort.hpp"
#include "helper_methods/qsort_partition.hpp"


using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// QUICK SORT TUKEYs 
//-------------------------------------------------------------------------------------------------------
void quicksort_tukeys(vector<int> &avector, int first, int last , bool print, sortData& sData){
	int splitpoint = 0;	                                                 // partition splitpoint index
    //----------------------------------------------------------------------------------------------------
    // if (last - first <= 15){
    //     insertionSort(avector, first, last+1, print, sData);  
    //     return;      
    // }   
    if (first < last) {		                            // if there is more than one element in the vector
        sData.comparisons ++ ;
		splitpoint = partition(avector, first, last, print, sData, false, true, false);	      // partition 
		quicksort_tukeys(avector, first, splitpoint - 1, print, sData);		                 // lower half
		quicksort_tukeys(avector, splitpoint + 1, last, print, sData);		                 // upper half
        sData.call_stack_depth ++ ;  
    //----------------------------------------------------------------------------------------------------
	} else {
        sData.call_stack_depth ++ ;
        if (print){                                                                    // graphical output
            printTowers(avector,100);
        }
    }
    //----------------------------------------------------------------------------------------------------
}

#endif