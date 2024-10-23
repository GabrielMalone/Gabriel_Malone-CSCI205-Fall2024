#ifndef RADIXSORT
#define RADIXSORT

#include <vector>
#include <queue>
#include "../backend/sort_data.hpp"
#include "helper_methods/radix_counting_helper.hpp"

sortData radixSort(std::vector<int>& vector, char type, bool print){
    //---------------------------------------------------------------------------
    int array_acccess = 0;                                        // for graphing
    int range = 0;                                               // get the range
    //---------------------------------------------------------------------------
    if (print)
        printTowers(vector);
    //if (! sorted (vector)){             // if sorted to start, don't do anything
        for (size_t i = 0 ; i < vector.size() ; i ++){
            if (vector[i] > range){
                range = vector[i];
                array_acccess ++ ;
            }
        }
        range ++ ;
        //-----------------------------------------------------------------------
        for (int div = 1 ; range/div > 0 ; div*=10){ // count sort for each digit
            array_acccess += countingSort_helper(vector, div, print);
        }
    //}
    if (print)                                                // graphical output
        printTowers(vector);
    return sortData(type, vector.size(), array_acccess, 0);
}

#endif
