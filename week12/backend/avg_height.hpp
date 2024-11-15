#ifndef AVG_HEIGHT
#define AVG_HEIGHT

#include "ClosedHashTable.hpp"
#include "../bst_helpers.hpp/bst_data.hpp"
#include "../tests/height_test.hpp"
#include <fstream>

//----------------------------------------------------------------------------
// ITERATE THROUGH MAP AND PLACE DATA INTO TEXT FILE
//----------------------------------------------------------------------------
double avg_height(ClosedHashTable<Height_Data>& HD){
    double sum = 0;	
    for (int i = 0 ; i < HD.m_size() ; i ++ ){
        Height_Data hd = HD.get(to_string(i+1));
        sum +=(double)hd.tree_height; 
    }
    return sum / (double)HD.m_size();
}

#endif