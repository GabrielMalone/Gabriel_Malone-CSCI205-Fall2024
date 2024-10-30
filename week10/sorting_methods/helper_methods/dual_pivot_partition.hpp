#ifndef QSORTPARTITION_DUALP
#define QSORTPARTITION_DUALP

#include "../../backend/sort_data.hpp"
#include "../../backend/print_graph.hpp"
#include "median_of_three.hpp"
#include "../../backend/swap.hpp"
#include "pivots.hpp"
#include "../../backend/swap.hpp"

using namespace std;

//-------------------------------------------------------------------------------------------------------
// Partition helper method - for loop algo - this one is slower but easier to understand
//-------------------------------------------------------------------------------------------------------
pivots dual_partition(vector<int>& avector, int low, int high, bool print, sortData& sData){
    pivots p;
    if (avector[low] > avector[high]){
        swap(avector, low, high);
    }
    //---------------------------------------------------------------------------------------------------
    // PARTITION ALGO from https://www.youtube.com/watch?v=XYVbjQXkmiI
    //---------------------------------------------------------------------------------------------------
    int leftPivotIndex = low + 1;
    int rightPivotIndex = high - 1;	
    int iterator = low + 1;

    while (iterator <= rightPivotIndex){
        sData.comparisons ++;
        if (avector[iterator] < avector[low]){
            sData.array_accesses += 2;
            if (print){
                printTowers(avector,avector[low]);
                printTowers(avector,avector[iterator]);
            }
            swap(avector, iterator ++, leftPivotIndex ++ );
            sData.comparisons ++;
        } else if (avector[iterator] > avector[high]) {
            if (print){
                printTowers(avector,avector[low]);
                printTowers(avector,avector[iterator]);
              }
            sData.array_accesses += 2;
            swap(avector, iterator, rightPivotIndex -- );
        } else {
            iterator ++ ;
        }
    }
    if (print){
            printTowers(avector,avector[low]);
            printTowers(avector,avector[iterator]);
    }
    swap(avector, low, --leftPivotIndex);
    swap(avector, high, ++rightPivotIndex);
    sData.array_accesses += 4;

    //---------------------------------------------------------------------------------------------------
    p.pivotL = leftPivotIndex;
    p.pivotR = rightPivotIndex;
    return p;
    //---------------------------------------------------------------------------------------------------
}   

#endif


