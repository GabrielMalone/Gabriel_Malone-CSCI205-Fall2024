
//-----------------------------------------------------------------------------------
// Gabriel Malone
//-----------------------------------------------------------------------------------
#ifndef PRINTGRAPH
#define PRINTGRAPH
//-----------------------------------------------------------------------------------
#include "colors.hpp"
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "List.hpp"
#include "histo_info.hpp"
#include <vector>
//-----------------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------------
unordered_map<int, string> colorMap;              // to set the color for each number
string CLEAR_SCREEN  = "\033[2J";                             // for animation effect                                              
string CURSOR_TOP_LEFT = "\033[H";                            // for animation effect 
 int speed = 5;       // print speed, smaller = faster but can cause screen to glitch
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// 256 Colors arranged by hue, removed some of the reds and grays
//-----------------------------------------------------------------------------------
void makeColorShades(){
    vector<int> sortedAnsiCodes = {
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
    //------------------------------------------------------------------------------
    // Fill the map with colors and their number key
    //------------------------------------------------------------------------------
    for (size_t i = 0 ; i < sortedAnsiCodes.size() ; ++i) {
        string shade = "\033[48;5;" + to_string(sortedAnsiCodes[i])+ "m";
        colorMap.emplace(i, shade);
    }
}
//-----------------------------------------------------------------------------------
// 'Bar Graph' representation of an array printing logic 
//-----------------------------------------------------------------------------------
void printTowers(List<histo_info>& list){ 
    string CLEAR_SCREEN  = "\033[2J";                         // for animation effect                                              
    string CURSOR_TOP_LEFT = "\033[H";                        // for animation effect 
    makeColorShades();                                       // get the colors set up                           
    int max_height = 0;
    for (size_t i = 0 ; i < list.length(); i  ++ ){                // get current max 
        if (list[i].frequency > max_height){       // (for max height of graph print)
            max_height = list[i].frequency;
        }
    }
    int height = max_height;
    for (int j = 0 ; j < max_height; j ++){                  // iterate size of array
        for (size_t k = 0 ; k < list.length(); k ++ ){      // iterate through vector 
            char cur_char = list[k].letter;
            if (list[k].frequency >= height){ // tall enough to print yet? (top down)
                cout <<  " " << colorMap[k] + Colors::BLACK + cur_char + "     " 
                +  Colors::RESET ;
            }
            else {                                       
                cout << "       ";                // if can't print yet, print blank
            }                                            
        }
        cout << endl;
        height -- ;                                                     // move down
    }
}

#endif