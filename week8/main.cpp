
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / CLOSED MAPS TESTING
//------------------------------------------------------------------------------------------------------------
#include "ClosedHashTable.hpp"
#include <iostream>
#include <string>
#include <random>
#include "backend/Contact.h"
#include "backend/FileOpener.hpp"
//------------------------------------------------------------------------------------------------------------
using namespace std;

string RESET = "\033[0m";                          				                // ANSI escape code variables
string BLACK = "\033[30m";
string RED = "\033[31m";
string GREEN = "\033[32m";
string YELLOW = "\033[33m";
string BLUE = "\033[34m";
string MAGENTA = BLUE;
string CYAN = "\033[36m";
string WHITE = "\033[37m";     
                                    
int main(){
    //--------------------------------------------------------------------------------------------------------
    // SET UP FOR STRING RANDOMIZATION
    //--------------------------------------------------------------------------------------------------------
    random_device rd;                                 
    mt19937 gen(rd());
    string s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // characters
    uniform_int_distribution<> dist(0, s.length()-1);              // random index for string building in loop
    uniform_int_distribution<> rand(10, 10);                  // random length for each string to place in map
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
    //testmap.print();                                                             // print current state of map
    //--------------------------------------------------------------------------------------------------------  
    cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- "
    << RESET << endl;
    cout << GREEN <<"                      <INT>MAP DATA - using random strings for keys" << RESET << endl;    
    cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << RESET << endl;                                                                         
    cout << "Map capacity = ";
    cout << MAGENTA << testmap.map_capacity() << RESET;                             // return correct capacity
    cout << ". Is this number prime? ";
    if (testmap.is_prime(testmap.map_capacity())){
        cout << GREEN << "true" << RESET << endl;
    } else {
        cout << RED << "false" << RESET << endl;
    }
    //--------------------------------------------------------------------------------------------------------   
    cout << "Number of key/value pairs in map: ";
    cout << MAGENTA << testmap.m_size() << RESET << endl;           // return number of key/value pairs in map
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Number of used buckets in map: ";
    cout << MAGENTA << testmap.count_full() << RESET << endl;                         // how many used buckets
    //--------------------------------------------------------------------------------------------------------  
    cout << "Number of empty buckets in map: ";
    cout << MAGENTA << testmap.count_empty() << RESET << endl;                      // how many unused buckets
    //--------------------------------------------------------------------------------------------------------
    cout << "Number of empty buckets " << MAGENTA << testmap.count_empty() << RESET 
         << " + number of used buckets "<< MAGENTA << testmap.count_full() << RESET << " = capacity "
         << MAGENTA << testmap.map_capacity() << ": " << RESET;
    if (testmap.count_empty() + testmap.count_full() == testmap.map_capacity()){
        cout << GREEN << "true" << RESET << endl;
    } else {
        cout << RED << "false" << RESET << endl;
    }                                                                               // confirm numbers add up
    //--------------------------------------------------------------------------------------------------------
    cout << "Average number of collisions per bucket: ";
    cout << MAGENTA << testmap.avg_depth() << RESET << endl;        // average number of collisions per bucket
    //--------------------------------------------------------------------------------------------------------
    cout << "Highest number of collisions present in map: ";
    cout << MAGENTA << testmap.max_depth() << RESET << endl;     // test to find the most number of collisions
    //--------------------------------------------------------------------------------------------------------
    cout << "Percent buckets empty (number of buckets used vs number of pairs):  "; // how many unused buckets
    cout << MAGENTA << (double)testmap.count_full() / (double)testmap.m_size()  << RESET << endl;                                  
    //-------------------------------------------------------------------------------------------------------- 
    cout << YELLOW << "Load factor 𝜆" << RESET << " : "; 
    cout << YELLOW << (double)testmap.count_full() / (double)testmap.map_capacity()  << RESET << endl;
    //-------------------------------------------------------------------------------------------------------- 
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
    cout << "Removing " << g << " from map... ";                                                 // test removal                             
    testmap.remove(g);  
    cout << "Map now contains key " << g << ": ";                                               // confirm removal
        if (testmap.contains(g)) {
            cout << GREEN << "true" << RESET << endl;
        } else {
            cout << RED << "false" << RESET << endl;
        }     
    //--------------------------------------------------------------------------------------------------------        
    cout << "Current number of key/value pairs in map: ";
    cout << MAGENTA << testmap.m_size() << RESET << endl;           // return number of key/value pairs in map
     cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << RESET << endl; 

    //--------------------------------------------------------------------------------------------------------  
    // Create a map of 100k contacts
    //--------------------------------------------------------------------------------------------------------  
    List<Contact> contacts;                                                    // Linked list to hold contacts
    FileOpener::contactLoader("backend/contacts.txt", contacts);     // load the contacts into the linked list
    ClosedHashTable<Contact> contactMap;                                 // create a blank map of type Contact
    Node<Contact>* n = contacts.get_head();                 // iterate through the contacts in the linked list
    while (n!=NULL){
        Contact contact = n->data;                                                     // pull out the contact
        string key = contact.getPhone();                             // get the phone number to use as a key
        contactMap.put(key, contact);                // place the key and value (value being contact object)
        n = n->next;
    }

    //contactMap.print();
    cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- "
    << RESET << endl;
    cout << GREEN <<"                    <CONTACT>MAP DATA - using phone numbers as keys " << RESET << endl;    
    cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << RESET << endl;                                                                         
    cout << "Map capacity = ";
    cout << MAGENTA << contactMap.map_capacity() << RESET;                             // return correct capacity
    cout << ". Is this number prime? ";
    if (testmap.is_prime(contactMap.map_capacity())){
        cout << GREEN << "true" << RESET << endl;
    } else {
        cout << RED << "false" << RESET << endl;
    }
    //--------------------------------------------------------------------------------------------------------   
    cout << "Number of key/value pairs in map: ";
    cout << MAGENTA << contactMap.m_size() << RESET << endl;           // return number of key/value pairs in map
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Number of used buckets in map: ";
    cout << MAGENTA << contactMap.count_full() << RESET << endl;                         // how many used buckets
    //--------------------------------------------------------------------------------------------------------  
    cout << "Number of empty buckets in map: ";
    cout << MAGENTA << contactMap.count_empty() << RESET << endl;                      // how many unused buckets
    //--------------------------------------------------------------------------------------------------------
    cout << "Number of empty buckets " << MAGENTA << contactMap.count_empty() << RESET 
         << " + number of used buckets "<< MAGENTA << contactMap.count_full() << RESET << " = capacity "
         << MAGENTA << contactMap.map_capacity() << ": " << RESET;
    if (contactMap.count_empty() + contactMap.count_full() == contactMap.map_capacity()){
        cout << GREEN << "true" << RESET << endl;
    } else {
        cout << RED << "false" << RESET << endl;
    }                                                                               // confirm numbers add up
    //--------------------------------------------------------------------------------------------------------
    cout << "Average number of collisions per bucket: ";
    cout << MAGENTA << contactMap.avg_depth() << RESET << endl;        // average number of collisions per bucket
    //--------------------------------------------------------------------------------------------------------
    cout << "Highest number of collisions present in map: ";
    cout << MAGENTA << contactMap.max_depth() << RESET << endl;     // test to find the most number of collisions
    //--------------------------------------------------------------------------------------------------------
    cout << "Percent buckets empty (number of buckets used vs number of pairs):  "; // how many unused buckets
    cout << MAGENTA << (double)contactMap.count_full() / (double)contactMap.m_size()  << RESET << endl;                                  
    //-------------------------------------------------------------------------------------------------------- 
    cout << YELLOW << "Load factor 𝜆" << RESET << " : "; 
    cout << YELLOW << (double)contactMap.count_full() / (double)contactMap.map_capacity()  << RESET << endl;
    //-------------------------------------------------------------------------------------------------------- 
    cout << GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << RESET << endl; 
   



    return 0;
}