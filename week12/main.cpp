//----------------------------------------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI 205 / WEEK 12 / BINARY SEARCH TREES
//----------------------------------------------------------------------------------------------------------------------
#include "backend/generate_vectors.hpp"
#include "backend/print_vector.hpp"
#include "tests/insertion_test.hpp"
#include "tests/height_test.hpp"
#include "bst_helpers.hpp/initialize_tree.hpp"
#include "avl_t.hpp"
#include <cassert>

using namespace std;

//BinarySearchTree<int> bst;                                       

int main(){
    AVL_BinarySearchTree<int> bst;                                                     // switch to run comparison tests
    //------------------------------------------------------------------------------------------------------------------
    // SET UP ARRAY TYPE TO BE USED TO BUILD BINARY SEARCH TREE - worst case 'ascending' data
    //------------------------------------------------------------------------------------------------------------------
    char type = 'r';                                                                                    // type of array
    bool print = false;    
    int vec_size = 0;                           // size of vec/size of final binary tree  - repeat vals not inlc in tree
    std::cout << "\033[2J\033[1;1H";                                            
    cout << "BINARY SEARCH TREE-O-MAKER 9000" << endl;
    cout << "--------------------------------" << endl;
    cout << "Size of vector of random ints from which to create binary search tre: \n";
    cout << "(either enable side scrolling or reduce font size for sizes over 30) : ";
    cin >> vec_size;
    //------------------------------------------------------------------------------------------------------------------
    // CREATE THE VECTOR AND THE BINARY SEARCH TREE 
    //------------------------------------------------------------------------------------------------------------------
    vector<int> v = bst.initialize(vec_size, type, print);
	int width = to_string(vec_size).length();                                    // currently crashes if tree size > 999
    if (width == 1) width = 2;                                                          // need spacing to be at least 2
	bst.print();
    //------------------------------------------------------------------------------------------------------------------
    // RUN ISERT TEST WITH THIS BINARY SEARCH TREE
    //------------------------------------------------------------------------------------------------------------------
    // this will create a graph of how many operations it took to insert an item
    // along with the average of how many operations it is taking to insert an item
    // along with the ideal number of operations it should take to insert an item (log2N)
    //------------------------------------------------------------------------------------------------------------------
    // bst_insert_test(bst, v, type, print);
    //------------------------------------------------------------------------------------------------------------------
    // FLATTEN AND CONFIRM FLAT
    //------------------------------------------------------------------------------------------------------------------
    // take the values in a tree and place them, in order, into a vector
    //------------------------------------------------------------------------------------------------------------------
    cout << "This tree flattened into ascending order: ";
    vector<int>d = bst.flatten();
    print_vec(d);                                                                              // confrim flatten worked
    cout << "This tree flattened into its original order: ";
    vector<int>z = bst.preOrderVector();
    print_vec(z);                                                                              // confrim flatten worked
    //------------------------------------------------------------------------------------------------------------------
    // FIND CLOSEST VALUE
    //------------------------------------------------------------------------------------------------------------------
    // this method will flatten the tree, then iterate through the tree vector taking the difference
    // between the passed in value and the current value. the smallest difference will be tracked and returned.
    // loop will cut short if identical value found (diff == 0)
    //------------------------------------------------------------------------------------------------------------------
    int close_val = 1;
    cout << "Closest value to " << close_val << " in the tree is:  " << bst.closest_val(close_val) << endl;
    //------------------------------------------------------------------------------------------------------------------
    // VALIDATE THE BST
    //------------------------------------------------------------------------------------------------------------------
    // A binary search tree (BST) is considered valid if, for every node in the tree, all the values in its left
    // subtree are smaller than the node's value, and all the values in its right subtree are larger than the
    // node's value; essentially, the tree maintains a sorted order where the left side is always smaller and
    // the right side is always larger than the root node
    //------------------------------------------------------------------------------------------------------------------
    bst.is_valid();                                                             // a job for preorder traversal, I think
    //------------------------------------------------------------------------------------------------------------------
    // GET MAX TREE HEIGHT // will use this method to compare height balance
    //------------------------------------------------------------------------------------------------------------------
    cout << "Height of this tree is: " << bst.get_height() << endl;
    cout << "Total number of nodes in this tree is: " << bst.tree_nodes();
    //------------------------------------------------------------------------------------------------------------------
    // FIND KTH SMALLEST VALUE
    //------------------------------------------------------------------------------------------------------------------
    int kth_val = bst.tree_nodes()/2;                                    // just get a value that will always be present
    int kth_smallest_val = bst.kth_smallest(kth_val);
    cout << "\nThe " << kth_val << "th smallest value in the tree is: " << kth_smallest_val << endl;
    assert(kth_smallest_val == d[kth_val-1]);                         // can confirm by checking index of flattened tree
    //------------------------------------------------------------------------------------------------------------------
    // HEIGHT TESTING - test various insertion methods from a sorted array to see their effectiveness
    //------------------------------------------------------------------------------------------------------------------
    // height_testing();
    //------------------------------------------------------------------------------------------------------------------
    // GRAPHICAL TREE MANIPULATION
    //------------------------------------------------------------------------------------------------------------------
    cout << "The Balance Factor of this tree is: " << bst.balance_factor() << endl;
    int value = 0;
    while (value != -1) {
        char selection = ' ';
        cout << "\n(a)dd or (r)emove value: ";
        cin >> selection;
        if (selection == 'a'){
            cout << "\nSelect value to add to the tree ";
            cin >> value;
            bst.insert(value);                  // original tree will continue to receive the actual inserts and removes
            vector<int> testa = bst.preOrderVector();                                // get preorder vector to copy tree
            AVL_BinarySearchTree<int>bstA;      // need make new tree to print/some lingering variable messing things up
            bstA.copyTree(testa);                                                        // flatten the data in preorder
            bstA.print();                         // insert vanilla from that preorder vector to copy old tree as it was
        }
         if (selection == 'r'){
            cout << "\nSelect value to remove from the tree ";
            cin >> value;
            bst.remove(value);
			vector<int> testb = bst.preOrderVector();
            AVL_BinarySearchTree<int>bstB;
            bstB.copyTree(testb);
			bstB.print();
        }
    }
    return 0;
}