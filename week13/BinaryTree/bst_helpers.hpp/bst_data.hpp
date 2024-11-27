#ifndef SEARCHDATA
#define SEARCHDATA

#include <string>
#include <iostream>

//---------------------------------------------------------
// Struct to hold swap experiment data
//---------------------------------------------------------
struct searchData{
    //-----------------------------------------------------
    std::string sort_method = "";    // record type of sort
    std::string order_type = ""; // ascend, descend, random
    int tree_nodes = 0;      // size of tree for experiment
    unsigned long long inserts = 0;         // inserts made
    int test_num = 0;            // which test run was this
    int call_stack_depth = 0;                // track depth
    int tree_height = 0;
    int total_inserts = 0;
    double average_inserts = 0;   
    //-----------------------------------------------------
    searchData(){};    // constructors not really necessary 
    //-----------------------------------------------------
    // SHOW SWAP COUNT
    //-----------------------------------------------------
    void displayDepthData(){
        std::cout << "This tree has a max height of "
            << tree_height
            << std::endl;
    }
    void displayInsertData(int val){
        std::cout << "inserting " << val << " took "
            << inserts
            << " operations"
            << std::endl;      
    }       
};
//---------------------------------------------------------

#endif