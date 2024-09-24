// Gabriel Malone // CSCI205 // LAB 4

#ifndef Linked_List_H
#define Linked_List_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;
};

template <class T>
class List {
    private:

        size_t link_size = 0;           // keep track of list size for various functions
        Node<T>* head;

    public:

        /**
         * No argument constructor
         */
        List(){
            head = NULL;                // entry point to the linked list
        };
        
        /**
         *  Accepts a templated array as a paramaeter. 
         *  Adds items to list according to their order in the array.
         */
        List(T* array, size_t size){
            head = new Node<T>();
            for (size_t i = 0 ; i < size ; i ++){
                insert(array[i], i);
            }
        };

        ~List(){   
            //cout << "deconstructor called for linked list of " << link_size <<  " items" << endl;                          
            Node<T>* cur_node = head;
            while (cur_node != NULL){
                Node<T>* next = cur_node->next;
                delete cur_node;
                cur_node = next;
            }
        };	

        /**
         * returns pointer to this List's head
         */
        Node<T>* get_head(){
            return this->head;
        }

        /**
         * returns pointer to this List's head
         */
        Node<T>* get_next(){
            return this->next;
        }

        /**
         * returns pointer to this List's head
         */
        T get_head_element(){
            return this->head->data;
        }

        /**
         *  Insert a item at a specific location
         */
        void insert(T item, size_t pos){
            if (pos == 0 && head == NULL){
                head = new Node<T>();
                head->data = item;
                link_size ++;
                return;       
                }                                   // return, else not needed
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
            while (cur_node != NULL){               // while the current node's position != the end of the list  
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
         *  Removes the item at the specified index
         */
        T remove (size_t pos){
            if (pos == 0){
                Node<T>* og_head = head;            // if removing at position 0 (the head),
                T item = og_head->data;
                head = head->next;                  // node that was just after the head now becomes the head
                link_size -- ;                      // decrease size of linked list
                og_head = nullptr;
                delete og_head;                     // delete the original head pointer
                return item;                        // nuffin else to do
            }                                       
                                                    
            if (pos > link_size){                   // if deleting after the head, need to see if the position falls within how many items are present (size of linked lis)
                throw std::invalid_argument("position out of bounds"); 
            }                                       
            size_t counter = 1;                     // start at one since skipping the head
            Node<T>* prev_node = head; 
            Node<T>* cur_node = head->next;         // get the node previous to where new node will be inserted via position / start at the node right after the head
            while (cur_node != NULL){               // while the current node's position != the end of the list  
               if (counter == pos ){                // if counter reaches the desired position
                    break;                          // break loop as you've reached your destination
                }      
                prev_node = cur_node;         
                cur_node = cur_node -> next;        // keep iterating to next node
                counter ++ ;                        // track how many nodes you've passed through    
            }
            prev_node->next = cur_node->next;        
            link_size -- ;                          // decrease link size
            T item = cur_node->data;                // get the diesired item
            delete cur_node;                        // remove dangling pointer
            return item;                            // return item
        }

        /**
         *  Get the element at the specified position
         */
        T& get (size_t pos){
            if (pos > link_size){
                throw std::invalid_argument("position out of bounds"); 
            }
            size_t counter = 0;                     // count until reach desired position
            Node<T>* cur_node = head;               
            while (cur_node != NULL){               // traverse the list and count each time reach a new node
                if (counter == pos){                // break look when you've arrived
                    break;
                }
                cur_node = cur_node->next;
                counter ++;
            }
            return cur_node->data;                  // return that node's data
        }

        /**
         *  Return index of item if found in the linked list
         *  Returns -1 if not found
         */
        int find (T item){
            int index = 0;
            Node<T>* cur_node = head;               
            while (cur_node != NULL){               // traverse the list and count each time a new node is reached
                if (item == cur_node->data){        // if node's data matches
                    return index;                   // break and return index
                }
                index ++ ;                          // otherwise keep looking
                cur_node = cur_node->next;          // move to next node
            }           
            return -1;                              // if get to here, nothing found
        }

        /**
		 * returns how many items are in a list
		 */
		size_t length(){
			return link_size;
		}   

        /**
		 * returns how many items are in a list
		 */
		size_t count(){
			return link_size;
		}  

        /**
         *  reverse the order of items in the list
         */
        void reverse(){
            T* temp = new T[link_size];             // set up temp array , wait lol why did I do this. need to redo this logic. 
            Node<T>* cur_node_A = head;               
            size_t index_A = 0 ;                    // index for array ^
            while (cur_node_A != NULL){             // traverse the linked list
                temp[index_A] = cur_node_A->data;   // add data to array as you go
                cur_node_A = cur_node_A->next;      // move to next node
                index_A ++ ;                        // increment index
            }
                                                    // now reverse loop through the array and set that data for the linked list
            Node<T>* cur_node_B = head;               
            size_t index_B = link_size -1;          // reverse index for array
            while (cur_node_B != NULL){             // traverse the linked list
                cur_node_B->data = temp[index_B];   // replace linked list data as you go
                cur_node_B = cur_node_B->next;      // move to next node
                index_B -- ;                        // decrement index
            }
            delete[] temp;           
        }

        /**
         *  appends another list to this list
         */
        void append(List &list){                    // originally had this function just p9ointing at another list, but this caused memory issues in linux
            Node<T>* n = list.get_head();
            while (n != NULL){
                this->insert(n->data, link_size);
                n = n->next;
            }
        }

        /**
		 *  print list contents
		 */
		void print(){
            cout << "[";
            Node<T>* current_node = head;
            size_t counter = 0;
            while (counter < link_size){
                cout << current_node->data << " -> ";
                current_node = current_node -> next;
                counter ++ ;
		    }
            cout << "]";
			cout << endl;
        }
};


#endif