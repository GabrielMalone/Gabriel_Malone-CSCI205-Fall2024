#ifndef COMB_TEST
#define COMB_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/combSort.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE COMB SORT DATA
//------------------------------------------------------------------------------------
void runCombTests(vector<int>& list , int trial, int vect_size, char array_type, 
                   bool printArrays, ClosedHashTable<sortData>& combSortData){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        if (printArrays){print_vector(list);}                      // see if it worked 
        cout << endl << Colors::YELLOW <<"Comb Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = combSort(list, array_type, printArrays);             // get data
        combSortData.put(to_string(trial), sd); // place that data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(combSortData, "comb_sort_" + s);                      // save data
    //--------------------------------------------------------------------------------
}

#endif