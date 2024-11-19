//--------------------------------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI 205 / WEEK 12 / BINARY SEARCH TREES
//--------------------------------------------------------------------------------------------------------------
#include "backend/generate_vectors.hpp"
#include "backend/print_vector.hpp"
#include "tests/insertion_test.hpp"
#include "tests/height_test.hpp"
#include "avl_t.hpp"
#include <cassert>

using namespace std;

AVL_BinarySearchTree<int> bst;                                                 // switch to run comparison tests
//BinarySearchTree<int> bst;                                       

int main(){
    //----------------------------------------------------------------------------------------------------------
    // SET UP ARRAY TYPE TO BE USED TO BUILD BINARY SEARCH TREE - worst case 'ascending' data
    //----------------------------------------------------------------------------------------------------------
    char type = 'r';                                                                            // type of array 
    bool print = false;                                                                 // confirmation printing
    int vec_size = 10;                  // size of vec/size of final binary tree  - repeat vals not inlc in tree
    //----------------------------------------------------------------------------------------------------------
    // CREATE THE VECTOR AND THE BINARY SEARCH TREE 
    //----------------------------------------------------------------------------------------------------------
    vector<int> v = bst.initialize(vec_size, type, print);
	int width = to_string(vec_size).length();                           // currently crashes if tree size > 999
	bst.fill_matrix(width);
//    //----------------------------------------------------------------------------------------------------------
//    // RUN ISERT TEST WITH THIS BINARY SEARCH TREE
//    //----------------------------------------------------------------------------------------------------------
//    // this will create a graph of how many operations it took to insert an item
//    // along with the average of how many operations it is taking to insert an item
//    // along with the ideal number of operations it should take to insert an item (log2N)
//    //----------------------------------------------------------------------------------------------------------
//    bst_insert_test(bst, v, type, print);
//    //----------------------------------------------------------------------------------------------------------
//    // FLATTEN AND CONFIRM FLAT
//    //----------------------------------------------------------------------------------------------------------
//    // take the values in a tree and place them, in order, into a vector
//    //----------------------------------------------------------------------------------------------------------
//    vector<int>d = bst.flatten();
//    print_vec(d);                                                                      // confrim flatten worked
//    //----------------------------------------------------------------------------------------------------------
//    // FIND CLOSEST VALUE
//    //----------------------------------------------------------------------------------------------------------
//    // this method will flatten the tree, then iterate through the tree vector taking the difference
//    // between the passed in value and the current value. the smallest difference will be tracked and returned.
//    // loop will cut short if identical value found (diff == 0)
//    //----------------------------------------------------------------------------------------------------------
//    int close_val = 1;
//    cout << "Closest value to " << close_val << " in the tree is:  " << bst.closest_val(close_val) << endl;
//    //----------------------------------------------------------------------------------------------------------
//    // VALIDATE THE BST
//    //----------------------------------------------------------------------------------------------------------
//    // A binary search tree (BST) is considered valid if, for every node in the tree, all the values in its left
//    // subtree are smaller than the node's value, and all the values in its right subtree are larger than the
//    // node's value; essentially, the tree maintains a sorted order where the left side is always smaller and
//    // the right side is always larger than the root node
//    //----------------------------------------------------------------------------------------------------------
//    bst.is_valid();                                                 // a job for preorder traversal, I think
//    //----------------------------------------------------------------------------------------------------------
//    // GET MAX TREE HEIGHT // will use this method to compare height balance
//    //----------------------------------------------------------------------------------------------------------
//    cout << "Height of this tree is: " << bst.get_height() << endl;
//    //----------------------------------------------------------------------------------------------------------
//    // FIND KTH SMALLEST VALUE
//    //----------------------------------------------------------------------------------------------------------
//    int kth_val = bst.tree_nodes()/2;                            // just get a value that will always be present
//    int kth_smallest_val = bst.kth_smallest(kth_val);
//    cout << "The " << kth_val << "th smallest value in the tree is: " << kth_smallest_val << endl;
//    print_vec(d);
//    assert(kth_smallest_val == d[kth_val-1]);                 // can confirm by checking index of flattened tree
//    //----------------------------------------------------------------------------------------------------------
//    // FIND THE BALANCE FACTOR
//    //----------------------------------------------------------------------------------------------------------
//    //bst.set_Balance();                                            // this function needed for the non avl tree
//    bst.print();
//    cout << "The Balance Factor of this tree is: " << bst.balance_factor() << endl;
//    //----------------------------------------------------------------------------------------------------------
//    // HEIGHT TESTING - test various insertion methods from a sorted array to see their effectiveness
//    //----------------------------------------------------------------------------------------------------------
//    height_testing();
   
    return 0;

}