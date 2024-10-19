
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / 
//------------------------------------------------------------------------------------------------------------
#include "hash_tables/OpenHashTable.hpp"
#include "hash_tables/ClosedHashTable.hpp"
#include "backend/List.hpp"
#include "backend/Contact.h"
#include "backend/FileOpener.hpp"
#include "backend/colors.hpp"
#include <iostream>
#include <string>

OpenHashTable<int>testmap;  
ClosedHashTable<int>testmap2;  
int counter = 0;
int sizer = 10;

int main(){

    //--------------------------------------------------------------------------------------------------------
    // continuously fill, delete with increasing number of items forever....
    //--------------------------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------------------------
    // OPEN MAP LOOP TESTING
    //--------------------------------------------------------------------------------------------------------

    while (true){
        sizer++;
        string str = "";
        for (int i = 1 ; i < sizer ; i ++ ){      
            str = "";
            str += to_string(i);                
            testmap[str] = i;                          
        }
        counter = 0;
        testmap.print();
        for (int i = 1 ; i < sizer ; i ++ ){      
            str = "";
            str += to_string(i);              
            counter ++ ;
            cout 
                << counter 
                << " - key: "
                << str 
                << " value: "
                << testmap.get(str)
                << endl;
        }
        counter = 0;
        for (int i = 1 ; i < sizer ; i ++ ){    
        str = "";
        str += to_string(i);              
        counter ++ ;
            cout 
                << counter 
                << " - removing key: " 
                << str
                << endl;
            testmap.remove(str);
        }
    }

    //--------------------------------------------------------------------------------------------------------
    // CLOSED MAP LOOP TESTING
    //--------------------------------------------------------------------------------------------------------

    while (true){
        sizer *= 2;;
        string str = "";
        for (int i = 0 ; i < sizer ; i ++ ){    
            str = "";
            str += to_string(i);              
            testmap2[str] = i;                            
        }
        counter = 0;
        testmap2.print();
        for (int i = 0 ; i < sizer ; i ++ ){     
            str = "";
            str += to_string(i);              
            counter ++ ;
            cout 
                << counter 
                << " - key: "
                << str 
                << " value: "
                << testmap2.get(str)
                << endl;
        }
        counter = 0;
        for (int i = 0 ; i < sizer ; i ++ ){    
        str = "";
        str += to_string(i);             
        counter ++ ;
            cout 
                << counter 
                << " - removing key: " 
                << str
                << endl;
            testmap2.remove(str);
        }
    }
    return 0;
}