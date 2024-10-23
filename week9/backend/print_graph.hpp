#ifndef PRINTGRAPH
#define PRINTGRAPH

#include <iostream>
#include <chrono>
#include <thread>

string CLEAR_SCREEN  = "\033[2J";                                                  
string CURSOR_TOP_LEFT = "\033[H";

using namespace std;

void printTowers(vector<int>& list){ 
    int speed = 50;
    cout << CLEAR_SCREEN << CURSOR_TOP_LEFT;                              
    int max_height = 0;
    for (size_t i = 0 ; i < list.size(); i  ++ ){          // get current max (for max height of graph print)
        if (list[i] > max_height){
            max_height = list[i];
        }
    }
    int height = max_height;                             // this will decrement, print from top to bottom
    for (size_t j = 0 ; j < list.size(); j ++){          // iterate for duration of size of array
        for (size_t k = 0 ; k < list.size(); k ++ ){     // iterate through vector and check each value
            if (list[k] >= height){
                cout << "#";                             // print column
            } else {
                cout << " ";                             // if can't print yet, print blank
            }
        }
        cout << endl;                                    // start next row
        height -- ;                                      // move down
    }
    this_thread::sleep_for(chrono::milliseconds(speed)); // speed of display of algo
}

#endif