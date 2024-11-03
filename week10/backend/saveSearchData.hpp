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
        f << i + 1;                                             // trial number
        f << " ";
        f << sd.order_type;                                 // array order type
        f << " ";
        f << sd.array_size;                                       // array size
        f << " ";    
        f << sd.array_accesses;
        f << " ";
        f << sd.comparisons;
        f << " ";
        f << sd.max_depth;                                  // recursion recorder
        f << endl;
    }
}

#endif