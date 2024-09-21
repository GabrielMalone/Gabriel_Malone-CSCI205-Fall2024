#ifndef List_H
#define List_H

#include <iostream>
#include <string>
#include "Node.hpp"

using namespace std;

template <typename T>
class List {
    private:
        size_t link_size = 0;
        Node<T>* head = new Node<T>();
    public:
        /**
         * No argument constructor
         */
        List(){};
        
        /**
         *  Accepts a templated array as a paramaeter. 
         *  Adds items to list according to their order in the array.
         */
        List(T* array, size_t size){};

        /**
         *  Insert a node at a specific location
         */
        void insert(T item, size_t pos){
            if (pos == 0){
                Node<T>* newNode = new Node<T>();   // if inserting at position 0 (the head),
                newNode->data = item;
                newNode->next = head;               // new node moves in front of current head
                head = newNode;                     // head is now the new node
                link_size ++ ;                      // increase size of linked list
                return;                             // nuffin else to do
            }                                       
                                                    
            if (pos > link_size){                   // if inserting after the head, need to see if the position falls within how many items are present (size of linked lis)
                throw std::invalid_argument("position out of bounds"); 
            }                                       
            size_t counter = 1;                     // start at one since skipping the head
            Node<T>* prev_node = head; 
            Node<T>* cur_node = head->next;         // get the node previous to where new node will be inserted via position / start at the node right after the head
            while (cur_node->next != NULL){         // while the current node's position != the end of the list  
               if (counter == pos ){                // if counter reaches the desired position
                    break;                          // break loop as you've reached your destination
                }      
                prev_node = cur_node;         
                cur_node = cur_node -> next;        // keep iterating to next node
                counter ++ ;                        // track how many nodes you've passed through    
            }
            Node<T>* newNode = new Node<T>();       // create new node 
            newNode->data = item;                   // with parameter's data
            prev_node->next = newNode;              // set newNode as the next for the node prior to it
            newNode->next = cur_node;               // set newNode's next as the node it is being inserted before
            link_size ++ ;                          // increase link size
        }   

        /**
		 *  print list contents
		 */
		void print(){
            cout << "[";
            Node<T>* current_node = head;
            size_t counter = 0;
            while (counter < link_size){
                cout << current_node->data << ",";
                current_node = current_node -> next;
                counter ++ ;
		    }
            cout << "]";
			cout << endl;
        }
};


#endif