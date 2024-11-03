#ifndef QSORT_INSERTION
#define QSORT_INSERTION

#include "insertionSort.hpp"
#include "helper_methods/validate_sort.hpp"
#include "helper_methods/qsort_partition.hpp"

using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// QUICK SORT INSERTION  
//-------------------------------------------------------------------------------------------------------
void quicksort_insertion(vector<int> &avector, int first, int last , bool print, sortData& sData, bool median){
    //---------------------------------------------------------------------------------------------------
	int splitpoint = 0;	                                                    // partition splitpoint index
    sData.call_stack_depth ++ ;
    if (sData.call_stack_depth > sData.max_depth){
            sData.max_depth = sData.call_stack_depth;
    }
    //---------------------------------------------------------------------------------------------------
    // INSERTION SORT WHEN VECTOR REACHES SMALL SIZE
    //---------------------------------------------------------------------------------------------------  
    if (last - first <= 15){
        sData.call_stack_depth -- ;  
        insertionSort(avector, first, last+1, print, sData);  
        return;      
    }                                    
    //---------------------------------------------------------------------------------------------------
    if (first<last) {
        splitpoint = partition(avector, first, last, print, sData, median, false, false);           
        quicksort_insertion(avector, first, splitpoint - 1, print, sData, median);		    // lower half
        sData.call_stack_depth -- ;
        quicksort_insertion(avector, splitpoint + 1, last, print, sData, median);		    // upper half
        sData.call_stack_depth -- ; 
    }
    //----------------------------------------------------------------------------------------------------
	else if (print){                                       
        printTowers(avector,100);// graphical output
    }
    //----------------------------------------------------------------------------------------------------
}

#endif