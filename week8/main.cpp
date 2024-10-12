
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / CLOSED MAPS TESTING
//------------------------------------------------------------------------------------------------------------
#include "ClosedHashTable.hpp"
#include <iostream>
#include <string>
#include <random>
#include <cassert>
//------------------------------------------------------------------------------------------------------------
using namespace std;

string RESET = "\033[0m";                          				                // ANSI escape code variables
string BLACK = "\033[30m";
string RED = "\033[31m";
string GREEN = "\033[32m";
string YELLOW = "\033[33m";
string BLUE = "\033[34m";
string MAGENTA = "\033[35m";
string CYAN = "\033[36m";
string WHITE = "\033[37m";     
                                    
int main(){
    //--------------------------------------------------------------------------------------------------------
    // SET UP FOR STRING RANDOMIZATION
    //--------------------------------------------------------------------------------------------------------
    random_device rd;                                 
    mt19937 gen(rd());
    string s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()1234567890><][{}"; // characters
    uniform_int_distribution<> dist(0, s.length()-1);              // random index for string building in loop
    uniform_int_distribution<> rand(1, 100);                  // random length for each string to place in map
    //--------------------------------------------------------------------------------------------------------
    ClosedHashTable<int>testmap; // initialize an empty map. loop below will test resize functionality as well
    //--------------------------------------------------------------------------------------------------------
    string str = "";
    //--------------------------------------------------------------------------------------------------------
    // RANDOM STRING BUILDER
    //--------------------------------------------------------------------------------------------------------
    for (int i = 0 ; i < 200000 ; i ++ ){                     // how many times to place a string into the map
        str = "";                                                                       // reset for each loop
        int rand_len = rand(gen);                                        // select string length for this loop
        for (int j = 0 ; j < rand_len ; j ++ ){                                            // build the string
            str += s[dist(gen)];                           // select letter from random position in 's' string
        }
        testmap.put(str, i);                // place the random string in the map as a key with , 'i' as value
    }
    //--------------------------------------------------------------------------------------------------------
    // CONSTANT VARIABLE 
    //--------------------------------------------------------------------------------------------------------
    string g = MAGENTA + "gabe" + RESET; // this constant can be used to test features needing known key value
    int myint = 100;
    testmap.put(g, myint);
    string goob = MAGENTA + "goob" + RESET;
    //--------------------------------------------------------------------------------------------------------
    testmap.print();                                                             // print current state of map
    //--------------------------------------------------------------------------------------------------------                                                                       
    cout << "Current map capacity = ";
    cout << MAGENTA << testmap.map_capacity() << RESET;                             // return correct capacity
    cout << ". Is this number prime? ";
    if (testmap.is_prime(testmap.map_capacity())){
        cout << GREEN << "true" << RESET << endl;
    } else {
        cout << RED << "false" << RESET << endl;
    }
    cout << "Map contains key " << g << ": ";                                                 // test contains
         if (testmap.contains(g)) {
            cout << GREEN << "true" << RESET << endl;
         } else {
            cout << RED << "false" << RESET << endl;
         }
    
    cout << "Map contains key " << goob << ": ";
         if (testmap.contains(goob)) {
            cout << GREEN << "true" << RESET << endl;
         } else {
            cout << RED << "false" << RESET << endl;
         } 
    //--------------------------------------------------------------------------------------------------------
    cout << "Getting value from key " << g << ": "<< testmap.get(g) << endl;                       // test get
    //--------------------------------------------------------------------------------------------------------        
    cout << "Current number of key/value pairs in map: ";
    cout << MAGENTA << testmap.m_size() << RESET << endl;           // return number of key/value pairs in map
    //--------------------------------------------------------------------------------------------------------
    cout << "Removing " << g << " from map. ";                                                 // test removal                             
    testmap.remove(g);  
    cout << "Map contains key " << g << ": ";                                               // confirm removal
        if (testmap.contains(g)) {
            cout << GREEN << "true" << RESET << endl;
        } else {
            cout << RED << "false" << RESET << endl;
        }     
    //--------------------------------------------------------------------------------------------------------   
    cout << "Current number of key/value pairs in map: ";
    cout << MAGENTA << testmap.m_size() << RESET << endl;           // return number of key/value pairs in map
    cout << testmap.count_empty() << endl;                                          // how many unused buckets
    cout << testmap.count_full() << endl;                                             // how many used buckets
    cout << testmap.count_empty() + testmap.count_full() << endl;         // see that these add up to capacity
    cout << testmap.max_depth() << endl;                         // test to find the most number of collisions
    cout << testmap.avg_depth() << endl;                            // average number of collisions per bucket

    return 0;
}