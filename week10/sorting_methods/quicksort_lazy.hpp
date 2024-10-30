#ifndef QSORT_LAZY
#define QSORT_LAZY

#include "helper_methods/qsort_partition.hpp"

using namespace std;

//-------------------------------------------------------------------------------------------------------
// QUICK SORT LAZY                    
//-------------------------------------------------------------------------------------------------------
void quicksort_lazy(vector<int> &avector, int first, int last , bool print, sortData& sData, bool median){
    sData.call_stack_depth ++ ;
	int splitpoint = 0;	                                                     // partition splitpoint index
    //----------------------------------------------------------------------------------------------------
	if (first<last) {	                                // if there is more than one element in the vector
        sData.comparisons ++ ;
		splitpoint = partition(avector, first, last, print, sData, median, false, false);     // partition
		quicksort_lazy(avector, first, splitpoint - 1, print, sData, median);		         // lower half
		quicksort_lazy(avector, splitpoint + 1, last, print, sData, median);		         // upper half
    //----------------------------------------------------------------------------------------------------
	} else {
        if (print){                                                                    // graphical output
            printTowers(avector,100);
        }
    }
    //----------------------------------------------------------------------------------------------------
}

#endif