#ifndef BUBBLESORT
#define BUBBLESORT

#include "swap.hpp"
#include "../huffman.hpp"

#include <vector>
template <typename T>
void bubbleSort(std::vector<T> & avector){
    //---------------------------------------------------------------------------------
    bool sorted = false;
    //---------------------------------------------------------------------------------
    for (size_t pass = avector.size()-1; pass > 0; pass -= 1){
        sorted = true;
		for (size_t i = 0; i < pass; i++){
			if (avector[i].letter > avector[i+1].letter){
                swap(avector, i, i + 1);
                sorted = false;    
            }		
        }
        if (sorted){
            break;
        }
    }
    //---------------------------------------------------------------------------------
}
#endif