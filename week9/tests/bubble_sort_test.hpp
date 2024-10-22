#ifndef BUBBLE_TEST
#define BUBBLE_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/bubbleSort.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE BUBBLE SORT DATA
//------------------------------------------------------------------------------------
void runBubbleTests(vector<int>& list , int trial, int vect_size, char array_type, 
                    bool printArrays, ClosedHashTable<sortData>&bubbleSortData){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Bubble Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = bubbleSort(list, array_type);           // get data for each run 
        bubbleSortData.put(to_string(trial), sd);    // place data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(bubbleSortData, "bubble_sort_" + s);                  // save data
    //--------------------------------------------------------------------------------
}

#endif