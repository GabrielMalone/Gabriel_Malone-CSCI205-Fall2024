#ifndef SAVESEARCH
#define SAVESEARCH

#include "ClosedHashTable.hpp"
#include "sort_data.hpp"
#include <fstream>

//----------------------------------------------------------------------------
// ITERATE THROUGH MAP AND PLACE DATA INTO TEXT FILE
//----------------------------------------------------------------------------
void saveSortingData(ClosedHashTable<sortData>& SortDataMap, string sortMethod){
    ofstream f ("data/" + sortMethod + ".txt");	
    for (int i = 0 ; i < SortDataMap.m_size() ; i ++ ){
        sortData sd = SortDataMap.get(to_string(i+1));
        f << i + 1;
        f << " ";
        f << sd.order_type;
        f << " ";
        f << sd.array_size;
        f << " ";
        f << sd.array_accesses + sd.comparisons;  // combine all the operations
        f << endl;
    }
}

#endif