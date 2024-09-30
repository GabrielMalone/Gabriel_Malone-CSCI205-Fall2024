// Gabriel Malone // CSCI205 // WEEK 6
#include <iostream>
#include <iomanip>

#ifndef Disc_H
#define Disc_H

using namespace std;

class Disc{
    private:
        int disc_num;
    public:

        Disc(){
            this->disc_num = 0;
        }

        Disc(int num){
            this->disc_num = num;
        }
        int get_disc_num(){
            return this->disc_num;
        }
        void print_disc(){
            cout 
            << setw(20 - disc_num)
            << "+";
            for (int i = 0 ; i < disc_num * 2 ; i ++){
                cout << "-" ;
            }
            cout 
            << "+"
            << endl;
        }
};

#endif