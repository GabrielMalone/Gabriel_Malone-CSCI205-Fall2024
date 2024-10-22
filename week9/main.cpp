//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------
#include "backend/ClosedHashTable.hpp"
#include "backend/show_graphs.hpp"
#include "backend/sort_data.hpp"
#include "sorting_methods/helper_methods/generate_vectors.hpp"
#include "tests/bubble_sort_test.hpp"
#include "tests/comb_test.hpp"
#include "tests/insert_test.hpp"
#include "tests/shell_sort_basic_test.hpp"
#include "tests/shell_sort_custom_test.hpp"
#include "tests/count_sort_test.hpp"
//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
ClosedHashTable<sortData>combSortData;        // map to store data related to sorting
ClosedHashTable<sortData>shellSortData;   
ClosedHashTable<sortData>bubbleSortData; 
ClosedHashTable<sortData>insertSortData;  
ClosedHashTable<sortData>shellCustomSortData;
ClosedHashTable<sortData>countSortData; 
//-----------------------------------------------------------------------------------
bool print = true;                                            // turn print on or off
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------------
int main(){
    //-------------------------------------------------------------------------------
    int trials = 50;
    int vec_size = 10;
    char type = 'r';
    //--------------------------------------------------------------------------------
    for (int i = 0 ; i < trials; i ++ ){
        vec_size = (vec_size + i) + (vec_size*.10);     // to create increasing arrays
        vector<int>list(vec_size);                             // generate random list
        generate_vector(vec_size, type, list);            
        vector<int>og1 = list;           // this way each test is runs the same values                   
        vector<int>og2 = list;                     
        vector<int>og3 = list;                     
        vector<int>og4 = list;   
        vector<int>og5 = list;  
        vector<int>og6 = list;                           
        int t = i + 1;                                // trial number for recording data
        //------------------------------------------------------------------------------
        runCombTests(       og1, t, vec_size, type, print, combSortData);    
        runBubbleTests(     og2, t, vec_size, type, print, bubbleSortData);  
        runInsertTests(     og3, t, vec_size, type, print, insertSortData);  
        runShellBasicTests( og4, t, vec_size, type, print, shellSortData);
        runShellCustomTests(og5, t, vec_size, type, print, shellCustomSortData);
        runCountCustomTests(og6, t, vec_size, type, print, countSortData);
        //-------------------------------------------------------------------------------
    }
    graph();   
    //-----------------------------------------------------------------------------------           
    return 0;
}








