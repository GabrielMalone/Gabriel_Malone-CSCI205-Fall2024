
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / CLOSED MAPS TESTING
//------------------------------------------------------------------------------------------------------------
#include "hash_tables/OpenHashTable.hpp"
#include "hash_tables/ClosedHashTable.hpp"
#include "backend/List.hpp"
#include <iostream>
#include <string>
#include <random>
#include "backend/Contact.h"
#include "backend/FileOpener.hpp"
#include "backend/colors.hpp"

//------------------------------------------------------------------------------------------------------------
using namespace std;

string goob = Colors::MAGENTA + "goob" + Colors::RESET;                                    
string name;
int val;

                                    
int main(){

    //--------------------------------------------------------------------------------------------------------
    // SET UP FOR STRING RANDOMIZATION
    //--------------------------------------------------------------------------------------------------------
    int count = 0;
    int problem_size = 100;
    cout << "-----------------------------" << endl;
    cout << "   OPEN MAP STRESS TESTING"    << endl;
    cout << "-----------------------------" << endl;


    cout << "enter your key: ";
    cin >> name;
    cout << endl;

    cout << "enter your value (int): ";
    cin >> val;
    cout << endl;

    string g = Colors::RED + name + Colors::RESET; //constant used to test features with known key value
  
    
    cout << "enter problem size: "; 
    cin >> problem_size; 
    cout << endl;
    cout << "creating map..." << endl;
    OpenHashTable<int>testmap;   
    cout << "current map size: " << testmap.m_size() << endl;
    //ClosedHashTable<int>testmap;  
    cout << "fillig map with keys and values..." << endl;
    List<string>keyHolder;
   
    testmap.put(g, val);
    keyHolder.insert(g);

    string str = "";
    for (int i = 0 ; i < problem_size ; i ++ ){               // how many times to place a string into the map
        str = "";
        str += to_string(i);                 // or can just test with numbers if you want for easier debugging
        testmap.put(str, i);                // place the random string in the map as a key with , 'i' as value
        keyHolder.insert(str);                      
    }
    int wait;
    cout << "current map size: " << testmap.m_size() << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Map filled.  press 1 then enter to view map"                                      << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    testmap.print();
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Stress test 'get' for every key in map. press 1 then enter to being"              << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    Node<string>* n = keyHolder.get_head();
    count = 0;
    while (n != NULL){
        count ++ ;
        string key = n->data;
        cout 
             << count 
             << " - key: "
             << key 
             << " value: "
             << testmap.get(key)
             << endl;
        n = n->next;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Stress test 'contains' for every key in map. press 1 then enter to being"   << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    Node<string>* q = keyHolder.get_head();
    count = 0;
    while (q != NULL){
        string key = q->data;
        if (! testmap.contains(key) ){
            throw out_of_range("contains error round 1");
        }
        count ++ ;
        cout 
            << count
            << " - map contains key:  "
            << key
            << endl;
        q = q->next;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Stress test 'remove' for every key in map. press 1 then enter to being"     << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    count = 0;
    Node<string>* p = keyHolder.get_head();
    while (p != NULL){
        string key = p->data;
        count ++ ;
        cout << count 
             << " - removing key: " 
             << key
             << endl;
        testmap.remove(key);
        p = p->next;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Stress test 'contains' again to check for false positives. press 1 then enter to begin."   << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    Node<string>* r = keyHolder.get_head();
    count = 0;
    while (r != NULL){
        string key = r->data;
        if (testmap.contains(key) ){
            throw out_of_range("false pisitive round 1");
        }
        count ++ ;
        cout 
            << count
            << " - key:  "
            << key
            << " not found"
            << endl; 
        r = r->next;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "print map to confirm empty. press 1 then enter to begin"                          << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cin >> wait;
    testmap.print();
    cout << "current map size: " << testmap.m_size() << endl;
   

//----------------------------------------------------------------------------------------------------------

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "loop testing"                                                                     << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "repeat those same fill, get, delete tests on the same map for how many loops?";
    int loops;
    cin >> loops;
    for (int j = 0 ; j < loops ; j ++){
        List<string>keyHolder2; // reset key holder
        for (int i = 0 ; i < problem_size ; i ++ ){              
            str = "";
            str += to_string(i);                
            testmap.put(str, i);              
            keyHolder2.insert(str);                      
        }
        cout << "current map size: " << testmap.m_size() << endl;
        testmap.print();
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Stress test 'get' for every key in map. press 1 then enter to begin"        << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        Node<string>* n = keyHolder2.get_head();
        count = 0;
        while (n != NULL){
            count ++ ;
            string key = n->data;
            cout 
                << count 
                << " - key: "
                << key 
                << " value: "
                << testmap.get(key)
                << endl;
            n = n->next;
        }
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Stress test 'contains' for every key in map. press 1 then enter to begin"   << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        Node<string>* q = keyHolder2.get_head();
        count = 0;
        while (q != NULL){
            string key = q->data;
            if (! testmap.contains(key) ){
                throw out_of_range("contains error round 1");
            }
            count ++ ;
            cout 
                << count
                << " - map contains key:  "
                << key
                << endl;
            q = q->next;
        }
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Stress test 'remove' for every key in map. press 1 then enter to begin"     << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        count = 0;
        Node<string>* p = keyHolder2.get_head();
        while (p != NULL){
            string key = p->data;
            count ++ ;
            cout << count 
                << " - removing key: " 
                << key
                << endl;
            testmap.remove(key);
            p = p->next;
        }
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Stress test 'contains' again to check for false positives. press 1 then enter to begin" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        Node<string>* r = keyHolder2.get_head();
        count = 0;
        while (r != NULL){
            string key = r->data;
            if (testmap.contains(key) ){
                throw out_of_range("false pisitive round 1");
            }
            count ++ ;
            cout 
                << count
                << " - key:  "
                << key
                << " not found"
                << endl; 
            r = r->next;
        }
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "print map to confirm empty. press 1 then enter to begin"                          << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        testmap.print();
    }
    cout  << Colors::GREEN << "tests finished, no errors thrown" << Colors::RESET << endl;
    cin >> wait;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Let's fill that same map one more time, with 100k key/value pairs and perform some analytics" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
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
    // cout << "Average number of collisions per bucket: ";            // average number of collisions per bucket
    // cout << Colors::MAGENTA << testmap.avg_depth() << Colors::RESET << endl;  
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Highest number of collisions present in map: ";     // test to find the most number of collisions
    // cout << Colors::MAGENTA << testmap.max_depth() << Colors::RESET << endl;     
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


    // --------------------------------------------------------------------------------------------------------  
    // TESTING WITH CONTACT OBJECTS  / Create a map of 100k contacts
    // --------------------------------------------------------------------------------------------------------  
    List<Contact> contacts;                                                    // Linked list to hold contacts
    FileOpener::contactLoader("backend/contacts.txt", contacts);     // load the contacts into the linked list
    OpenHashTable<Contact> contactMap;                                   // create a blank map of type Contact
    //ClosedHashTable<Contact> contactMap;                                   // create a blank map of type Contact
    Node<Contact>* z = contacts.get_head();                 // iterate through the contacts in the linked list
    while (z != NULL){
        Contact contact = z->data;                                                     // pull out the contact
        string key = contact.getPhone();                               // get the phone number to use as a key
        contactMap.put(key, contact);                  // place the key and value (value being contact object)
        z = z->next;
    }

    contactMap.print();
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- "
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" OPEN<CONTACT>MAP DATA - using phone numbers as keys " << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << Colors::RESET << endl;                                                                         
    cout << "Map capacity = ";
    cout << Colors::MAGENTA << contactMap.map_capacity() << Colors::RESET;        // return correct capacity
    cout << ". Is this number prime? ";
    if (testmap.is_prime(contactMap.map_capacity())){
        cout << Colors::GREEN << "true" << Colors::RESET << endl;
    } else {
        cout << Colors::RED << "false" << Colors::RESET << endl;
    }
    //--------------------------------------------------------------------------------------------------------   
    cout << "Number of key/value pairs in map: ";                   // return number of key/value pairs in map
    cout << Colors::MAGENTA << contactMap.m_size() << Colors::RESET << endl;        
    //-------------------------------------------------------------------------------------------------------- 
    cout << "Number of used buckets in map: ";
    cout << Colors::MAGENTA << contactMap.count_full() << Colors::RESET << endl;      // how many used buckets
    //--------------------------------------------------------------------------------------------------------  
    cout << "Number of empty buckets in map: ";
    cout << Colors::MAGENTA << contactMap.count_empty() << Colors::RESET << endl;   // how many unused buckets
    //--------------------------------------------------------------------------------------------------------
    cout << "Number of empty buckets " 
         << Colors::MAGENTA 
         << contactMap.count_empty() 
         << Colors::RESET 
         << " + number of used buckets "
         << Colors::MAGENTA << contactMap.count_full() 
         << Colors::RESET << " = capacity "
         << Colors::MAGENTA << contactMap.map_capacity() << ": " << Colors::RESET;
    if (contactMap.count_empty() + contactMap.count_full() == contactMap.map_capacity()){
        cout << Colors::GREEN << "true" << Colors::RESET << endl;
    } else {
        cout << Colors::RED << "false" << Colors::RESET << endl;
    }                                                                                // confirm numbers add up
    //--------------------------------------------------------------------------------------------------------
    // cout << "Average number of collisions per bucket: ";            // average number of collisions per bucket
    // cout << Colors::MAGENTA << contactMap.avg_depth() << Colors::RESET << endl;     
    // //--------------------------------------------------------------------------------------------------------
    // cout << "Highest number of collisions present in map: ";     // test to find the most number of collisions
    // cout << Colors::MAGENTA << contactMap.max_depth() << Colors::RESET << endl;  
    //--------------------------------------------------------------------------------------------------------
    cout << "Percent buckets empty (number of buckets used vs number of pairs):  "; // how many unused buckets
    cout << Colors::MAGENTA << (double)contactMap.count_full() / (double)contactMap.m_size()  
         << Colors::RESET << endl;                                  
    //-------------------------------------------------------------------------------------------------------- 
    cout << Colors::YELLOW << "Load factor 𝜆" << Colors::RESET << " : "; 
    cout << Colors::YELLOW << (double)contactMap.count_full() / (double)contactMap.map_capacity()  
         << Colors::RESET << endl;
    //-------------------------------------------------------------------------------------------------------- 
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << Colors::RESET << endl; 

    return 0;
    
}