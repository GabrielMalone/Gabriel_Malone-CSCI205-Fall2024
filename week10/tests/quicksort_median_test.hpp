#ifndef QSORT_MEDIAN_TEST
#define QSORT_MEDIAN_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/quicksort_median.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE QUICKSORT LAZY DATA
//------------------------------------------------------------------------------------
void runQuickSortMedianTests(std::vector<int>& list , int trial, int vect_size, 
                           char array_type, bool printArrays, 
                           ClosedHashTable<sortData>&insertSortData){
    //--------------------------------------------------------------------------------
    string s{array_type};                                        // for file name info
    bool median = true;                                         // median pivot search
    sortData sData;
    sData.order_type = array_type;
    sData.array_size = list.size();
    cout << endl << Colors::YELLOW <<"Quick Sort Median: " << Colors::RESET << endl;
    if (printArrays) print_vector(list);                           // see if it worked 
    quicksort_median(list, 0 , list.size() - 1, printArrays, sData, median); 
    insertSortData.put(to_string(trial), sData);     // place data to track every sort 
    if (printArrays) print_vector(list);                           // see if it worked 
    sorted(list, true);                                         // confirm sort worked
    sData.displaySwapData();          // can show the output of a sort on the terminal
    sData.displayCompareData();
    sData.displayDepthData();
    //--------------------------------------------------------------------------------
    saveSortingData(insertSortData, "Quick_Sort_Median_" + s);            // save data
    //--------------------------------------------------------------------------------
}

#endif