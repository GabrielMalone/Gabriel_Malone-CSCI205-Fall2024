//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <random>
#include "backend/ClosedHashTable.hpp"
#include <fstream>	                                      // ofstream and file output
#include "backend/sort_data.hpp"
#include "sorting_methods/combSort.hpp"
//-----------------------------------------------------------------------------------

using namespace std;


//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
random_device rd;                // random number generator for random val assignment
mt19937 gen(rd());
uniform_int_distribution<> dist(1,  100); // range from 0 to 100 for the rnadom value
ClosedHashTable<sortData>combSortData;      // map to store data related to combsorts
sortData combSort(vector<int>&, char);  // perform combsort and return data from sort
void generate_vector(int, char, vector<int>&);  // create vect of an arrangement type
void printVector(vector<int>&);                            // show what's in a vector
void displaySwapData(int);                         // show how many swaps a sort took
void saveSortingData(ClosedHashTable<sortData>&, string);// save the data from a sort
void runCombTests(int, int, char);       // run comb tests and save comb sorting data

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------------
int main(){

    runCombTests(100, 100, 'r');  // run tests of x size for y trials, on array type z

    return 0;
}
//------------------------------------------------------------------------------------
// RUN AND SAVE COMB SORT DATA
//------------------------------------------------------------------------------------
void runCombTests(int trials, int vect_size, char array_type){
    string s{array_type};                                        // for file name info
    vector<int>list(vect_size);                                   // initialize vector
    //--------------------------------------------------------------------------------
    generate_vector(vect_size, array_type, list);              // generate random list
    printVector(list);                                             // see if it worked
    //--------------------------------------------------------------------------------
    for (int i = 0 ; i < trials ; i ++){        // run the sort for a number of trials
        vector<int>list(vect_size);                               // initialize vector
        generate_vector(vect_size, array_type, list);          // generate random list
        sortData sd = combSort(list, array_type);   // get data for each run of a sort
        combSortData.put(to_string(i + 1), sd); // place that data to track every sort 
        printVector(list);                                       // see if sort worked
        displaySwapData(sd.swaps);    // can show the output of a sort on the terminal
    }
    //--------------------------------------------------------------------------------
    saveSortingData(combSortData, "comb_sort_" + s);                      // save data
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
// SHOW WHATS IN THE VECTOR
//----------------------------------------------------------------------------
void printVector(vector<int>& list){
    cout << "[ ";
    for (int i : list){
        cout << i << ", ";
    }
    cout << " ]" << endl;
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