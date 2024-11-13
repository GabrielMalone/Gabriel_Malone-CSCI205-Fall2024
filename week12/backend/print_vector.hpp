#ifndef H_PRINT_VEC
#define H_PRINT_VEC

#include <iostream>
#include <vector>

using namespace std;

template<typename V>
void print_vec(vector<V>& v){
    for (int i = 0 ; i < v.size() ; i ++ ){
        cout << v[i] << " ";
    }
    cout << endl;
};


#endif