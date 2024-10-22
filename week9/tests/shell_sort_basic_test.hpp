#ifndef SHELL_BASIC_TEST
#define SHELL_BASIC_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/shellSortBasic.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT BASIC DATA
//------------------------------------------------------------------------------------
void runShellBasicTests(vector<int>& list,int trial,int vect_size,char array_type, 
                        bool printArrays, ClosedHashTable<sortData>&shellSortData){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Shell Sort Default: " << Colors::RESET 
             << endl;
        if (printArrays){print_vector(list);}                      // see if it worked                                   
        sortData sd = shellSortBasic(list, array_type);       // get data for each run 
        shellSortData.put(to_string(trial), sd);// place that data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked  
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(shellSortData, "shell_sort_" + s);                   // save data
    //--------------------------------------------------------------------------------
}


#endif