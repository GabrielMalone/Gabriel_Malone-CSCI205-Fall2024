#ifndef SAVESEARCH
#define SAVESEARCH

#include "ClosedHashTable.hpp"
#include "../bst_helpers.hpp/bst_data.hpp"
#include <fstream>

//----------------------------------------------------------------------------
// ITERATE THROUGH MAP AND PLACE DATA INTO TEXT FILE
//----------------------------------------------------------------------------
void saveSortingData(ClosedHashTable<searchData>& SortDataMap, string sortMethod, double ideal_avg, double avg){
    ofstream f ("test_data/" + sortMethod + ".txt");	
    for (int i = 0 ; i < SortDataMap.m_size() ; i ++ ){
        searchData sd = SortDataMap.get(to_string(i));
        f << i + 1;                                             // trial number
        f << " ";
        f << sd.order_type;                                 // array order type
        f << " ";
        f << sd.tree_nodes;                       // number of nodes in the tree
        f << " ";
        f << sd.inserts; // number of operations to place a random value in tree
        f << " ";
        f << sd.average_inserts;
        f << " ";
        f << ideal_avg;
        f << " ";
        f << avg;
        f << endl;
    }
}

#endif