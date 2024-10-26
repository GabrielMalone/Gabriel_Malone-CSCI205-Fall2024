#ifndef SHELL_SED_TEST
#define SHELL_SED_TEST

#include <vector>
#include "../backend/colors.hpp"
#include "../backend/sort_data.hpp"
#include "../backend/print_vector.hpp"
#include "../sorting_methods/shellSortCustomGap.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../sorting_methods/helper_methods/validate_sort.hpp"
#include "../backend/saveSearchData.hpp"
#include "../sorting_methods/helper_methods/hibbard_sequence.hpp"
#include "../sorting_methods/helper_methods/knuth_sequence.hpp"
#include "../sorting_methods/helper_methods/sedgwick_sequence.hpp"

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT CUSTOM GAP DATA
//------------------------------------------------------------------------------------
void runShellSedgwickTests(vector<int>& list,int trial,int vect_size,char array_type, 
                         bool printArrays, 
                         ClosedHashTable<sortData>&shellCustomSortData){
    string s{array_type};                                        // for file name info
    //vector<int>gaps = hibbard(vect_size);
    vector<int>gaps = sedgwick(vect_size);
    //vector<int>gaps = knuth(vect_size);
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW << "Shell Sort Sedgwick Gap: " << Colors::RESET 
             << endl;
        if (printArrays){print_vector(list);}                      // see if it worked                                   
        sortData sd = shellSortCustomGaps(list,gaps,array_type, printArrays);//   data 
        shellCustomSortData.put(to_string(trial), sd);    // place data to track sorts 
        if (printArrays){print_vector(list);}                      // see if it worked  
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(shellCustomSortData, "shell_sort_sedgwick_Gap_" + s);   // save data
    //--------------------------------------------------------------------------------
}
#endif 