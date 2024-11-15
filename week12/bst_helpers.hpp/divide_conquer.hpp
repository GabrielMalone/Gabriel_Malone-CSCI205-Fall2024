#ifndef DIVIDE_CONQUER
#define DIVIDE_CONQUER

#include <vector>
#include "../bst.hpp"

using namespace std;


void divide_conquer(vector<int>& v, BinarySearchTree<int>& bst){              // recursive solution to the balanced tree
    if (v.size() < 1){                                                                                      // base case
        return;
    }
    int middle_index = (v.size()/2);                                                                 // get middle index
    bst.insert(v[middle_index]);                                                           // insert this item into tree
	v.erase(v.begin() + middle_index);                                                    // erase this item from vector
    vector<int>v_left(v.begin(), v.begin() + (v.size()/2));                                             // get left half
    divide_conquer(v_left, bst);                                                             // recursive call left side
    vector<int>v_right(v.begin() + (v.size()/2), v.end());                                             // get right half
    divide_conquer(v_right, bst);                                                           // recursive call right side
}

#endif