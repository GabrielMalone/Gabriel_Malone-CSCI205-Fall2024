#ifndef BUBBLESORT
#define BUBBLESORT

#include "../backend/sort_data.hpp"
#include "../backend/swap.hpp"

#include <vector>

sortData bubbleSort(std::vector<int>& avector, char type){
    bool sorted = false;
    unsigned long long array_accesses = 0;
    unsigned long long comparisons = 0;
    for (int pass = avector.size()-1; pass > 0; pass -= 1){
        sorted = true;
		for (int i = 0; i < pass; i++){
            comparisons ++ ;
			if (avector[i] > avector[i+1]){
                swap(avector, i, i+1);
                array_accesses += 2;
                sorted = false;
            }		
        }
        if (sorted){
            break;
        }
    }
    return sortData(type, avector.size(), array_accesses, comparisons);
}
#endif

