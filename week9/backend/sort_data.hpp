#ifndef SORTDATA
#define SORTDATA

#include <string>

//-----------------------------------------------------------------------------------
// Struct to hold swap experiment data
//-----------------------------------------------------------------------------------
struct sortData{
    //-----------------------------------------------------
    std::string sort_method = "";    // record type of sort
    std::string order_type = ""; // ascend, descend, random
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

#endif