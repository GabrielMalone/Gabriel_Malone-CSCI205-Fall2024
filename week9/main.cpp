//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------

#include <iostream>
#include "backend/sort_data.hpp"
#include "backend/saveSearchData.hpp"
#include "sorting_methods/combSort.hpp"
#include "sorting_methods/shellSortBasic.hpp"
#include "sorting_methods/shellSortCustomGap.hpp"
#include "sorting_methods/bubbleSort.hpp"
#include "sorting_methods/insertionSort.hpp"
#include "sorting_methods/helper_methods/hibbard_sequence.hpp"
#include "sorting_methods/helper_methods/validate_sort.hpp"
#include "sorting_methods/helper_methods/generate_vectors.hpp"
#include "sorting_methods/helper_methods/sedgwick_sequence.hpp"
#include "sorting_methods/helper_methods/knuth_sequence.hpp"

//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
ClosedHashTable<sortData>combSortData;      // map to store data related to combsorts
ClosedHashTable<sortData>shellSortData;    // map to store data related to shellsorts
ClosedHashTable<sortData>bubbleSortData;  // map to store data related to bubblesorts
ClosedHashTable<sortData>insertSortData;  // map to store data related to insertsorts
ClosedHashTable<sortData>shellCustomSortData;  // map to store data related to custom
//-----------------------------------------------------------------------------------
bool printArrays = false;                                     // turn print on or off
bool sorted(vector<int>&);                    // method to confirm validity of a sort
void saveSortingData(ClosedHashTable<sortData>&, string);// save the data from a sort
void runCombTests(vector<int>&, int, int, char);           // run tests and save data
void runShellBasicTests(vector<int>&, int, int, char);     // run tests and save data
void runShellCustomTests(vector<int>&, int, int, char);    // run tests and save data
void runBubbleTests(vector<int>&, int, int, char);         // run tests and save data
void runInsertTests(vector<int>&, int, int, char);         // run tests and save data
void graph();
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------------
int main(){
    int trials = 50;
    int vec_size = 10000;
    char array_type = 'a';
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
        // run tests for x trials of y size, on arr type z
        runCombTests(og_list1, trial, vec_size, array_type);    
        runBubbleTests(og_list2, trial, vec_size, array_type);  
        runInsertTests(og_list3, trial, vec_size, array_type);  
        runShellBasicTests(og_list4, trial, vec_size, array_type);
        runShellCustomTests(og_list5, trial, vec_size, array_type);
    }
     graph();
    return 0;
}
//------------------------------------------------------------------------------------
// RUN AND SAVE COMB SORT DATA
//------------------------------------------------------------------------------------
void runCombTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        if (printArrays){print_vector(list);}                      // see if it worked 
        cout << endl << Colors::YELLOW <<"Comb Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = combSort(list, array_type);   // get data for each run of a sort
        combSortData.put(to_string(trial), sd); // place that data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(combSortData, "comb_sort_" + s);                      // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT BASIC DATA
//------------------------------------------------------------------------------------
void runShellBasicTests(vector<int>& list,int trial,int vect_size,char array_type){
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

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT CUSTOM GAP DATA
//------------------------------------------------------------------------------------
void runShellCustomTests(vector<int>& list,int trial,int vect_size,char array_type){
    string s{array_type};                                        // for file name info
    vector<int>gaps = hibbard(vect_size);
    //vector<int>gaps = sedgwick(vect_size);
    //vector<int>gaps = knuth(vect_size);
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW << "Shell Sort Custom Gap: " << Colors::RESET 
             << endl;
        if (printArrays){print_vector(list);}                      // see if it worked                                   
        sortData sd = shellSortCustomGaps(list,gaps,array_type);           // get data 
        shellCustomSortData.put(to_string(trial), sd);    // place data to track sorts 
        if (printArrays){print_vector(list);}                      // see if it worked  
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(shellCustomSortData, "shell_sort_Custom_Gap_" + s);   // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// RUN AND SAVE BUBBLE SORT DATA
//------------------------------------------------------------------------------------
void runBubbleTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Bubble Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = bubbleSort(list, array_type);           // get data for each run 
        bubbleSortData.put(to_string(trial), sd);    // place data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(bubbleSortData, "bubble_sort_" + s);                  // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// RUN AND SAVE INSERTION SORT DATA
//------------------------------------------------------------------------------------
void runInsertTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Insertion Sort: " << Colors::RESET << endl;
        if (printArrays){print_vector(list);}                      // see if it worked 
        sortData sd = insertionSort(list, array_type);        // get data for each run 
        insertSortData.put(to_string(trial), sd);    // place data to track every sort 
        if (printArrays){print_vector(list);}                      // see if it worked 
        sorted(list);                                           // confirm sort worked
        sd.displaySwapData();         // can show the output of a sort on the terminal
        sd.displayCompareData();
    //--------------------------------------------------------------------------------
    saveSortingData(insertSortData, "Insertion_sort_" + s);               // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// OUTPUT GRAPHS
//------------------------------------------------------------------------------------
void graph() {
	int status = system("python3 backend/plot.py"); 
	if (status == -1)
	{
		cerr << "\npython script failed :[\n" << endl;
	} else {
		cout << "\n  graphs created successfully!\n" << endl;
		cout << "  all .txt data cleared\n" << endl;
	}
}
