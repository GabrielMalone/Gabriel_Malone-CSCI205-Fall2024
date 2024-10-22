#ifndef RADIXSORT
#define RADIXSORT

#include <vector>
#include <queue>
#include "../backend/sort_data.hpp"
#include "helper_methods/radix_counting_helper.hpp"

sortData radixSort(std::vector<int>& vector, char type){

    //---------------------------------------------------------------------------
    int array_acccess = 0;                        // for graphing
    int range = 0;                                // get the range
    //---------------------------------------------------------------------------
    for (int i = 0 ; i < vector.size() ; i ++){
        if (vector[i] > range){
            range = vector[i];
            array_acccess ++ ;
        }
    }
    range ++ ;
    //---------------------------------------------------------------------------
    // count sort for each digit
    for (int div = 1 ; range/div > 0 ; div*=10){
       array_acccess += countingSort_helper(vector, div);
    }
    return sortData(type, vector.size(), array_acccess, 0);
}

#endif
