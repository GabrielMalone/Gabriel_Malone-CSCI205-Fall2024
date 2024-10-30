#ifndef MERGE_SORT_TEST
#define MERGE_SORT_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/merge_Sort.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// MERGE SORT
//------------------------------------------------------------------------------------
void runMergeSortTests(std::vector<int>& list , int trial, int vect_size, 
                           char array_type, bool printArrays, 
                           ClosedHashTable<sortData>&insertSortData){
    //--------------------------------------------------------------------------------
    string s{array_type};                                        // for file name info
    sortData sData;
    sData.order_type = array_type;
    sData.array_size = list.size();
    cout << endl << Colors::YELLOW <<"Merge Sort: " << Colors::RESET << endl;
    if (printArrays) print_vector(list);                           // see if it worked 
    mergeSort(list, sData, printArrays); 
    insertSortData.put(to_string(trial), sData);     // place data to track every sort 
    if (printArrays) print_vector(list);                           // see if it worked 
    sorted(list, true);                                         // confirm sort worked
    sData.displaySwapData();          // can show the output of a sort on the terminal
    sData.displayCompareData();
    sData.displayDepthData();
    //--------------------------------------------------------------------------------
    saveSortingData(insertSortData, "Merge_Sort_" + s);       // save data
    //--------------------------------------------------------------------------------
}

#endif