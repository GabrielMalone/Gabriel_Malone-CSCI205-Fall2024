#ifndef H_FILE_SAVER
#define H_FILE_SAVER

#include <fstream>
#include <string>
#include "List.hpp"

using namespace std;

/**
 *  save data
 */
void saveData(List<int>& data, string filename){
    Node<int>* d = data.get_head();   
    int trial_num = 0;
    ofstream outFile(filename + ".txt");                                                                      
    if (outFile.is_open()){
        while (d != NULL){     
            trial_num ++ ;                                              
            outFile << trial_num << " " << d->data << "\n";
            d = d->next; 
        }                                   
    outFile << endl;                                                                          
    }  
} 

#endif

