#ifndef INSERTIONSORT
#define INSERTIONSORT

#include <vector>
#include "../backend/sort_data.hpp"

sortData insertionSort(std::vector<int>& vector, char type){
    int swaps = 0;
    for (int i = 1 ; i < vector.size() ; i ++){     // iterate through vector starting at index 1
        int temp_value = vector[i];                 // get value at that index
		int j = i - 1; 								// index for previous item
		while (j >= 0 && vector[j] > temp_value){   // while spaces remain to the left and the current item is larger than the temp item, continue loop
			vector[j + 1] = vector[j];  			// shift element to the right 
			j -- ; 								    // shift index to left to keep checking items to the left
			swaps ++ ;								// track swaps
		}	
		vector[j + 1] = temp_value;					// place temp value in its new (or original) sport
    }
    return sortData(type, vector.size(), swaps);
}

#endif 