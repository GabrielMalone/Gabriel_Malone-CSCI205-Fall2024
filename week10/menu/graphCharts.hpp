#ifndef MENU_GRAPH_CHARTS
#define MENU_GRAPH_CHARTS

#include "../backend/ClosedHashTable.hpp"
#include "../backend/print_graph.hpp"
#include "../backend/show_graphs.hpp"
#include "../backend/sort_data.hpp"
#include "../sorting_methods/helper_methods/generate_vectors.hpp"
#include "../tests/insert_test.hpp"
#include "../tests/quicksort_lazy_test.hpp"
#include "../tests/quicksort_median_test.hpp"
#include "../tests/quicksort_insertion_test.hpp"
#include "../tests/quickort_tukeys_test.hpp"
#include "../tests/quicksort_true_median_test.hpp"


void graph_data(char type, vector<int>& algo_selections){
    //---------------------------------------------------------------------------------------------
    ClosedHashTable<sortData>quickSortLazyData;                 // map to store data related to sorting
    ClosedHashTable<sortData>quickSortMedianData;               // map to store data related to sorting
    ClosedHashTable<sortData>quickSortInsertionData;            // map to store data related to sorting
    ClosedHashTable<sortData>quickSortNtherData;                // map to store data related to sorting
    ClosedHashTable<sortData>quickSortTrueMedianData;           // map to store data related to sorting
    ClosedHashTable<sortData>insertSortData;  
     //---------------------------------------------------------------------------------------------
    for (int selection : algo_selections){
        int vec_size = 10;
        for (int i = 0 ; i < 100; i ++ ){
                vec_size = (vec_size + i) + (vec_size*.10);// to create increasing arrays
                vector<int>list(vec_size);                        // generate random list
                generate_vector(vec_size, type, list, vec_size);   
                vector<int>og1 = list;      // this way each test is runs the same values                   
                vector<int>og2 = list;  
                vector<int>og3 = list;
                vector<int>og4 = list;       
                vector<int>og5 = list;                 
                        
                int t = i + 1;                         // trial number for recording data
    //---------------------------------------------------------------------------------------------
            switch (selection)
            {
            case 1: runQuickSortLazyTests(     og1, t, vec_size, type, false, quickSortLazyData);  
                break; 
            case 2: runQuickSortMedianTests(   og2, t, vec_size, type, false, quickSortMedianData); 
                break;
            case 3: runQuickSortInsertionTests(og3, t, vec_size, type, false, quickSortInsertionData); 
                break;
            case 4: runQuickSortTukeysTests(    og4, t, vec_size, type, false, quickSortNtherData);
                break;
            case 5: runQuickSortTrueMedianTests(     og5, t, vec_size, type, false, quickSortTrueMedianData);
                break;
            case 6: //runShellSedgwickTests(  og6, t, vec_size, type, false, shellSortDataSedgwick);
                break;
            case 7: //runCombTests(           og7, t, vec_size, type, false, combSortData);  
                break;
            case 8: //runCountCustomTests(    og8, t, vec_size, type, false, countSortData);
                break;
            case 9: //runRadixBasicTests(     og9, t, vec_size, type, false, radixSortData);
                break;
            }
        }
    }
    //---------------------------------------------------------------------------------------------
    graph();   
    //---------------------------------------------------------------------------------------------
}

#endif