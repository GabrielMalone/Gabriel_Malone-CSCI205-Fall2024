#ifndef QSORT_INSERTION
#define QSORT_INSERTION

#include "insertionSort.hpp"
#include "helper_methods/validate_sort.hpp"
#include "helper_methods/qsort_partition.hpp"

using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// QUICK SORT MEDIAN  
//-------------------------------------------------------------------------------------------------------
void quicksort_insertion(vector<int> &avector, int first, int last , bool print, sortData& sData, bool median){
    //---------------------------------------------------------------------------------------------------
	int splitpoint = 0;	                                                    // partition splitpoint index
    //---------------------------------------------------------------------------------------------------
    // INSERTION SORT WHEN VECTOR REACHES SMALL SIZE
    //---------------------------------------------------------------------------------------------------  
    if (last - first <= 4){
        insertionSort(avector, first, last+1, print, sData);  
        return;      
    }                                    
    //---------------------------------------------------------------------------------------------------
    if (first<last) {
        sData.comparisons ++ ;						   // if there is more than one element in the vector
        splitpoint = partition(avector, first, last, print, sData, median, false, false);           
        quicksort_insertion(avector, first, splitpoint - 1, print, sData, median);		    // lower half
        quicksort_insertion(avector, splitpoint + 1, last, print, sData, median);		    // upper half 
    }
    //----------------------------------------------------------------------------------------------------
	else if (print){                                            
         printTowers(avector,100);// graphical output
    }
    //----------------------------------------------------------------------------------------------------
}

#endif