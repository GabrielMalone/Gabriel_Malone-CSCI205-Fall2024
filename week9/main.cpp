//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <random>
#include <fstream>	                                      // ofstream and file output
#include "backend/sort_data.hpp"
#include "sorting_methods/combSort.hpp"
#include "sorting_methods/shellSort.hpp"
#include "sorting_methods/bubbleSort.hpp"
#include "sorting_methods/insertionSort.hpp"
#include "backend/print_vector.hpp"
#include "backend/ClosedHashTable.hpp"

//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
random_device rd;                // random number generator for random val assignment
mt19937 gen(rd());
uniform_int_distribution<> dist(1,  100); // range from 0 to 100 for the rnadom value
ClosedHashTable<sortData>combSortData;      // map to store data related to combsorts
ClosedHashTable<sortData>shellSortData;    // map to store data related to shellsorts
ClosedHashTable<sortData>bubbleSortData;  // map to store data related to bubblesorts
ClosedHashTable<sortData>insertSortData;  // map to store data related to insertsorts
//-----------------------------------------------------------------------------------
bool sorted(vector<int>&);                    // method to confirm validity of a sort
void generate_vector(int, char, vector<int>&);  // create vect of an arrangement type
void displaySwapData(int);                         // show how many swaps a sort took
void saveSortingData(ClosedHashTable<sortData>&, string);// save the data from a sort
void runCombTests(vector<int>&, int, int, char);           // run tests and save data
void runShellTests(vector<int>&, int, int, char);          // run tests and save data
void runBubbleTests(vector<int>&, int, int, char);         // run tests and save data
void runInsertTests(vector<int>&, int, int, char);         // run tests and save data
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------------
int main(){
    int trials = 1;
    int vec_size = 1000;
    char array_type = 'r';
    for (int i = 0 ; i < trials; i ++ ){
        // generate random list
        vector<int>list(vec_size);
        generate_vector(vec_size, array_type, list);            
        // this way each test is run on the exact same values
        vector<int>og_list1 = list;                          
        vector<int>og_list2 = list;                     
        vector<int>og_list3 = list;                     
        vector<int>og_list4 = list;                          
        // for recording data
        int trial = i + 1;
        // run tests for x trials of y size, on arr type z
        runCombTests(og_list1, trial, vec_size, array_type);    
        runBubbleTests(og_list2, trial, vec_size, array_type);  
        runInsertTests(og_list3, trial, vec_size, array_type);  
        runShellTests(og_list4, trial, vec_size, array_type);
    }
    return 0;
}
//------------------------------------------------------------------------------------
// RUN AND SAVE COMB SORT DATA
//------------------------------------------------------------------------------------
void runCombTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Comb Sort: " << Colors::RESET << endl;
        //print_vector(list);                                      // see if it worked
        sortData sd = combSort(list, array_type);   // get data for each run of a sort
        combSortData.put(to_string(trial), sd); // place that data to track every sort 
        //print_vector(list);                                 // visual confirm worked
        sorted(list);                                           // confirm sort worked
        displaySwapData(sd.swaps);    // can show the output of a sort on the terminal
    //--------------------------------------------------------------------------------
    saveSortingData(combSortData, "comb_sort_" + s);                      // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// RUN AND SAVE SHELL SORT DATA
//------------------------------------------------------------------------------------
void runShellTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    vector<int>gaps{4, 2, 1};
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Shell Sort: " << Colors::RESET << endl;
        //print_vector(list);                                      // see if it worked
        sortData sd = shellSort(list, array_type);            // get data for each run 
        shellSortData.put(to_string(trial), sd);// place that data to track every sort 
        //print_vector(list);                                    // see if sort worked
        sorted(list);                                           // confirm sort worked
        displaySwapData(sd.swaps);    // can show the output of a sort on the terminal
    //--------------------------------------------------------------------------------
    saveSortingData(shellSortData, "shell_sort_" + s);                   // save data
    //--------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// RUN AND SAVE BUBBLE SORT DATA
//------------------------------------------------------------------------------------
void runBubbleTests(vector<int>& list , int trial, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    //--------------------------------------------------------------------------------
        cout << endl << Colors::YELLOW <<"Bubble Sort: " << Colors::RESET << endl;
        //print_vector(list);                                      // see if it worked
        sortData sd = bubbleSort(list, array_type);           // get data for each run 
        bubbleSortData.put(to_string(trial), sd);    // place data to track every sort 
        //print_vector(list);                                    // see if sort worked
        sorted(list);                                           // confirm sort worked
        displaySwapData(sd.swaps);    // can show the output of a sort on the terminal
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
        //print_vector(list);                                      // see if it worked
        sortData sd = insertionSort(list, array_type);        // get data for each run 
        insertSortData.put(to_string(trial), sd);    // place data to track every sort 
        //print_vector(list);                                    // see if sort worked
        sorted(list);                                           // confirm sort worked
        displaySwapData(sd.swaps);    // can show the output of a sort on the terminal
    //--------------------------------------------------------------------------------
    saveSortingData(insertSortData, "Insertion_sort_" + s);               // save data
    //--------------------------------------------------------------------------------
}


//------------------------------------------------------------------------------------
//  generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially 
//------------------------------------------------------------------------------------
void generate_vector(int size, char type, vector<int>& temp){
	switch (type){
		case 'a': // ascending
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			break;
		case 'd': // descending
			for(int i = 0; i < size; i++)
				temp[i] = size - i;
			break;
		case 'r': // random
			for(int i = 0; i < size; i++)
				temp[i] = dist(gen);
			break;
		case 'p': // partially sorted
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			// swap every 5th item
			for (size_t i = 4; i < temp.size(); i += 5) 
				swap(temp[i], temp[i - 4]);
	}
}

//----------------------------------------------------------------------------
// SHOW SWAP COUNT
//----------------------------------------------------------------------------
void displaySwapData(int swaps){
    cout << "sorting took "
         << swaps
         << " swaps"
         << endl;
}

//----------------------------------------------------------------------------
// ITERATE THROUGH MAP AND PLACE DATA INTO TEXT FILE
//----------------------------------------------------------------------------
void saveSortingData(ClosedHashTable<sortData>& SortDataMap, string sortMethod){
    ofstream f ("data/" + sortMethod + ".txt");	
    for (int i = 0 ; i < SortDataMap.m_size() ; i ++ ){
        sortData sd = SortDataMap.get(to_string(i+1));
        f << i + 1;
        f << " ";
        f << sd.order_type;
        f << " ";
        f << sd.array_size;
        f << " ";
        f << sd.swaps;
        f << endl;
    }
}

//----------------------------------------------------------------------------
// CONFIRM VALIDITY OF SORT
//----------------------------------------------------------------------------
bool sorted(vector<int>& vector){
    for (int i = 1 ; i < vector.size(); i ++){
        int prev_item = vector[i-1];
        int cur_item = vector[i];
        if (prev_item > cur_item){
            cout <<  Colors::RED 
                 << prev_item
                 << " > "
                 << cur_item
                 << " sort failed" 
                 << Colors::RESET 
                 << endl;
            return false;
        }
    }
    cout <<  Colors::GREEN 
         << "sort successful" 
         << Colors::RESET 
         << endl;
    return true;
}