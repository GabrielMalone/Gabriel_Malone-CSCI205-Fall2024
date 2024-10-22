#ifndef VALIDATESORT
#define VALIDATESORT

#include <vector>
#include <iostream>

//----------------------------------------------------------------------------
// CONFIRM VALIDITY OF SORT
//----------------------------------------------------------------------------
bool sorted(std::vector<int>& vector){
    //------------------------------------------------------------------------
    for (int i = 1 ; i < vector.size(); i ++){
        int prev_item = vector[i-1];
        int cur_item = vector[i];
        if (prev_item > cur_item){
            std::cout <<  Colors::RED 
                 << prev_item
                 << " > "
                 << cur_item
                 << " sort failed" 
                 << Colors::RESET 
                 << std::endl;
            return false;
        }
    }
   //---------------------------------------------------------------------------
   std::cout << Colors::GREEN 
         << "sort successful" 
         << Colors::RESET 
         << std::endl;
    return true;
    //---------------------------------------------------------------------------
}

#endif