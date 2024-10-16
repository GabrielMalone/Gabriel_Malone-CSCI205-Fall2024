
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / CLOSED MAPS TESTING
//------------------------------------------------------------------------------------------------------------
#include "hash_tables/ClosedHashTable.hpp"
#include <iostream>
#include <string>
#include <random>
#include "backend/Contact.h"
#include "backend/FileOpener.hpp"
#include "backend/colors.hpp"

//------------------------------------------------------------------------------------------------------------
using namespace std;
                                    
int main(){
    //--------------------------------------------------------------------------------------------------------
    // SET UP FOR STRING RANDOMIZATION
    //--------------------------------------------------------------------------------------------------------
   
    random_device rd;                                 
    mt19937 gen(rd());
    string s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";                           // characters
    uniform_int_distribution<> dist(0, s.length()-1);              // random index for string building in loop
    uniform_int_distribution<> rand(10, 500);                  // random length for each string to place in map
    //--------------------------------------------------------------------------------------------------------
    ClosedHashTable<int>testmap; // initialize an empty map. loop below will test resize functionality as well
    //--------------------------------------------------------------------------------------------------------
    // CONSTANT VARIABLE 
    //--------------------------------------------------------------------------------------------------------
    string g = Colors::MAGENTA + "gabe" + Colors::RESET; //constant used to test features with known key value
    int myint = 100;
    testmap.put(g, myint);
    string goob = Colors::MAGENTA + "goob" + Colors::RESET;
    //--------------------------------------------------------------------------------------------------------
    string str = "";
    //--------------------------------------------------------------------------------------------------------
    // RANDOM STRING BUILDER
    //--------------------------------------------------------------------------------------------------------
    for (int i = 0 ; i < 100000 ; i ++ ){                     // how many times to place a string into the map
        str = "";                                                                       // reset for each loop
        int rand_len = rand(gen);                                        // select string length for this loop
        for (int j = 0 ; j < rand_len ; j ++ ){                                            // build the string
            str += s[dist(gen)];                           // select letter from random position in 's' string
        }
        testmap.put(str, i);                // place the random string in the map as a key with , 'i' as value
    }
    //--------------------------------------------------------------------------------------------------------
    // PRINT CURRENT STATE OF MAP
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------
    testmap.print();                                                             // print current state of map
    //--------------------------------------------------------------------------------------------------------  
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- "
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" CLOSED<INT>MAP DATA - using random strings for keys" << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << Colors::RESET << endl;
    //--------------------------------------------------------------------------------------------------------
    // SHOW CURRENT MAP CAPACITY
    //--------------------------------------------------------------------------------------------------------                                                                         
    cout << "Map capacity = ";
    cout << Colors::MAGENTA << testmap.map_capacity() << Colors::RESET;           // return correct capacity
    //--------------------------------------------------------------------------------------------------------
    // IS THIS NUMBER PRIME?
    //--------------------------------------------------------------------------------------------------------
    cout << ". Is this number prime? ";
    if (testmap.is_prime(testmap.map_capacity())){
        cout << Colors::GREEN << "true" << Colors::RESET << endl;
    } else {
        cout << Colors::RED << "false" << Colors::RESET << endl;
    }
    //--------------------------------------------------------------------------------------------------------
    // OTHER METRICS
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------   
    cout << "Number of key/value pairs in map: ";
    cout << Colors::MAGENTA << testmap.m_size() << Colors::RESET << endl;  // return number of key/value pairs 
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Number of used buckets in map: ";
    cout << Colors::MAGENTA << testmap.count_full() << Colors::RESET << endl;         // how many used buckets
    //--------------------------------------------------------------------------------------------------------  
    cout << "Number of empty buckets in map: ";
    cout << Colors::MAGENTA << testmap.count_empty() << Colors::RESET << endl;      // how many unused buckets
    //--------------------------------------------------------------------------------------------------------
    cout << "Number of empty buckets " 
         << Colors::MAGENTA << testmap.count_empty() 
         << Colors::RESET 
         << " + number of used buckets "
         << Colors::MAGENTA << testmap.count_full() 
         << Colors::RESET << " = capacity "
         << Colors::MAGENTA << testmap.map_capacity() 
         << ": " 
         << Colors::RESET;
    if (testmap.count_empty() + testmap.count_full() == testmap.map_capacity()){
        cout << Colors::GREEN << "true" << Colors::RESET << endl;
    } else {
        cout << Colors::RED << "false" << Colors::RESET << endl;
    }                                                                                // confirm numbers add up
    //--------------------------------------------------------------------------------------------------------
    cout << "Average number of collisions per bucket: ";            // average number of collisions per bucket
    cout << Colors::MAGENTA << testmap.avg_depth() << Colors::RESET << endl;  
    //--------------------------------------------------------------------------------------------------------
    cout << "Highest number of collisions present in map: ";     // test to find the most number of collisions
    cout << Colors::MAGENTA << testmap.max_depth() << Colors::RESET << endl;     
    //--------------------------------------------------------------------------------------------------------
    cout << "Percent buckets empty (number of buckets used vs number of pairs):  "; // how many unused buckets
    cout << Colors::MAGENTA << (double)testmap.count_full() / (double)testmap.m_size()  
         << Colors::RESET << endl;        
    //--------------------------------------------------------------------------------------------------------
    // LOAD FACTOR
    //--------------------------------------------------------------------------------------------------------                          
    //-------------------------------------------------------------------------------------------------------- 
    cout << Colors::YELLOW << "Load factor 𝜆" << Colors::RESET << " : "; 
    cout << Colors::YELLOW << (double)testmap.count_full() / (double)testmap.map_capacity()  
         << Colors::RESET << endl;
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Map contains key " << g << ": ";                                                 // test contains
         if (testmap.contains(g)) {                                        // placed in map, should be present
            cout << Colors::GREEN << "true" << Colors::RESET << endl;
         } else {
            cout << Colors::RED << "false" << Colors::RESET << endl;
         }
    //--------------------------------------------------------------------------------------------------------
    // TESTING FIND AND CONTAINS
    //--------------------------------------------------------------------------------------------------------  
    //-------------------------------------------------------------------------------------------------------- 
    cout << "It took " << Colors::GREEN << testmap.search_count() << Colors::RESET   // test search complexity
         << " operations to find " << g << endl;
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Map contains key " << goob << ": ";
         if (testmap.contains(goob)) {                              // never placed in map should return false
            cout << Colors::GREEN << "true" << Colors::RESET << endl;
         } else {
            cout << Colors::RED << "false" << Colors::RESET << endl;
         }
    //--------------------------------------------------------------------------------------------------------
    // TIME COMPLEXITY DATA
    //--------------------------------------------------------------------------------------------------------   
    //-------------------------------------------------------------------------------------------------------- 
    cout << "It took " << Colors::GREEN << testmap.search_count() << Colors::RESET   // test search complexity
         << " operations to find " << goob << " not present" << endl;
    //--------------------------------------------------------------------------------------------------------
    cout << "Getting value from key " << g << ": " << testmap.get(g) << endl;                      // test get
    //--------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------
    // TESTING REMOVE
    //--------------------------------------------------------------------------------------------------------  
    cout << "Removing " << g << " from map... ";                                               // test removal                             
    testmap.remove(g);  
    cout << "Map now contains key " << g << ": ";                                           // confirm removal
        if (testmap.contains(g)) {
            cout << Colors::GREEN << "true" << Colors::RESET << endl;
        } else {
            cout << Colors::RED << "false" << Colors::RESET << endl;
        }
    //--------------------------------------------------------------------------------------------------------
    // MISC DATA
    //--------------------------------------------------------------------------------------------------------       
    //--------------------------------------------------------------------------------------------------------        
    cout << "Current number of key/value pairs in map: ";           // return number of key/value pairs in map
    cout << Colors::MAGENTA << testmap.m_size() <<Colors::RESET << endl;   
    //--------------------------------------------------------------------------------------------------------
    cout << "number of resizes to fill this map: ";                      // return number of resizes completed
    cout << Colors::MAGENTA << testmap.times_resized() <<Colors::RESET << endl;   
    //--------------------------------------------------------------------------------------------------------            
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << Colors::RESET << endl; 


    //--------------------------------------------------------------------------------------------------------  
    // TESTING WITH CONTACT OBJECTS  / Create a map of 100k contacts
    //--------------------------------------------------------------------------------------------------------  
    // List<Contact> contacts;                                                    // Linked list to hold contacts
    // FileOpener::contactLoader("backend/contacts.txt", contacts);     // load the contacts into the linked list
    // ClosedHashTable<Contact> contactMap;                                 // create a blank map of type Contact
    // Node<Contact>* n = contacts.get_head();                 // iterate through the contacts in the linked list
    // while (n != NULL){
    //     Contact contact = n->data;                                                     // pull out the contact
    //     string key = contact.getPhone();                               // get the phone number to use as a key
    //     contactMap.put(key, contact);                  // place the key and value (value being contact object)
    //     n = n->next;
    // }

    // //contactMap.print();
    // cout << Colors::GREEN 
    // <<"--------------------------------------------------------------------------------------------------- "
    // << Colors::RESET << endl;
    // cout << Colors::GREEN <<" CLOSED<CONTACT>MAP DATA - using phone numbers as keys " << Colors::RESET << endl;    
    // cout << Colors::GREEN 
    // <<"--------------------------------------------------------------------------------------------------- " 
    // << Colors::RESET << endl;                                                                         
    // cout << "Map capacity = ";
    // cout << Colors::MAGENTA << contactMap.map_capacity() << Colors::RESET;        // return correct capacity
    // cout << ". Is this number prime? ";
    // if (testmap.is_prime(contactMap.map_capacity())){
    //     cout << Colors::GREEN << "true" << Colors::RESET << endl;
    // } else {
    //     cout << Colors::RED << "false" << Colors::RESET << endl;
    // }
    // //--------------------------------------------------------------------------------------------------------   
    // cout << "Number of key/value pairs in map: ";                   // return number of key/value pairs in map
    // cout << Colors::MAGENTA << contactMap.m_size() << Colors::RESET << endl;        
    // //-------------------------------------------------------------------------------------------------------- 
    // cout << "Number of used buckets in map: ";
    // cout << Colors::MAGENTA << contactMap.count_full() << Colors::RESET << endl;      // how many used buckets
    // //--------------------------------------------------------------------------------------------------------  
    // cout << "Number of empty buckets in map: ";
    // cout << Colors::MAGENTA << contactMap.count_empty() << Colors::RESET << endl;   // how many unused buckets
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Number of empty buckets " 
    //      << Colors::MAGENTA 
    //      << contactMap.count_empty() 
    //      << Colors::RESET 
    //      << " + number of used buckets "
    //      << Colors::MAGENTA << contactMap.count_full() 
    //      << Colors::RESET << " = capacity "
    //      << Colors::MAGENTA << contactMap.map_capacity() << ": " << Colors::RESET;
    // if (contactMap.count_empty() + contactMap.count_full() == contactMap.map_capacity()){
    //     cout << Colors::GREEN << "true" << Colors::RESET << endl;
    // } else {
    //     cout << Colors::RED << "false" << Colors::RESET << endl;
    // }                                                                                // confirm numbers add up
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Average number of collisions per bucket: ";            // average number of collisions per bucket
    // cout << Colors::MAGENTA << contactMap.avg_depth() << Colors::RESET << endl;     
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Highest number of collisions present in map: ";     // test to find the most number of collisions
    // cout << Colors::MAGENTA << contactMap.max_depth() << Colors::RESET << endl;  
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Percent buckets empty (number of buckets used vs number of pairs):  "; // how many unused buckets
    // cout << Colors::MAGENTA << (double)contactMap.count_full() / (double)contactMap.m_size()  
    //      << Colors::RESET << endl;                                  
    // //-------------------------------------------------------------------------------------------------------- 
    // cout << Colors::YELLOW << "Load factor 𝜆" << Colors::RESET << " : "; 
    // cout << Colors::YELLOW << (double)contactMap.count_full() / (double)contactMap.map_capacity()  
    //      << Colors::RESET << endl;
    // //-------------------------------------------------------------------------------------------------------- 
    // cout << Colors::GREEN 
    // <<"--------------------------------------------------------------------------------------------------- " 
    // << Colors::RESET << endl; 

    return 0;
}