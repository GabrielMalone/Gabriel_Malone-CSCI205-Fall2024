#ifndef SORTDATA
#define SORTDATA

#include <string>
#include <iostream>

//---------------------------------------------------------
// Struct to hold swap experiment data
//---------------------------------------------------------
struct sortData{
    //-----------------------------------------------------
    std::string sort_method = "";    // record type of sort
    std::string order_type = ""; // ascend, descend, random
    int array_size = 0;     // size of array for experiment
    int swaps = 0;    // how many swaps to order this array
    int comparisons = 0;       // how many comparisons made
    int test_num = 0;            // which test run was this
    //-----------------------------------------------------
    sortData(){};
    sortData(char type,int arr_size,int num_swaps,int comp)
    {
        order_type = type;
        array_size = arr_size;
        swaps = num_swaps;
        comparisons = comp;
    };
    //-----------------------------------------------------
    // SHOW SWAP COUNT
    //-----------------------------------------------------
    void displaySwapData(){
        std::cout << "sorting took "
            << swaps
            << " swaps"
            << std::endl;
    }
    void displayCompareData(){
        std::cout << "sorting took "
            << comparisons
            << " comparisons"
            << std::endl;
    }     
};
//---------------------------------------------------------

#endif