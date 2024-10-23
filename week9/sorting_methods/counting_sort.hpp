#ifndef COUNTINGSORT
#define COUNTINGSORT

#include <vector>
#include "../backend/sort_data.hpp"

sortData countingsort(std::vector<int>& vector, char type, bool print){
    if (print)
		printTowers(vector);
    //---------------------------------------------------------------------------------
    int range = 0;                                  // get the range
    int array_acccess = 0;
    //---------------------------------------------------------------------------------
    for (size_t i = 0 ; i < vector.size() ; i ++){
        if (vector[i] > range){
            range = vector[i];
            array_acccess ++ ;
        }
    }
    range ++ ;                                      // add one to range
    //---------------------------------------------------------------------------------
    std::vector<int>output((int)vector.size());     // count each element and place the count in the count array
    std::vector<int>count(range, 0);                // set values to zero
    //---------------------------------------------------------------------------------
    for (size_t k = 0 ; k < vector.size() ; k ++ ){    // if a number present at vector index, place that count
        ++ count[vector[k]]; 
        array_acccess ++ ;                          // in the corresponding count index (e.g. '1' in vector will 
    }                                               // be placed at the 1 index of count)
    //---------------------------------------------------------------------------------
    for (int l = 1 ; l < range ; l ++ ){            // cumulaive sum to see how much space each number will take in the sorted array   
        count[l] = count[l] + count[l - 1];         // add prev bucket and current bucket (e.g. index 1 + index 0, index2 + index 1)
        array_acccess ++ ;
    }                 
    //---------------------------------------------------------------------------------
    for (size_t g = 0 ; g < vector.size(); g ++ ){// take the integer present at the current index of the original array
        output[--count[vector[g]]] = vector[g];     // get the integer (the count of that number) from the count vector
        array_acccess ++ ;
    }                                               // decrement that count by 1 to get the final index position for this integer
    //---------------------------------------------------------------------------------                                               
    for (size_t m = 0 ; m < vector.size(); m ++ ){// set the original vector with the sorted values
        vector[m] = output[m];
          if (print)
            printTowers(vector);
        array_acccess ++ ;
    }
    //---------------------------------------------------------------------------------
    if (print)
        printTowers(vector);
    return sortData(type, vector.size(), array_acccess, 0); 
}
#endif 