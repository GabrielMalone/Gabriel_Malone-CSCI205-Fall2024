#ifndef SHELLSORT
#define SHELLSORT

#include "insertionSort.hpp"
#include "../backend/print_vector.hpp"
#include "../backend/sort_data.hpp"


sortData shellSort(std::vector<int>& vector, char type){
    int swaps = 0;
    int gap = vector.size()-1;
	for(int i = 0; i < vector.size(); i++){             // iterate through the gap sequence vector.
        if (gap <= 1){
            return insertionSort(vector, type);
        }
        for (int i  = 0 ; i + gap < vector.size() ; i ++ ){
            if (vector[i] > vector[gap]){
                int temp_front = vector[i];
                int temp_back = vector[gap]; 
                vector[i] = temp_back;
                vector[gap] = temp_front; 
            }
        }
        gap  = gap / 2;
	}
    return sortData(type, vector.size(), swaps); 
}

#endif