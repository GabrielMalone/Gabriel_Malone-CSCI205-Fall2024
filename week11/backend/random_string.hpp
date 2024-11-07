#ifndef RANDOM_STRING
#define RANDOM_STRING

#include <random>

using namespace std;
    
    string get_random_string(int size){
        string options = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        random_device rd;               
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1,  options.size()-1); 
        string histo_string = "";
        for (int i = 0 ; i < size ; i ++ ){
            histo_string += options[dist(gen)];
        }
        return histo_string;
    }


#endif