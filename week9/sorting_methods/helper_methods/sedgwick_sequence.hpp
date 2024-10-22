#ifndef SEDGWICK
#define SEDGWICK

#include <vector>
#include <cmath>
#include "../reverseBubbleSort.hpp"

std::vector<int> sedgwick (int size){
    //---------------------------------------------------------------------------
    std::vector<int>s1;
    std::vector<int>s2;  
    std::vector<int>s3; 
    //---------------------------------------------------------------------------
    int k = 0;
    int h = 1;                                                  // starting value
    //---------------------------------------------------------------------------
    while (k < size){                                           // make new numbers in the sequence until the number is greater than the size of the vector
        k = 9 * (pow(4,h)-pow(2,h)) + 1;       
        s1.insert(s1.begin(), k);                               // insert at front for how I have the custom shell set up
        h ++ ;
    }
    //---------------------------------------------------------------------------
    k = 0;
    h = 1;                                                      // starting value
    //---------------------------------------------------------------------------
    while (k < size){                                           // make new numbers in the sequence until the number is greater than the size of the vector
        k = (pow(2,(h+2)) * (pow(2,(h+2)) - 3)) + 1;            // 2 raised to the power of h - 1
        s2.insert(s2.begin(), k);                               // insert at front for how I have the custom shell set up
        h ++ ;
    }
    //---------------------------------------------------------------------------
    for (int i = 0 ; i < s1.size() ; i ++){
        s3.insert(s3.begin(), s1[i]);
    }
    for (int j = 0 ; j < s2.size() ; j ++){
        s3.insert(s3.begin(), (s2[j]));
    }
    //---------------------------------------------------------------------------
    reverseBubbleSort(s3, 'r');
    s3.emplace_back(1);                                          // make sure 1 present for final comparisons
    //---------------------------------------------------------------------------
    return s3;
}

#endif