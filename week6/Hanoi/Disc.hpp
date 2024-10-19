// Gabriel Malone // CSCI205 // WEEK 6
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "../backend/ArrayList.hpp"

#ifndef Disc_H
#define Disc_H

#include <string>

//------------------------------------------------------------------------------
// Colors for the disc object being created
//------------------------------------------------------------------------------
string RESET = "\033[0m";                          // ANSI escape code variables
string BLACK = "\033[30m";
string RED = "\033[31m";
string GREEN = "\033[32m";
string YELLOW = "\033[33m";
string BLUE = "\033[34m";
string MAGENTA = "\033[35m";
string CYAN = "\033[36m";
string WHITE = "\033[37m";
//------------------------------------------------------------------------------
// Array Class to hold the colors
//------------------------------------------------------------------------------
A_List<string> COLORS;

using namespace std;
//------------------------------------------------------------------------------
// DISC Class
//------------------------------------------------------------------------------
class Disc{
    private:
        string disc_color;
        int disc_num;                                       
    public:
        /**
         * Default constructor
         */
        Disc(){
            this->disc_num = 0;                            
        }
        /**
         * Overloaded constructor
         */
        Disc(int num){
            COLORS.insert(BLACK);                          // load up the colors
            COLORS.insert(RED);
            COLORS.insert(GREEN);
            COLORS.insert(YELLOW);
            COLORS.insert(BLUE);
            COLORS.insert(MAGENTA);
            COLORS.insert(WHITE);
            this->disc_num = num;                           // set width at construction
            this->disc_color = COLORS.get(disc_num%7);      // wrap around indexing 
        }                                                   // set color via disc size
        int get_disc_num(){                                 
            return this->disc_num;
        }
        string getColor(){
            return this->disc_color;
        }
        //------------------------------------------------------------------------------
        // Print discs with colors, padding is dynamic so always the same width output
        //------------------------------------------------------------------------------
        void print_disc(){              // THIS ONLY WORKS WITH ODDLY SIZED DISC NUMBERS
            int limit = 40;
            if (disc_num % 2 == 0){
                disc_num ++ ;
            }
            int padding = 20;      // how wide to make the graphical ouput for each disc 
            if ((padding * 2 ) + disc_num > limit)
            while ((padding * 2 ) + disc_num > limit){
                padding -- ;
            }
            if ((padding * 2 ) + disc_num < limit)
            while ((padding * 2 ) + disc_num < limit){
                padding ++ ;
            }
            cout  << "[ "
             << setw(padding)  << setfill(' ')  << ""
             << this->disc_color
             << setw(disc_num) << setfill('#')  << ""
             << RESET
             << setw(padding)  << setfill(' ')  << ""
             << " ] ";
        }
};

#endif