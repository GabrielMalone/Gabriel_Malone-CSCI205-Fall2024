#ifndef MENU_GRAPH_CHARTS
#define MENU_GRAPH_CHARTS

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


void graph_data(char type, vector<int>& algo_selections){

    ClosedHashTable<sortData>combSortData;        // map to store data related to sorting
    ClosedHashTable<sortData>shellSortData; 
    ClosedHashTable<sortData>shellSortDataKnuth;   
    ClosedHashTable<sortData>shellSortDataSedgwick;   
    ClosedHashTable<sortData>shellSortDataHibbard;     
    ClosedHashTable<sortData>bubbleSortData; 
    ClosedHashTable<sortData>insertSortData;  
    ClosedHashTable<sortData>countSortData; 
    ClosedHashTable<sortData>radixSortData; 
    
    for (int selection : algo_selections){
        int vec_size = 10;
        for (int i = 0 ; i < 50; i ++ ){
                vec_size = (vec_size + i) + (vec_size*.10);// to create increasing arrays
                vector<int>list(vec_size);                        // generate random list
                generate_vector(vec_size, type, list);   
                vector<int>og1 = list;      // this way each test is runs the same values                   
                vector<int>og2 = list;                     
                vector<int>og3 = list;                     
                vector<int>og4 = list;   
                vector<int>og5 = list;  
                vector<int>og6 = list;   
                vector<int>og7 = list;
                vector<int>og8 = list;   
                vector<int>og9 = list;               
                        
                int t = i + 1;                         // trial number for recording data
    //---------------------------------------------------------------------------------
            switch (selection)
            {
            case 1: runBubbleTests(         og1, t, vec_size, type, false, bubbleSortData);  
                break; 
            case 2: runInsertTests(         og2, t, vec_size, type, false, insertSortData); 
                break;
            case 3: runShellBasicTests(     og3, t, vec_size, type, false, shellSortData); 
                break;
            case 4: runShellHibbardTests(   og4, t, vec_size, type, false, shellSortDataHibbard);
                break;
            case 5: runShellKnuthTests(     og5, t, vec_size, type, false, shellSortDataKnuth);
                break;
            case 6: runShellSedgwickTests(  og6, t, vec_size, type, false, shellSortDataSedgwick);
                break;
            case 7: runCombTests(           og7, t, vec_size, type, false, combSortData);  
                break;
            case 8: runCountCustomTests(    og8, t, vec_size, type, false, countSortData);
                break;
            case 9: runRadixBasicTests(     og9, t, vec_size, type, false, radixSortData);
                break;
            }
        }
    }
    graph();   
}

#endif