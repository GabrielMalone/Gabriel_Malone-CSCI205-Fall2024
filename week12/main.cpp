#include "backend/generate_vectors.hpp"
#include "backend/print_vector.hpp"
#include "tests/random_search.hpp"

using namespace std;

BinarySearchTree<int> bst;


int main(){
//--------------------------------------------------------------------------------------------------------------
// SET UP ARRAY TYPE TO BE USED TO BUILD BINARY SEARCH TREE
//--------------------------------------------------------------------------------------------------------------
    char type = 'r';                                                                            // type of array 
    bool print = false;                                                                 // confirmation printing
    int vec_size = 10000;                              // size of vec and thus the size of the final binary tree
//--------------------------------------------------------------------------------------------------------------
// CREATE THE VECTOR AND THE BINARY SEARCH TREE 
//--------------------------------------------------------------------------------------------------------------
    vector<int> v = bst.initialize(vec_size, type, print);
//--------------------------------------------------------------------------------------------------------------
// RUN ISERT TEST WITH THIS BINARY SEARCH TREE
//--------------------------------------------------------------------------------------------------------------
    bst_insert_random_array_test(bst, v, type, print);
    return 0;
}