#ifndef BUBBLESORT
#define BUBBLESORT

#include "../backend/sort_data.hpp"

#include <vector>

sortData bubbleSort(std::vector<int>& vector, char type){
    int swaps = 0;
    bool sorted = false;
    while (! sorted ){
        sorted = true;
        for (int i = 1 ; i < vector.size(); i ++){
            int prev_item = vector[i-1];
            int cur_item = vector[i];
            if (prev_item > cur_item){
                int tempA = prev_item;
                int tempB = cur_item;
                vector[i-1] = tempB;
                vector[i] = tempA;
                swaps ++ ;
                sorted = false;
            }
        }
    }
    return sortData(type, vector.size(), swaps);
}
#endif