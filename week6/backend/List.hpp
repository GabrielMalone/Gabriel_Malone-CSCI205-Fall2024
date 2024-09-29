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

        size_t link_size = 0;                               // keep track of list size for various functions
        Node<T>* head;
        Node<T>* tail;

    public:

        /**
         * No argument constructor
         */
        List(){
            head = NULL;                                // entry point to the linked list
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

        Node<T>* get_tail(){
            return this->tail;
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
         *  Insert item at front of list without position argument
         */
        void insert(T item){
            if (head == NULL){                      // if inserting at the front of linked list
                head = new Node<T>();               // make new node
                head->data = item;                  // set data 
                tail = head;                        // set tail as head as well since only one node exists
                link_size ++;                       // increment by 1 
                return;                             // return, else not needed
            }                                   
            Node<T>* newNode = new Node<T>();       // if inserting at position 0 (the head),
            newNode->data = item;
            newNode->next = head;                   // new node moves in front of current head
            head = newNode;                         // head is now the new node
            link_size ++ ;                          // increase size of linked list
            return;                                 // nuffin else to do
        }

        /**
         *  Insert a item at a specific location
         */
        void insert(T item, size_t pos){
            if (pos == 0 && head == NULL){         // if inserting at the front of linked list
                head = new Node<T>();              // make new node
                head->data = item;                 // set data 
                tail = head;                       // set tail as head as well since only one node exists
                link_size ++;                      // increment by 1 
                return;                            // return, else not needed
                }                                   
            if (pos == 0){
                Node<T>* newNode = new Node<T>();   // if inserting at position 0 (the head),
                newNode->data = item;
                newNode->next = head;               // new node moves in front of current head
                head = newNode;                     // head is now the new node
                link_size ++ ;                      // increase size of linked list
                return;                             // nuffin else to do
            }
            if (pos == link_size){                  // if inserting at the back
                Node<T>* newNode = new Node<T>();   // same logic as head insertion
                newNode->data = item;               // constant time operation
                tail->next = newNode;
                tail = newNode;
                link_size ++;
                return;    
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
                delete og_head;                     // delete the original head pointer
                return item;                        // nuffin else to do
            }
            if (pos == link_size){                  // if removing from the back
                Node<T>* n = head;                  // if removing at position 0 (the head),
                while (n->next != NULL){   
                    n = n->next;
                }
                T item = n->next->data;
                delete tail;
                tail = n;
                link_size --;
                return item;    
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
		size_t count(T item) {                     
            size_t count = 0;                       // increase counnt when item found          
			Node<T>* n = head;                      // traverse list
            while(n != NULL){
                if (n->data == item){                // if item found
                    count ++;                        // increase count
                }
                n = n->next;
            }
            return count;
		}  
        /**
         *  reverse the order of items in the list
         */
        void reverse(){
            T* temp = new T[link_size];             // set up temp array 
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
        void append(List& list){                    // originally had this function just p9ointing at another list, 
            tail->next = list.head;
            tail = list.tail;
            link_size += list.link_size;
            list.head = nullptr;                    // set these nullptrs to avoid double deletes
            list.tail = nullptr;                    // the appending list's destructor will e called and traverse the shared pointers
        }                                           // then called again when the list being appenended's destructor is called
                                                    // nothign will try to be deleted at this point if the pointer is null, though
         /**
         * remove duplicated items from the list    // my entirely inneficient solution to appease linux and valgrind
         */
        void removeDuplicates(){
            T* temparr = new T[link_size];          // initialize a temp array
            for (size_t i = 0 ; i < link_size ; i ++){
				temparr[i] = -999999999;
			}
            size_t tempIndex = 0;                   // index for temp array
            bool inArry = false;                    // keep track of unique elements
            Node<T>* node = head;                   // traverse list
            while (node != NULL){
                inArry = false;
                for (size_t i = 0 ; i < link_size ; i ++){
                    if (node->data == temparr[i]){  // if item in list
                        inArry = true;              // then it be in list
                    }
                }
                if (! inArry){
                    temparr[tempIndex] = node->data;// if looped through array and it wasn't there, add it to array
                    tempIndex ++ ;
                }
                node = node->next;
            }
           
            Node<T>* cur_node = head;               // delete the old linked list - sigh
            while (cur_node != NULL){
                Node<T>* next = cur_node->next;
                delete cur_node;
                cur_node = next;
            }
            
            Node<T>* newNode = new Node<T>();       // make a new linked list 
            head = newNode;                         // of length = unique values in array
            newNode->data = temparr[0];
            for (size_t i = 1 ; i < tempIndex; i ++){
                Node<T>* next = new Node<T>();
                newNode->next = next;
                tail = newNode->next;
                newNode = newNode->next;
                newNode->data = temparr[i];
            }
            link_size = tempIndex;
            tail->data = temparr[tempIndex -1];
            delete[] temparr;
        }

        // /**                                      // linux and valgrind didn't like this but im guessing this is more in line what is supposed to be done
        //  * remove duplicated items from the list
        //  */
        // void removeDuplicates(){
        //     Node<T>* n = head;
        //     Node<T>* next = head->next;
        //     size_t counter = 0;
        //     while (n != NULL ){
        //         while (next != NULL){
        //             if (n->data == next->data){
        //                 counter ++;
        //             }
        //             next = next->next;
        //         }
        //         for (size_t i = 1 ; i < counter ; i ++){ 
        //             remove(find(n->data));
        //         }
        //         next = head;
        //         n = n->next;
        //         counter = 0;
        //     }
        // }

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
