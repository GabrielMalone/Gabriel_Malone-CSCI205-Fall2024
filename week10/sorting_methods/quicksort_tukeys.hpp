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
    sData.call_stack_depth ++ ; 
    if (sData.call_stack_depth > sData.max_depth){
            sData.max_depth = sData.call_stack_depth;
    }	
    //----------------------------------------------------------------------------------------------------
    // if (last - first <= 15){
    //     sData.call_stack_depth -- ;  
    //     insertionSort(avector, first, last+1, print, sData);  
    //     return;      
    // }   
    if (first < last) {	
        int splitpoint = 0;	                                                 // partition splitpoint index
                                   // if there is more than one element in the vector
		splitpoint = partition(avector, first, last, print, sData, false, true, false);	     // partition 
		quicksort_tukeys(avector, first, splitpoint - 1, print, sData);		                 // lower half
        sData.call_stack_depth -- ;
		quicksort_tukeys(avector, splitpoint + 1, last, print, sData);		                 // upper half
        sData.call_stack_depth -- ;
    //----------------------------------------------------------------------------------------------------
	} else {
        if (print){                                                                    // graphical output
            printTowers(avector,100);
        }
    }
    //----------------------------------------------------------------------------------------------------
}

#endif