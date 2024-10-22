#ifndef COUNT_CUSTOM_TEST
#define COUNT_CUSTOM_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/counting_sort.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"
#include "../sorting_methods/helper_methods/hibbard_sequence.hpp"
#include "../sorting_methods/helper_methods/knuth_sequence.hpp"
#include "../sorting_methods/helper_methods/sedgwick_sequence.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT CUSTOM GAP DATA
//------------------------------------------------------------------------------------
void runCountCustomTests(vector<int>& list,int trial,int vect_size,char array_type,
                        bool printArrays, ClosedHashTable<sortData>&countSortData){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW << "Counting Sort: " << Colors::RESET 
             << endl;
        if (printArrays){print_vector(list);}                      // see if it worked                                   
        sortData sd = countingsort(list, array_type, printArrays);         // get data 
        countSortData.put(to_string(trial), sd);          // place data to track sorts 
        if (printArrays){print_vector(list);}                      // see if it worked  
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(countSortData, "Counting_Sort_" + s);   // save data
    //--------------------------------------------------------------------------------
}
#endif 