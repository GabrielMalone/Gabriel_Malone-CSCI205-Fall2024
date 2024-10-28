#ifndef MENU_GRAPHICAL_DISPLAY
#define MENU_GRAPHICAL_DISPLAY

#include "../backend/ClosedHashTable.hpp"
#include "../backend/print_graph.hpp"
#include "../backend/show_graphs.hpp"
#include "../backend/sort_data.hpp"
#include "../sorting_methods/helper_methods/generate_vectors.hpp"
#include "../tests/insert_test.hpp"
#include "../tests/quicksort_median_test.hpp"
#include "../tests/quicksort_lazy_test.hpp"
#include "../tests/quicksort_insertion_test.hpp"

bool print = true;

void graphical_sorting_data(char type, int selection){
     //---------------------------------------------------------------------------------------------
    ClosedHashTable<sortData>quickSortLazyData;   // map to store data related to sorting
    ClosedHashTable<sortData>quickSortMedianData; // map to store data related to sorting
    ClosedHashTable<sortData>quickSortInsertionData; // map to store data related to sorting
    ClosedHashTable<sortData>insertSortData;  
     //---------------------------------------------------------------------------------------------
    int vec_size = 100;
    int range = 100;       
    vector<int>list(vec_size);                             // generate random list
    generate_vector(vec_size, type, list, range);              
    //----------------------------------------------------------------------------------------------
    switch (selection)
    {
    case 1: runQuickSortLazyTests(      list, 1, vec_size, type, print, quickSortLazyData);  
        break; 
    case 2: runQuickSortMedianTests(    list, 1, vec_size, type, print, quickSortMedianData); 
        break;
    case 3: runQuickSortInsertionTests( list, 1, vec_size, type, print, quickSortInsertionData); 
        break;
    case 4: //runShellHibbardTests(   list, 1, vec_size, type, print, shellSortDataHibbard);
        break;
    case 5: //runShellKnuthTests(     list, 1, vec_size, type, print, shellSortDataKnuth);
        break;
    case 6: //runShellSedgwickTests(  list, 1, vec_size, type, print, shellSortDataSedgwick);
        break;
    case 7: //runCombTests(           list, 1, vec_size, type, print, combSortData);  
        break;
    case 8: //runCountCustomTests(    list, 1, vec_size, type, print, countSortData);
        break;
    case 9: //runRadixBasicTests(     list, 1, vec_size, type, print, radixSortData);
        break;
    }
    //---------------------------------------------------------------------------------------------
}

#endif