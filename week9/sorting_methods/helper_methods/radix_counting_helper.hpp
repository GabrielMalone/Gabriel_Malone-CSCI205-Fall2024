#ifndef COUNTINGSORT_HELPER
#define COUNTINGSORT_HELPER

#include <vector>


int countingSort_helper(std::vector<int>& vector, int div, bool print){
    //---------------------------------------------------------------------------------
    int range = 10;                                             // decimal system so 10
    int array_acccess = 0;
    //---------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------
    std::vector<int>output((int)vector.size());                 // count each element and place the count in the count array
    std::vector<int>count(range, 0);                            // set values to zero
    //---------------------------------------------------------------------------------
    for (int k = 0 ; k < (int)vector.size() ; k ++ ){           // if a number present at vector index, place that count
        count[(vector[k]/div)%10] ++; 
        array_acccess ++ ;                                      // in the corresponding count index (e.g. '1' in vector will 
    }                                                           // be placed at the 1 index of count)
    //---------------------------------------------------------------------------------
    for (int l = 1 ; l < range ; l ++ ){                        // cumulaive sum to see how much space each number will take in the sorted array   
        count[l] += count[l - 1];                               // add prev bucket and current bucket (e.g. index 1 + index 0, index2 + index 1)
        array_acccess ++ ;
    }                 
    //---------------------------------------------------------------------------------
    for (int g = (int)vector.size()-1; g >= 0 ; g -- ){         // reverse order this time  to maintain FIFO order ? take the integer present at the current index of the original array
        output[count[ (vector[g]/div)%10 ] -1 ] = vector[g];    // get the integer (the count of that number) from the count vector
        count[ (vector[g]/div)%10 ]--;
        array_acccess ++ ;
    }
    //----------------------------------                        // decrement that count by 1 to get the final index position for this integer
    for (int m = 0 ; m < (int)vector.size(); m ++ ){            // set the original vector with the sorted values
        if (print)
            printTowers(vector, vector[m]);
        vector[m] = output[m];
        array_acccess ++ ;
    }
    //---------------------------------------------------------------------------------
    return array_acccess;
}
#endif 