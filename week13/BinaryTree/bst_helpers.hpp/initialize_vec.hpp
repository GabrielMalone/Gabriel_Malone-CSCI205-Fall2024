#ifndef INITIAL_VEC
#define INITIAL_VEC

#include "../../Backend/generate_vectors.hpp"
#include "../../Backend/print_vector.hpp"

#include <vector>


using namespace std;

void intialize_vector(vector<int>& v, int vec_size, char type, bool print){
    int data_range = vec_size;                          // range of data to use 
    generate_vector(vec_size, type , v, data_range);    // what kind of data do you want in the vector
    if (print)
        print_vec(v);                                   // confirm working
}

#endif