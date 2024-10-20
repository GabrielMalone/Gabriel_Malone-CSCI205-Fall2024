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
//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------
// Struct to hold swap experiment data
//-----------------------------------------------------------------------------------
struct sortData{
    //-----------------------------------------------------
    string sort_method = "";         // record type of sort
    string order_type = "";// ascending, descending, random
    int array_size = 0;     // size of array for experiment
    int swaps = 0;    // how many swaps to order this array
    int test_num = 0;            // which test run was this
    //-----------------------------------------------------
    sortData(){};
    sortData(char type, int arr_size, int num_swaps)
    {
        order_type = type;
        array_size = arr_size;
        swaps = num_swaps;
    };
};
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
// COMB SORT METHOD (Bubble Sort with gaps)
//------------------------------------------------------------------------------------
sortData combSort(vector<int>&list, char type){
    //--------------------------------------------------------------------------------
    // method vars
    //--------------------------------------------------------------------------------
    int gap = list.size();                                         // initial gap size
    double shrink = 1.3;                                              // shrink factor
    bool sorted = false;                                              // search switch
    int i = 0;
    int swaps = 0;
    //--------------------------------------------------------------------------------
    // Outter loop to gap check and terminate when at 1
    //--------------------------------------------------------------------------------
    while (! sorted)                                          // continue until sorted
    {   
        if (gap > 1)                  // not done sorting until final pass of gap of 1
        {
            sorted = false;
        }
        if (gap < 1){                                                   // final pass
            sorted = true;
        }
        //----------------------------------------------------------------------------
        // Inner loop to do actual position check and swapping
        //----------------------------------------------------------------------------
        i = 0;
        while (i + gap < list.size())  //                   index position + gap width                      
        {
            if (list[i] > list[i + gap])                 // if larger element in front
            {   
                int tempA = list[i];                                           // swap
                int tempB = list[i + gap];                           // use temp items
                list[i] = tempB;
                list[i + gap] = tempA;
                sorted = false; 
                swaps ++ ;                                              // track swaps 
            }
            i ++ ;
        }   
        gap = floor(gap / shrink);                         // reduce gap for next pass          
    }
    return sortData(type, list.size(), swaps); 
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