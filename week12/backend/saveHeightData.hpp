#ifndef SAVEHEIGHT
#define SAVEHEIGHT

#include "ClosedHashTable.hpp"
#include "../bst_helpers.hpp/bst_data.hpp"
#include "../tests/height_test.hpp"
#include <fstream>

//----------------------------------------------------------------------------
// ITERATE THROUGH MAP AND PLACE DATA INTO TEXT FILE
//----------------------------------------------------------------------------
void saveHeightData(ClosedHashTable<Height_Data>& HD, string height_type){
    ofstream f ("test_data/" + height_type + ".txt");	
    for (int i = 0 ; i < HD.m_size() ; i ++ ){
        Height_Data hd = HD.get(to_string(i+1));
        f << hd.trial_method;                               
        f << " ";
        f << hd.trial_num;                     
        f << " ";
        f << hd.tree_height; 
        f << " ";
        f << endl;
    }
}

#endif