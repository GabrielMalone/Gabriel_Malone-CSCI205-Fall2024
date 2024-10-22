//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------
#include "backend/ClosedHashTable.hpp"
#include "backend/print_graph.hpp"
#include "backend/show_graphs.hpp"
#include "backend/sort_data.hpp"
#include "sorting_methods/helper_methods/generate_vectors.hpp"
#include "tests/bubble_sort_test.hpp"
#include "tests/comb_test.hpp"
#include "tests/insert_test.hpp"
#include "tests/shell_sort_basic_test.hpp"
#include "tests/shell_sort_knuth_test.hpp"
#include "tests/shell_sort_hibbard_test.hpp"
#include "tests/shell_sort_sedgwick_test.hpp"
#include "tests/count_sort_test.hpp"
#include "tests/radix_sort_test.hpp"
#include <iomanip>
#include <iostream>
#include <string>

//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
ClosedHashTable<sortData>combSortData;        // map to store data related to sorting
ClosedHashTable<sortData>shellSortData; 
ClosedHashTable<sortData>shellSortDataKnuth;   
ClosedHashTable<sortData>shellSortDataSedgwick;   
ClosedHashTable<sortData>shellSortDataHibbard;     
ClosedHashTable<sortData>bubbleSortData; 
ClosedHashTable<sortData>insertSortData;  
ClosedHashTable<sortData>countSortData; 
ClosedHashTable<sortData>radixSortData; 

void graphical_sorting_data(char, int);
void graph_data(char, vector<int>&);
//-----------------------------------------------------------------------------------
bool print = true;                                            // turn print on or off
//-----------------------------------------------------------------------------------
                                             // vector of the sorting algorithm names
vector<string> fileNames =
    {
        "BUBBLE SORT",
        "INSERTION SORT",
        "SHELL SORT - N/2 GAP",
        "SHELL SORT - HIBBARD GAP",
        "SHELL SORT - KNUTH GAP",
        "SHELL SORT - SEDGWICK GAP",
        "COMB SORT",
        "COUNTING SORT",
        "RADIX SORT"
    };
//-----------------------------------------------------------------------------------
                                    // vector of the sorting vectory set up options
vector<string> arrayTypes =
    {
        "SORTED - ASCENDING",
        "SORTED - DESCENDING",
        "PARTIALLY SORTED",
        "RANDOM",
    };
//-----------------------------------------------------------------------------------
                                    // vector of the sorting vectory set up options
vector<string> experiment_type =
    {
        "GRAPHICAL SORTING DEMO",
        "GRAPH DATA",
    };

//-----------------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------------
int main(){

    //-------------------------------------------------------------------------------
    char type = 'r';                                             // set type of array 
    //-------------------------------------------------------------------------------

    int minWidth = 57;
    int algo_selection;
    int array_type_selection;
    int experiment_selection;
    
    size_t i = 1;
    // create menu seleciton box
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "--------------------------------------------------------------" << endl;
    cout << "                     ARRAY SET UP OPTIONS                     " << endl;
    cout << "--------------------------------------------------------------" << endl;
    i = 1;
	for (string fileName : arrayTypes)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+------------------------------------------------------------+ " << endl;
	cout << "  SELECT ARRAY TYPE: "; cin >> array_type_selection;

    //-------------------------------------------------------------------------------
    cout << "--------------------------------------------------------------" << endl;
    cout << "                    ARRAY SET UP OPTIONS                      " << endl;
    cout << "--------------------------------------------------------------" << endl;
    i = 1;
	for (string fileName : experiment_type)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+------------------------------------------------------------+ " << endl;
	cout << "  SELECT  TYPE: "; cin >> experiment_selection;

    //---------------------------------------------------------------------------
    i = 1;
    cout << "--------------------------------------------------------------" << endl;
    cout << "                 ITERATIVE SORTING ALGORITHMS                 " << endl;
    cout << "--------------------------------------------------------------" << endl;
	for (string fileName : fileNames)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+------------------------------------------------------------+ " << endl;

    //-------------------------------------------------------------------------------
    switch (array_type_selection)
    {
    case 1: type = 'a';
        break;
    case 2: type = 'd';
        break;
    case 3: type = 'p';
        break;
    case 4: type = 'r';
        break;
    default: type = 'r';
        break;
    }
    //-------------------------------------------------------------------------------
    vector<int>algo_selections;

    if (experiment_selection == 1){
        cout << "  SELECT ALOGORITHM: "; cin >> algo_selection;
        graphical_sorting_data(type, algo_selection);
    }
    else {
        cout << "  SELECT ALOGORITHM(S) FOR COMAPRISON (Enter after each, 0 when done): "; 
        cin >> experiment_selection;
        while (experiment_selection != 0){
            algo_selections.emplace_back(experiment_selection);
            cin >> experiment_selection;
        }
        graph_data(type, algo_selections);
    }

    //---------------------------------------------------------------------------------
       
    return 0;
}

void graph_data(char type, vector<int>& algo_selections){
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

void graphical_sorting_data(char type, int selection){
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






