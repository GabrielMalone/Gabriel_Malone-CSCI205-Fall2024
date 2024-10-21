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
//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
ClosedHashTable<sortData>combSortData;        // map to store data related to sorting
ClosedHashTable<sortData>shellSortData;   
ClosedHashTable<sortData>bubbleSortData; 
ClosedHashTable<sortData>insertSortData;  
ClosedHashTable<sortData>shellCustomSortData; 
//-----------------------------------------------------------------------------------
bool printArrays = false;                                     // turn print on or off
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------------
int main(){
    int trials = 50;
    int vec_size = 10000;
    char array_type = 'r';
    for (int i = 0 ; i < trials; i ++ ){
        //vec_size = (vec_size + i) + (vec_size*.10);  // to create increasing arrays
        // generate random list
        vector<int>list(vec_size);
        generate_vector(vec_size, array_type, list);            
        // this way each test is run on the exact same values
        vector<int>og_list1 = list;                          
        vector<int>og_list2 = list;                     
        vector<int>og_list3 = list;                     
        vector<int>og_list4 = list;   
        vector<int>og_list5 = list;                         
        // for recording data
        int trial = i + 1;
        // run tests
        runCombTests(og_list1, trial, vec_size, array_type, printArrays, combSortData);    
        runBubbleTests(og_list2, trial, vec_size, array_type, printArrays, bubbleSortData);  
        runInsertTests(og_list3, trial, vec_size, array_type, printArrays, insertSortData);  
        runShellBasicTests(og_list4, trial, vec_size, array_type, printArrays, shellSortData);
        runShellCustomTests(og_list5, trial, vec_size, array_type, printArrays, shellCustomSortData);
    }
    graph();
    return 0;
}








