
//------------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / OPEN MAPS TESTING
//------------------------------------------------------------------------------------------------------------
#include "hash_tables/OpenHashTable.hpp"
#include "hash_tables/ClosedHashTable.hpp"
#include "backend/List.hpp"
#include "backend/Contact.h"
#include "backend/FileOpener.hpp"
#include "backend/colors.hpp"
#include <iostream>
#include <string>


//------------------------------------------------------------------------------------------------------------
using namespace std;

string goob = Colors::MAGENTA + "goob" + Colors::RESET;                                    
string name;
int val;
List<string>keyHolder;
ClosedHashTable<int>testmap;   
                                    
int main(){

    //--------------------------------------------------------------------------------------------------------
    // SET UP STRESS TEST
    //--------------------------------------------------------------------------------------------------------
    int count = 0;
    int problem_size = 100;
    cout <<"---------------------------------------------------------------------------------------------------" << endl;
    cout << "   OPEN MAP STRESS TESTING"    << endl;
    cout <<"---------------------------------------------------------------------------------------------------" << endl;

    //--------------------------------------------------------------------------------------------------------
    // PRINT CURRENT STATE OF MAP
    //--------------------------------------------------------------------------------------------------------
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------"
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" OPEN<INT>MAP DATA - using strings for keys" << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------" 
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
    <<"---------------------------------------------------------------------------------------------------" 
    << Colors::RESET << endl; 
    //--------------------------------------------------------------------------------------------------------
    // USER DEFINED KEY / VALUE
    //--------------------------------------------------------------------------------------------------------
    cout << "enter your key: ";
    cin >> name;
    cout << endl;

    cout << "enter your value (int): ";
    cin >> val;
    cout << endl;

    string g = Colors::RED + name + Colors::RESET; //constant used to test features with known key value
  
    //--------------------------------------------------------------------------------------------------------
    // USER DEFINED PROBLEM SIZE
    //--------------------------------------------------------------------------------------------------------
    cout << "enter problem size: "; 
    cin >> problem_size; 
    cout << endl;

    //--------------------------------------------------------------------------------------------------------
    // FILL MAP
    //--------------------------------------------------------------------------------------------------------
    testmap.put(g, val);
    keyHolder.insert(g);

    string str = "";
    for (int i = 0 ; i < problem_size ; i ++ ){               // how many times to place a string into the map
        str = "";
        str += to_string(i);                 // or can just test with numbers if you want for easier debugging
        testmap[str] = i;                // place the random string in the map as a key with , 'i' as value
        keyHolder.insert(str);                      
    }

    //--------------------------------------------------------------------------------------------------------
    // BEGIN STRESS TEST WALK THROUGH
    //--------------------------------------------------------------------------------------------------------
    int wait;
     //--------------------------------------------------------------------------------------------------------
    // PRINT CURRENT STATE OF MAP
    //--------------------------------------------------------------------------------------------------------
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------" 
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" OPEN<INT>MAP DATA - using strings for keys" << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------"  
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
    cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "press 1 then enter to see map"                                                    << endl;
    cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cin >> wait;
    testmap.print();
    cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "Stress test 'get' for every key in map. press 1 then enter to begin"              << endl;
    cout <<"---------------------------------------------------------------------------------------------------"  << endl;
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
    cout  << Colors::GREEN << "get test finished, no errors thrown" << Colors::RESET << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "Stress test 'contains' for every key in map. press 1 then enter to being"   << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
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
    cout  << Colors::GREEN << "contains test finished, no errors thrown" << Colors::RESET << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "Stress test 'remove' for every key in map. press 1 then enter to being"     << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
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
    cout  << Colors::GREEN << "remove test finished, no errors thrown" << Colors::RESET << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "Stress test 'contains' again to check for false positives. press 1 then enter to begin."   << endl;
    cout <<"---------------------------------------------------------------------------------------------------"  << endl;
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
    cout  << Colors::GREEN << "get test finished, no errors thrown" << Colors::RESET << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cout << "print map to confirm empty. press 1 then enter to begin"                          << endl;
     cout <<"---------------------------------------------------------------------------------------------------"  << endl;
    cin >> wait;
    testmap.print();
    cout << "current map size: " << testmap.m_size() << endl;
   

   
    //--------------------------------------------------------------------------------------------------------
    // PRINT CURRENT STATE OF MAP
    //--------------------------------------------------------------------------------------------------------
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------"
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" OPEN<INT>MAP DATA - using strings for keys" << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"---------------------------------------------------------------------------------------------------" 
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

    cout <<"---------------------------------------------------------------------------------------------------"<< endl;
    cout << "TEST CLOSED MAP WITH 100k CONTACT OBJECTS. press 1 then enter to begin"                                << endl;
    cout <<"---------------------------------------------------------------------------------------------------"<< endl;
    cin >> wait;
    //--------------------------------------------------------------------------------------------------------  
    // TESTING WITH CONTACT OBJECTS  /  Create a map of 100k contacts
    //--------------------------------------------------------------------------------------------------------  
    List<Contact> contacts;                                                    // Linked list to hold contacts
    FileOpener::contactLoader("backend/contacts.txt", contacts);     // load the contacts into the linked list
    ClosedHashTable<Contact> contactMap;                                 // create a blank map of type Contact
    Node<Contact>* zz = contacts.get_head();                // iterate through the contacts in the linked list
    while (zz != NULL){
        Contact contact = zz->data;                                                   // pull out the contact
        string key = contact.getPhone();                               // get the phone number to use as a key
        contactMap.put(key, contact);                  // place the key and value (value being contact object)
        zz = zz->next;
    }

    contactMap.print();
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- "
    << Colors::RESET << endl;
    cout << Colors::GREEN <<" OPEN <CONTACT>MAP DATA - using phone numbers as keys " << Colors::RESET << endl;    
    cout << Colors::GREEN 
    <<"--------------------------------------------------------------------------------------------------- " 
    << Colors::RESET << endl;  
    cout << "number of resizes to fill this map: ";                      // return number of resizes completed
    cout << Colors::MAGENTA << contactMap.times_resized() <<Colors::RESET << endl;  
    cout << Colors::GREEN                                                                        
         << "Map capacity = ";
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
    cout << "Highest number of collisions present in map: ";  // test to find the most number of collisions
    cout << Colors::MAGENTA << contactMap.max_depth() << Colors::RESET << endl;  
    //--------------------------------------------------------------------------------------------------------
    cout << "Average number of collisions per bucket: ";            // average number of collisions per bucket
    cout << Colors::MAGENTA << testmap.avg_depth() << Colors::RESET << endl;  
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