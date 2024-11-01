#ifndef QSORT_DUAL_PIVOT
#define QSORT_DUAL_PIVOT

#include "insertionSort.hpp"
#include "helper_methods/validate_sort.hpp"
#include "helper_methods/dual_pivot_partition.hpp"
#include "helper_methods/pivots.hpp"

using namespace std;
       
//-------------------------------------------------------------------------------------------------------
// QUICK SORT DUAL PIVOT 
//-------------------------------------------------------------------------------------------------------
void quicksort_dual_pivot(vector<int> &avector, int first, int last , bool print, sortData& sData){
    //  if (last - first <= 15){
    //     insertionSort(avector, first, last+1, print, sData);  
    //     return;      
    // }   
    //---------------------------------------------------------------------------------------------------  
    if (first<last) {       
    //---------------------------------------------------------------------------------------------------
    pivots p = dual_partition(avector, first, last, print, sData);           
    int pivotL = p.pivotL;
    int pivotR = p.pivotR;
    quicksort_dual_pivot(avector, first, pivotL - 1, print, sData);		        // lower third
    quicksort_dual_pivot(avector, pivotL + 1, pivotR - 1, print, sData);        // middle third
    quicksort_dual_pivot(avector, pivotR + 1, last, print, sData);		        // upper third
    sData.call_stack_depth ++ ;     
    }
    //----------------------------------------------------------------------------------------------------
	if (print){                                       
         printTowers(avector,100);// graphical output
    }
    //----------------------------------------------------------------------------------------------------
}

#endif