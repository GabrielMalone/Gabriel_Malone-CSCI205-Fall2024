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
#include "../tests/quickort_tukeys_test.hpp"
#include "../tests/quicksort_dual_pivot_test.hpp"
#include "../tests/mergeSortTests.hpp"

bool print = true;

void graphical_sorting_data(char type, int selection){
     //---------------------------------------------------------------------------------------------
    ClosedHashTable<sortData>quickSortLazyData;                 // map to store data related to sorting
    ClosedHashTable<sortData>quickSortMedianData;               // map to store data related to sorting
    ClosedHashTable<sortData>quickSortInsertionData;            // map to store data related to sorting
    ClosedHashTable<sortData>quickSortNtherData;                // map to store data related to sorting
    ClosedHashTable<sortData>quickSortTrueMedianData;           // map to store data related to sorting
    ClosedHashTable<sortData>quickSortDualPivotData;            // map to store data related to sorting
    ClosedHashTable<sortData>mergeSortData;                     // map to store data related to sorting
     //---------------------------------------------------------------------------------------------
    int vec_size = 50;
    int range = 50;
    vector<int>list(vec_size);                                  // generate random list
    generate_vector(vec_size, type, list, range);              
    //----------------------------------------------------------------------------------------------
    switch (selection)
    {
    case 1: runQuickSortLazyTests(       list, 1, vec_size, type, print, quickSortLazyData);  
        break; 
    case 2: runQuickSortMedianTests(     list, 1, vec_size, type, print, quickSortMedianData); 
        break;
    case 3: runQuickSortInsertionTests(  list, 1, vec_size, type, print, quickSortInsertionData); 
        break;
    case 4: runQuickSortTukeysTests(     list, 1, vec_size, type, print, quickSortNtherData);
        break;
    case 5: runQuickSortDualPivotTests(  list, 1, vec_size, type, print, quickSortDualPivotData);
        break;
    case 6: runMergeSortTests(           list, 1, vec_size, type, print, mergeSortData);  
        break;
    }
    //---------------------------------------------------------------------------------------------
}

#endif