#ifndef COMBSORT
#define COMBSORT

#include "../backend/sort_data.hpp"
#include <vector>

//------------------------------------------------------------------------------------
// COMB SORT METHOD (Bubble Sort with gaps)
//------------------------------------------------------------------------------------
sortData combSort(std::vector<int>&list, char type){
    //--------------------------------------------------------------------------------
    // method vars
    //--------------------------------------------------------------------------------
    int gap = list.size();                                         // initial gap size
    double shrink = 1.3;                                              // shrink factor
    bool sorted = false;                                              // search switch
    int i = 0;
    int swaps = 0;
    //--------------------------------------------------------------------------------
    // Outter loop to gap check and terminate when at 1
    //--------------------------------------------------------------------------------
    while (! sorted)                                          // continue until sorted
    {   
        if (gap > 1)                  // not done sorting until final pass of gap of 1
        {
            sorted = false;
        }
        if (gap < 1){                                                   // final pass
            sorted = true;
        }
        //----------------------------------------------------------------------------
        // Inner loop to do actual position check and swapping
        //----------------------------------------------------------------------------
        i = 0;
        while (i + gap < list.size())  //                   index position + gap width                      
        {
            if (list[i] > list[i + gap])                 // if larger element in front
            {   
                int tempA = list[i];                                           // swap
                int tempB = list[i + gap];                           // use temp items
                list[i] = tempB;
                list[i + gap] = tempA;
                sorted = false; 
                swaps ++ ;                                              // track swaps 
            }
            i ++ ;
        }   
        gap = floor(gap / shrink);                         // reduce gap for next pass          
    }
    return sortData(type, list.size(), swaps); 
}

#endif