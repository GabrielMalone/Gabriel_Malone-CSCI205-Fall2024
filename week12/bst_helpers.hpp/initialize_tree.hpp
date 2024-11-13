#ifndef bst_initialize
#define bst_initialize

#include "../bst.hpp"

using namespace std;

template<typename V>
void intialize_bst(BinarySearchTree<V>& bst, vector<V>& v){
    for (int i = 0 ; i < v.size() ; i ++ ){
        bst.insert(v[i]);
    }
};

#endif