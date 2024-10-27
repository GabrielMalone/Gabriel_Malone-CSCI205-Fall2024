#ifndef QSORTPARTITION
#define QSORTPARTITION

#include "../../backend/sort_data.hpp"
#include "../../backend/print_graph.hpp"
#include "median_of_three.hpp"

using namespace std;

//-------------------------------------------------------------------------------------------------------
// Partition helper method
//-------------------------------------------------------------------------------------------------------
int partition(vector<int>& avector, int first, int last, bool print, sortData& sData, bool median){
    //---------------------------------------------------------------------------------------------------
	int pivotValue = avector[last];      // grab the pivot (lazy approach: first, last or middle element)
    if (median)                                           // if median mode enabled, replace pivot value
	    pivotValue = MO3(avector, first, last);
	int rightmark  = last - 1;		                                           // establish right pointer
	int leftmark   = first;			                                            // establish left pointer
	bool done = false;				                                        // flag to indicate when done
    //---------------------------------------------------------------------------------------------------
	while (!done){					                                                    // while not done
        //-----------------------------------------------------------------------------------------------
		while (leftmark <= rightmark && avector[leftmark] <= pivotValue)  // points not crossed and l < r 
			leftmark++;            // increment left pointer until a value larger than the pivot is found
            sData.comparisons ++ ;
        //-----------------------------------------------------------------------------------------------
		while (rightmark >= leftmark && avector[rightmark] >= pivotValue){  // points not crossed & r > l
			rightmark--;         // decrement right pointer until a value smaller than the pivot is found
            sData.comparisons ++ ;                                                         // record data
        }                                     
        //-----------------------------------------------------------------------------------------------       
		if (rightmark < leftmark){
            done = true;				                      // if pointers cross, the partition is done
            sData.comparisons ++ ;                                                         // record data
        } 
        //-----------------------------------------------------------------------------------------------
		else{
            swap(avector[rightmark], avector[leftmark]);	  // pointers haven't crossed, perform a swap
            sData.array_accesses += 2;                                                     // record data
            if (print){                                                               // graphical output 
                printTowers(avector,avector[leftmark]);
                printTowers(avector,avector[rightmark]);
            }                                             
        } 
	}
    //---------------------------------------------------------------------------------------------------
    // When done...
    //---------------------------------------------------------------------------------------------------
	swap(avector[leftmark], avector[last]);	                             // place the pivot at splitpoint
    sData.array_accesses += 2;
    if (print){
        printTowers(avector,avector[leftmark]);
        printTowers(avector,avector[last]);
    }
    //---------------------------------------------------------------------------------------------------
	return leftmark;						                                        // return split point
    //---------------------------------------------------------------------------------------------------
}   

#endif