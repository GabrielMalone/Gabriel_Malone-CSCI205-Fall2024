#ifndef HIBBARD
#define HIBBARD

#include <vector>
#include <cmath>

std::vector<int> hibbard (int size){
    std::vector<int>hs;                 
    int k = 0;
    int h = 1;                      // starting value
    while (k < size){               // make new numbers in the sequence until the number is greater than the size of the vector
        k = pow(2,h) - 1;           // 2 raised to the power of h - 1
        hs.insert(hs.begin(), k);   // insert at front for how I have the custom shell set up
        h ++ ;
    }
    return hs;                      // return vector of hibbard's sequence
}

#endif