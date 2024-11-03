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
    unsigned long long array_accesses = 0; // array accssed
    unsigned long long comparisons = 0; // comparisons made
    int test_num = 0;            // which test run was this
    int call_stack_depth = 0;                // track depth
    int max_depth = 0;
    //-----------------------------------------------------
    sortData(){};      // constructors not really necessary 
    sortData(char type,int arr_size,int array_acc,int comp)
    {
        order_type = type;
        array_size = arr_size;
        array_accesses = array_acc;
        comparisons = comp;
    };
    //-----------------------------------------------------
    // SHOW SWAP COUNT
    //-----------------------------------------------------
    void displaySwapData(){
        std::cout << "sorting took "
            << array_accesses
            << " array_accesses"
            << std::endl;
    }
    void displayCompareData(){
        std::cout << "sorting took "
            << comparisons
            << " comparisons"
            << std::endl;
    } 
    void displayDepthData(){
        std::cout << "sorting placed "
            << max_depth
            << " methods on the call stack"
            << std::endl;
    }       
};
//---------------------------------------------------------

#endif