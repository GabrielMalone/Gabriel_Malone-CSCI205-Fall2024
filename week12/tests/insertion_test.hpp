#ifndef RANDOM_SEARCH
#define RANDOM_SEARCH

#include <random>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../bst.hpp"
#include "../backend/saveSearchData.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../backend/graph_insertion_tests.hpp"
#include "../avl_t.hpp"

ClosedHashTable<searchData>random_test_map;

using namespace std;

//--------------------------------------------------------------------------------------------------------------
// CALCULATE HOW MANY SEARCH OPERATIONS, ON AVERAGE, IT TAKES TO INSERT AN ITEM INTO A BST 
// when the tree initialized with randomized data
//--------------------------------------------------------------------------------------------------------------
template<typename T>
void bst_insert_test(BinarySearchTree<T>& bst, vector<T>& v, char type, bool print){
    random_device rd;                                       // random number generator for random val assignment
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, bst.tree_nodes() * 2);       // set up to  get val not present in the BST
    bst.get_data().tree_nodes = bst.tree_nodes();                   // record size of the tree for graphing data
    bst.get_data().order_type = type;                                            // order type set to 'r' random
    vector<T> results_vector;                                            // initialize vector of size of the BST
    int i = 0;                                                                           // counter for the loop
    while (i < 1000){                   // run test to see how many operations it takes to insert a random value
        bst.get_data().inserts = 0;                                                      // reset count each run
        int rand_val = dist(gen);                                                  // get random value to insert
        bst.insert(rand_val);                                                  // insert the unique random value
        bst.get_data().total_inserts += bst.get_data().inserts;
        bst.get_data().average_inserts = bst.get_data().total_inserts / (double)(i+1);
        results_vector.emplace_back(bst.get_data().inserts);                                  // record the data
        random_test_map.put(to_string(i), bst.get_data());                      // save data in map for plotting
        if (print)
            bst.get_data().displayInsertData(rand_val);
        if (find(v.begin(), v.end(), rand_val) == v.end()){
            bst.remove(rand_val);              // remove val if not part of original tree to keep tree same size 
        }
        i ++ ; 
    }
    //----------------------------------------------------------------------------------------------------------
    // Get the average value from the vector
    //----------------------------------------------------------------------------------------------------------
    double total = 0;                                                                  // double to hold the sum
    double avg = 0;
    for (int j = 0 ; j < results_vector.size(); j ++  ){
        total += results_vector[j];                                                    // sum up all the results
    }
    avg = total / (double)results_vector.size();                                         // calulate the average
    //----------------------------------------------------------------------------------------------------------
    // Compare this value to the theoretical best case performance of inserting an item  (log base 2 of N)
    //----------------------------------------------------------------------------------------------------------
    double val = (double)(bst.tree_nodes());
    double best_case = log2(val);                                  // this is log base 2 of total num tree nodes                                               
    if (print)
        bst.print();
    cout << "log base 2 of this BST (" << bst.tree_nodes() << " nodes): " << best_case << endl;
    cout << "actual avg insert performance: " << avg << " operations." << endl;
    //----------------------------------------------------------------------------------------------------------
    // Plot data
    //----------------------------------------------------------------------------------------------------------
    saveSortingData(random_test_map, "random_data_insertion", best_case, avg);  // place the data into text file
    graph();
};
template<typename T>
void bst_insert_test(AVL_BinarySearchTree<T>& bst, vector<T>& v, char type, bool print){
    random_device rd;                                       // random number generator for random val assignment
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, bst.tree_nodes() * 2);       // set up to  get val not present in the BST
    bst.get_data().tree_nodes = bst.tree_nodes();                   // record size of the tree for graphing data
    bst.get_data().order_type = type;                                            // order type set to 'r' random
    vector<T> results_vector;                                            // initialize vector of size of the BST
    int i = 0;                                                                           // counter for the loop
    while (i < 1000){                   // run test to see how many operations it takes to insert a random value
        bst.get_data().inserts = 0;                                                      // reset count each run
        int rand_val = dist(gen);                                                  // get random value to insert
        bst.insert(rand_val);                                                  // insert the unique random value
        bst.get_data().total_inserts += bst.get_data().inserts;
        bst.get_data().average_inserts = bst.get_data().total_inserts / (double)(i+1);
        results_vector.emplace_back(bst.get_data().inserts);                                  // record the data
        random_test_map.put(to_string(i), bst.get_data());                      // save data in map for plotting
        if (print)
            bst.get_data().displayInsertData(rand_val);
        if (find(v.begin(), v.end(), rand_val) == v.end()){
            bst.remove(rand_val);              // remove val if not part of original tree to keep tree same size 
        }
        i ++ ; 
    }
    //----------------------------------------------------------------------------------------------------------
    // Get the average value from the vector
    //----------------------------------------------------------------------------------------------------------
    double total = 0;                                                                  // double to hold the sum
    double avg = 0;
    for (int j = 0 ; j < results_vector.size(); j ++  ){
        total += results_vector[j];                                                    // sum up all the results
    }
    avg = total / (double)results_vector.size();                                         // calulate the average
    //----------------------------------------------------------------------------------------------------------
    // Compare this value to the theoretical best case performance of inserting an item  (log base 2 of N)
    //----------------------------------------------------------------------------------------------------------
    double val = (double)(bst.tree_nodes());
    double best_case = log2(val);                                  // this is log base 2 of total num tree nodes                                               
    if (print)
        bst.print();
    cout << "log base 2 of this BST (" << bst.tree_nodes() << " nodes): " << best_case << endl;
    cout << "actual avg insert performance: " << avg << " operations." << endl;
    //----------------------------------------------------------------------------------------------------------
    // Plot data
    //----------------------------------------------------------------------------------------------------------
    saveSortingData(random_test_map, "random_data_insertion", best_case, avg);  // place the data into text file
    graph();
};

#endif