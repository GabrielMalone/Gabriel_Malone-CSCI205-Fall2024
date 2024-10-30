#ifndef QSORTPARTITION
#define QSORTPARTITION

#include "../../backend/sort_data.hpp"
#include "../../backend/print_graph.hpp"
#include "median_of_three.hpp"
#include "actual_median.hpp"
#include "tukey.hpp"
#include <random>
#include "../../backend/swap.hpp"

using namespace std;

//-------------------------------------------------------------------------------------------------------
// Partition helper method - for loop algo - this one is slower but easier to understand
//-------------------------------------------------------------------------------------------------------
int partition(vector<int>& avector, int low, int high, 
                    bool print, sortData& sData, bool median, bool tukey, bool true_median){
    int pivotValue = 0;
    //---------------------------------------------------------------------------------------------------
    // MEDIAN OF 3 INDEX
    //---------------------------------------------------------------------------------------------------
    if (median) {                                          // if median mode enabled, replace pivot value
	    pivotValue = MO3(avector, low, high);
    }
    //---------------------------------------------------------------------------------------------------
    // TUKEY'S MEDIAN OF 9
    //---------------------------------------------------------------------------------------------------
    else if (tukey) {
	    int pivotIndex = tukeys(avector, low, high);
	    swap(avector[pivotIndex], avector[high]); // Place pivot at the end
        pivotValue = avector[high];
    }
    //---------------------------------------------------------------------------------------------------
    // TRUE MEDIAN
    //---------------------------------------------------------------------------------------------------
    else if (true_median){
        int pivotindex = realMedian(avector, low, high);
        swap(avector[pivotindex], avector[high]);    // always place the pivot value at back for the algo
        pivotValue = avector[high];
    //---------------------------------------------------------------------------------------------------
    } else {
    //---------------------------------------------------------------------------------------------------
    // LAZY APPROACH WITH RANDOM INDEX PICKED
    //---------------------------------------------------------------------------------------------------
        random_device rd;                           // random number generator for lazy random assignment
        mt19937 gen(rd());
        uniform_int_distribution<> dist(low,  high);          // range from 0 to 100 for the rnadom value
        int rand_index = dist(gen);
        pivotValue = avector[rand_index];                                 // grab the pivot lazy approach
        swap(avector[rand_index], avector[high]);   // always place the pivot value at back for lazy algo
    }
    //---------------------------------------------------------------------------------------------------
    // PARTITION ALGO
    //---------------------------------------------------------------------------------------------------
    int i = low - 1; 						    
	for (int j = low; j <= high - 1; j++){
        sData.comparisons ++ ;
		if (avector[j] < pivotValue){			          // If current element is smaller than the pivot
			i++; 								                    // increment index of smaller element
			swap(avector[j], avector[i]);		    // swap items at i and j (j being smaller than pivot)
            sData.array_accesses += 2;
            if (print){
                printTowers(avector,avector[i]);
                printTowers(avector,avector[j]);
            }
		}
	}
    //---------------------------------------------------------------------------------------------------
    i ++ ;
	swap(avector[i], avector[high]);	     // after partitioning, put pivot in it's place at splitpoint
	return i;								                                     // return the splitpoint
    //---------------------------------------------------------------------------------------------------
}   

#endif


