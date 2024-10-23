#ifndef MENU_GRAPHICAL_DISPLAY
#define MENU_GRAPHICAL_DISPLAY

#include "../backend/ClosedHashTable.hpp"
#include "../backend/print_graph.hpp"
#include "../backend/show_graphs.hpp"
#include "../backend/sort_data.hpp"
#include "../sorting_methods/helper_methods/generate_vectors.hpp"
#include "../tests/bubble_sort_test.hpp"
#include "../tests/comb_test.hpp"
#include "../tests/insert_test.hpp"
#include "../tests/shell_sort_basic_test.hpp"
#include "../tests/shell_sort_knuth_test.hpp"
#include "../tests/shell_sort_hibbard_test.hpp"
#include "../tests/shell_sort_sedgwick_test.hpp"
#include "../tests/count_sort_test.hpp"
#include "../tests/radix_sort_test.hpp"

bool print = true;



void graphical_sorting_data(char type, int selection){

    ClosedHashTable<sortData>combSortData;        // map to store data related to sorting
    ClosedHashTable<sortData>shellSortData; 
    ClosedHashTable<sortData>shellSortDataKnuth;   
    ClosedHashTable<sortData>shellSortDataSedgwick;   
    ClosedHashTable<sortData>shellSortDataHibbard;     
    ClosedHashTable<sortData>bubbleSortData; 
    ClosedHashTable<sortData>insertSortData;  
    ClosedHashTable<sortData>countSortData; 
    ClosedHashTable<sortData>radixSortData; 
    
    int vec_size = 100;       
    vector<int>list(vec_size);                             // generate random list
    generate_vector(vec_size, type, list);              
    //----------------------------------------------------------------------------
    switch (selection)
    {
    case 1: runBubbleTests(         list, 1, vec_size, type, print, bubbleSortData);  
        break; 
    case 2: runInsertTests(         list, 1, vec_size, type, print, insertSortData); 
        break;
    case 3: runShellBasicTests(     list, 1, vec_size, type, print, shellSortData); 
        break;
    case 4: runShellHibbardTests(   list, 1, vec_size, type, print, shellSortDataHibbard);
        break;
    case 5: runShellKnuthTests(     list, 1, vec_size, type, print, shellSortDataKnuth);
        break;
    case 6: runShellSedgwickTests(  list, 1, vec_size, type, print, shellSortDataSedgwick);
        break;
    case 7: runCombTests(           list, 1, vec_size, type, print, combSortData);  
        break;
    case 8: runCountCustomTests(    list, 1, vec_size, type, print, countSortData);
        break;
    case 9: runRadixBasicTests(     list, 1, vec_size, type, print, radixSortData);
        break;
    }
}

#endif