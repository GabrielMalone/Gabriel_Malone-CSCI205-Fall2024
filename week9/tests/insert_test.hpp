#ifndef INSERT_TEST
#define INSERT_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/insertionSort.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE INSERTION SORT DATA
//------------------------------------------------------------------------------------
void runInsertTests(std::vector<int>& list , int trial, int vect_size, char array_type, 
                    bool printArrays, ClosedHashTable<sortData>&insertSortData){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Insertion Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = insertionSort(list, array_type);        // get data for each run 
        insertSortData.put(to_string(trial), sd);    // place data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(insertSortData, "Insertion_sort_" + s);               // save data
    //--------------------------------------------------------------------------------
}

#endif