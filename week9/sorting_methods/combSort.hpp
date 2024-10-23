#ifndef COMBSORT
#define COMBSORT

#include "../backend/sort_data.hpp"
#include <vector>

//------------------------------------------------------------------------------------
// COMB SORT METHOD (Bubble Sort with gaps)
//------------------------------------------------------------------------------------
sortData combSort(std::vector<int>&list, char type, bool print){
    //--------------------------------------------------------------------------------
    // method vars
    //--------------------------------------------------------------------------------
    size_t gap = list.size()-1;                                    // initial gap size
    double shrink = 1.3;                                              // shrink factor
    bool sorted = false;                                              // search switch
    int i = 0;
    unsigned long long array_accesses = 0;
    unsigned long long comparisons = 0;
    //--------------------------------------------------------------------------------
    // Outter loop to gap check and terminate when at 1
    //--------------------------------------------------------------------------------
    while (! sorted)                                          // continue until sorted
    {   
        if (gap > 1)                  // not done sorting until final pass of gap of 1
            sorted = false;
        if (gap < 1){                                                    // final pass
            sorted = true;
            gap = 1;
        }
        //----------------------------------------------------------------------------
        // Inner loop to do actual position check and swapping
        //----------------------------------------------------------------------------
        i = 0;
        while ((i + (gap)) < list.size())  //               index position + gap width                      
        {   
            comparisons ++ ;
            if (list[i] > list[i + gap])                 // if larger element in front
            {   
                if (print)                                         // graphical output
                    printTowers(list, list[i]);
                int tempA = list[i];                                           // swap
                int tempB = list[i + gap];                           // use temp items
                list[i] = tempB;
                list[i + gap] = tempA;
                array_accesses += 2 ;                                   // track swaps 
                sorted = false;
            }
            i ++ ;
        }   
        gap = gap / shrink;                                // reduce gap for next pass      
    }
    if (print)                                         // graphical output
            printTowers(list, list[100]);
    //---------------------------------------------------------------------------------
    return sortData(type, list.size(), array_accesses, comparisons); 
    //---------------------------------------------------------------------------------
}

#endif