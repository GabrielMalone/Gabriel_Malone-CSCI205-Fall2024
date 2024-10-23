#ifndef PRINTGRAPH
#define PRINTGRAPH

#include "colors.hpp"
#include "ClosedHashTable.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

ClosedHashTable<string> colorMap;
string CLEAR_SCREEN  = "\033[2J";                                                  
string CURSOR_TOP_LEFT = "\033[H";
 int speed = 5;


void makeColorShades(){
// asked chatGPT to arrange the 256 ansi colors according to hue, I removed a handful of colors I didn't like. 
int sortedAnsiCodes[] = {
    230, 190, 148, 106, 191, 64, 154, 149, 192, 112, 70, 118, 107, 150, 155, 
    193, 76, 82, 113, 156, 119, 22, 2, 28, 34, 40, 65, 10, 46, 71, 108, 77, 
    114, 83, 151, 120, 157, 194, 84, 78, 121, 47, 41, 72, 115, 85, 158, 48, 35, 
    42, 79, 122, 49, 29, 86, 36, 43, 50, 23, 6, 30, 37, 44, 66, 14, 51, 73, 
    109, 80, 116, 87, 152, 123, 159, 195, 45, 38, 31, 81, 24, 39, 74, 117, 32, 
    25, 33, 67, 110, 75, 153, 26, 27, 68, 111, 69, 17, 4, 18, 19, 20, 60, 12, 
    21, 61, 103, 62, 104, 63, 146, 105, 147, 189, 99, 98, 141, 57, 56, 97, 140, 
    135, 183, 93, 55, 92, 134, 177, 129, 54, 171, 91, 128, 165, 53, 5, 90, 127, 
    164, 96, 13, 201, 133, 139, 170, 176, 207, 182, 213, 219, 225, 200, 163, 
    126, 206, 89, 199, 169, 212, 162, 125, 198, 132, 175, 205, 218, 161, 197, 
    168, 211, 204
};
    for (int i = 0; i < 255; ++i) {
        string shade = "\033[48;5;" + to_string(sortedAnsiCodes[i])+ "m";
        colorMap.put(to_string(i), shade);
    }
}

void printTowers(vector<int>& list, int being_moved){ 
    makeColorShades();
    cout << CLEAR_SCREEN << CURSOR_TOP_LEFT;                              
    int max_height = 0;
    for (size_t i = 0 ; i < list.size(); i  ++ ){        // get current max (for max height of graph print)
        if (list[i] > max_height){
            max_height = list[i];
        }
    }
    int height = max_height;                             // this will decrement, print from top to bottom
    for (size_t j = 0 ; j < list.size(); j ++){          // iterate for duration of size of array
        for (size_t k = 0 ; k < list.size(); k ++ ){     // iterate through vector and check each value
            if (list[k] == being_moved && being_moved >= height){
                cout << Colors::YELLOW << "#" << Colors::RESET;  
            }
            else if (list[k] >= height){
                cout <<  colorMap.get(to_string(k)) + "#" + Colors::RESET;
            }
            else {                                       // print column
                cout << " "; 
            }                                            // if can't print yet, print blank
        }
        cout << endl;                                    // start next row
        height -- ;                                      // move down
    }
    this_thread::sleep_for(chrono::milliseconds(speed)); // speed of display of algo
}

#endif