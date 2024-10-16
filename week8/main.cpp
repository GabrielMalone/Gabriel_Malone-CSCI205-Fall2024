
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
                                    
int main(){
    while (true){
    //--------------------------------------------------------------------------------------------------------
    // SET UP FOR STRING RANDOMIZATION
    //--------------------------------------------------------------------------------------------------------
    int count = 0;
    int problem_size = 200;

    //OpenHashTable<int>testmap;   // initialize an empty map. loop below will test resize functionality as well
    ClosedHashTable<int>testmap;   // initialize an empty map. loop below will test resize functionality as well
 
    List<string>keyHolder;
    cout << "current map size: " << testmap.m_size() << endl;
    string str = "";
    // fill map and key holder
    for (int i = 0 ; i < problem_size ; i ++ ){               // how many times to place a string into the map
        str = "";
        str += to_string(i);              // or can just test with numbers if you want for easier debugging
        testmap.put(str, i);                // place the random string in the map as a key with , 'i' as value
        keyHolder.insert(str);                      
    }
    // should be filled
    testmap.print();
    // should equal problem size
    cout << "current map size: " << testmap.m_size() << endl;
    // see if you can get all the keys without issue
    Node<string>* n = keyHolder.get_head();
    count = 0;
    while (n != NULL){
        count ++ ;
        string key = n->data;
        cout 
        << count
        << " - getting key: " << key
        << " value: " << testmap.get(key) 
        << endl;
        n = n->next;
    }
    // see if contains works without issue
    Node<string>* q = keyHolder.get_head();
    count = 0;
    while (q != NULL){
        count ++ ;
        string key = q->data;
        cout 
        << count
        << " - " ;
        if (! testmap.contains(key) ){
            cout << "key not found" << endl;
            throw out_of_range("contains error round 1");
        } else {
            cout << "true" << endl;
        }
        q = q->next;
    }
    // see if you can delete all the values without issue
    count = 0;
    Node<string>* p = keyHolder.get_head();
    while (p != NULL){
        count ++;
        string key = p->data;
        cout << count << " - ";
        testmap.remove(key);
        p = p->next;
    }
    // test contains again to see if it doesn't falsely pick up the old values
    Node<string>* r = keyHolder.get_head();
    count = 0;
    while (r != NULL){
        count ++ ;
        string key = r->data;
        cout 
        << count
        << " - " ;
        if (testmap.contains(key) ){
            throw out_of_range("false pisitive round 1");
        } else {
            cout << "remove successful" << endl;
        }
        r = r->next;
    }
    // see current state of map, should be empty
    testmap.print();
    // should be zero
    cout << "current map size: " << testmap.m_size() << endl;

    List<string>keyHolder2; // reset key holder


//----------------------------------------------------------------------------------------------------------

    // fill map and key holder
    for (int i = 0 ; i < problem_size ; i ++ ){               // how many times to place a string into the map
        str = "";
        str += to_string(i);                 // or can just test with numbers if you want for easier debugging
        testmap.put(str, i);                // place the random string in the map as a key with , 'i' as value
        keyHolder2.insert(str);                      
    }

    // should be filled
    testmap.print();
    // should equal problem size
    cout << "current map size: " << testmap.m_size() << endl;
    // see if you can get all the keys without issue
    Node<string>* a = keyHolder2.get_head();
    count = 0;
    while (a != NULL){
        count ++ ;
        string key = a->data;
        cout 
        << count
        << " - getting key: " << key
        << " value: " << testmap.get(key) 
        << endl;
        a = a->next;
    }
    // see if contains works without issue
    Node<string>* b = keyHolder2.get_head();
    count = 0;
    while (b != NULL){
        count ++ ;
        string key = b->data;
        cout 
        << count
        << " - " ;
        if (! testmap.contains(key) ){
            cout << "key not found" << endl;
            throw out_of_range("contains error round 2");	
        } else {
            cout << "true" << endl;
        }
        b = b->next;
    }
    // see if you can delete all the values without issue
    count = 0;
    Node<string>* c = keyHolder2.get_head();
    while (c != NULL){
        count ++;
        string key = c->data;
        cout << count << " - ";
        testmap.remove(key);
        c = c->next;
    }
    // test contains again to see if it doesn't falsely pick up the old values
    Node<string>* d = keyHolder2.get_head();
    count = 0;
    while (d != NULL){
        count ++ ;
        string key = d->data;
        cout 
        << count
        << " - " ;
        if (testmap.contains(key) ){
            throw out_of_range("false pisitive round 2");				
        } else {
            cout << "remove successful" << endl;
        }
        d = d->next;
    }
    // see current state of map, should be empty
    testmap.print();
    // should be zero
    cout << "current map size: " << testmap.m_size() << endl;

    //--------------------------------------------------------------------------------------------------------  
    // TESTING WITH CONTACT OBJECTS  / Create a map of 100k contacts
    //--------------------------------------------------------------------------------------------------------  
    List<Contact> contacts;                                                    // Linked list to hold contacts
    FileOpener::contactLoader("backend/contacts.txt", contacts);     // load the contacts into the linked list
    //OpenHashTable<Contact> contactMap;                                   // create a blank map of type Contact
    ClosedHashTable<Contact> contactMap;                                   // create a blank map of type Contact
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
    }
    return 0;
}
