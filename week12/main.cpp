//--------------------------------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI 205 / WEEK 12 / BINARY SEARCH TREES
//--------------------------------------------------------------------------------------------------------------
#include "backend/generate_vectors.hpp"
#include "backend/print_vector.hpp"
#include "tests/insertion_test.hpp"
#include "tests/height_test.hpp"

using namespace std;

BinarySearchTree<int> bst;                                             // non-self balancing binary search tree


int main(){
    // //----------------------------------------------------------------------------------------------------------
    // // SET UP ARRAY TYPE TO BE USED TO BUILD BINARY SEARCH TREE
    // //----------------------------------------------------------------------------------------------------------
    // char type = 'r';                                                                            // type of array 
    // bool print = false;                                                                 // confirmation printing
    // int vec_size = 1000000;                            // size of vec and thus the size of the final binary tree
    // //----------------------------------------------------------------------------------------------------------
    // // CREATE THE VECTOR AND THE BINARY SEARCH TREE 
    // //----------------------------------------------------------------------------------------------------------
    // vector<int> v = bst.initialize(vec_size, type, print);
    // //----------------------------------------------------------------------------------------------------------
    // // RUN ISERT TEST WITH THIS BINARY SEARCH TREE
    // //----------------------------------------------------------------------------------------------------------
    // // this will create a graph of how many operations it took to insert an item 
    // // along with the average of how many operations it is taking to insert an item 
    // // along with the ideal number of operations it should take to insert an item (log2N)
    // //----------------------------------------------------------------------------------------------------------
    // bst_insert_test(bst, v, type, print);
    // //----------------------------------------------------------------------------------------------------------
    // // FLATTEN AND CONFIRM FLAT 
    // //----------------------------------------------------------------------------------------------------------
    // // take the values in a tree and place them, in order, into a vector
    // //----------------------------------------------------------------------------------------------------------
    // vector<int>d = bst.flatten();
    // //print_vec(d);
    // //----------------------------------------------------------------------------------------------------------
    // // FIND CLOSEST VALUE
    // //----------------------------------------------------------------------------------------------------------
    // // this method will flatten the tree, then iterate through the tree vector taking the difference 
    // // between the passed in value and the current value. the smallest difference will be tracked and returned.
    // // loop will cut short if identical value found (diff == 0)
    // //----------------------------------------------------------------------------------------------------------
    // cout << bst.closest_val(1) << endl;
    // //----------------------------------------------------------------------------------------------------------
    // // VALIDATE THE BST
    // //----------------------------------------------------------------------------------------------------------
    // // A binary search tree (BST) is considered valid if, for every node in the tree, all the values in its left 
    // // subtree are smaller than the node's value, and all the values in its right subtree are larger than the
    // // node's value; essentially, the tree maintains a sorted order where the left side is always smaller and 
    // // the right side is always larger than the root node
    // //----------------------------------------------------------------------------------------------------------
    // bst.is_valid();                                                     // a job for preorder traversal, I think
    // //----------------------------------------------------------------------------------------------------------
    // // GET MAX TREE HEIGHT // will use this method to compare height balance 
    // //----------------------------------------------------------------------------------------------------------
    // cout << bst.get_height() << endl;
    // //----------------------------------------------------------------------------------------------------------
    // // HEIGHT TESTING
    // //----------------------------------------------------------------------------------------------------------
    height_testing();

    return 0;

}