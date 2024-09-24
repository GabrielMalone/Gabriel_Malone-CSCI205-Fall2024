// GABRIEL MALONE / CSCI205 / LAB 4

#ifndef Array_List_H
#define Array_List_H

#include <string>
#include <typeinfo>
#include <iostream>
#include <iomanip>


using namespace std;

/**
 * List class
 */
template <class T> class A_List{
	private:													//Private member variables to manage insertion and removal points		
		size_t size = 0;		            					// number of items in the List
		size_t capacity = 100;	            					// size of the array (Default = 100)
		size_t front = 0;		            					// index of the front of the List
		size_t back = capacity-1;           					// 0 index adjust
		size_t head = 0;	                					// index of the head of the list
		size_t tail = capacity - 1;		    					// index of the tail of the list
		T* array;			                					// array to store items (pointer to type T, to be determined at run time

		/**
		 * Helper function to resize the array
		 */
		void resize(){
			size_t old_capacity = capacity; 					// for resorting / unwrapping array on resize
			capacity = capacity * 2;        					// size of next array = double current array
			T* dbl_array_temp ;             					// instantiate new array
			dbl_array_temp = new T[capacity];					// copy contents from old array in order
			for (size_t i = 0 ; i < old_capacity; i ++)			// start from the current head position to the end of the array
			{
				dbl_array_temp[i] = array[i];					// zero out the head position for the new array
			}
			delete[] array;										// delete old array on resize
			array = dbl_array_temp;								// set array pointer to the new, bigger temp array
		}

		/**
		 * for operations that remove items from the array
		 */
		void shiftItemsDown(size_t pos){
			size_t index = pos;                                 // set index to the current elelment being removed
			for (size_t i = 0 ; i < size - pos - 1; i ++ ){     // iterate for the distance from current position to end of array (to where the end of values are located anyway) - 1 for decreased size of array
				array[index] = array[index + 1];                // set the current item equal to the next item
				index ++;                                       // repeat ^
			}
		}

		/**
		 * for operations that remove items from the array
		 */
		void shiftItemsUp(size_t pos){
			// iterate backwards? yee
			size_t index = size;
			for (size_t i = size ; i > pos ; i -- ){
				array[index] = array[index - 1];
				index --;
			}
		}

	public:

		/**
		 * Default constructor. Creates list with a capacity of 10
		 */
		A_List(){
			capacity= 10;
			array	= new T[capacity]; 							// create dynamic memory for array of template type T
		}					

		/**
		 * Constructs a List with given capacity (size of underlying array)
		 */
		A_List(size_t cap){
			capacity = cap;
			array = new T[cap];
		}

		/**
		 * Constructs a List with given array of items and size
		 */
		A_List(T* arr, size_t o_size){
			if (arr == nullptr)									// ensure the array is not null. Throw an invalid argument exception if it is
			{
				throw std::invalid_argument("array is null");
			} else {
				capacity = o_size * 2;							// set the capacity to double the size of the array
				T* temp_array = new T[capacity];
				for (size_t i = 0; i < o_size; i++) {			// copy contents from old array
					temp_array[i] = arr[i];
				}
				array = temp_array;								// point og array at temp array
			}

		}

		/**
		 * Free dynamic memory allocated for the List
		 */
		~A_List(){
			delete[] array;
		}

		/**
		 * return capacity of array
		 */
		size_t getCapacity(){
			return capacity;
		}

		/**
		 * Returns whether the List is full
		 */
		bool full(){
			return size == capacity;
		}

		/**
		 * Returns whether the List is empty
		 */
		bool empty(){
			return size == 0;
		}

		/**
		 * Returns the number of items in the List
		 */
		size_t length(){
			return size;
		}

		/**
		 * returns pointer to the array
		 */
		T* get_array(){
			return array;
		}

		/**
		 * get item at position
		 */
		T get(size_t pos){
			if (pos > capacity || pos < 0){						// if invalid index
				throw std::invalid_argument("index out of bounds");
			}
			// otherwise
			return array[pos];
		}

		/**
		 * returns how many items are in a list
		 */
		size_t count(){
			return size;
		}

		/**
		 *  find item and return its position
		 */
		int find(T item){
			for (size_t i = 0 ; i < size ; i ++){
				if (item == array[i]){
					return (int)i;
				}
			}
			return -1;											// if nothing found return -1;
		}

		/**
		 * insert item at position
		 */
		void insert(T item, size_t pos){									
			if (pos > capacity || pos < 0){						// if index out of bounds
				throw std::invalid_argument("index out of bounds");
			}
			size ++ ;                  							// increaes size first to make the extra room for shifting
			if (full()){                						// increae capacity if needed
				resize();
			}
			shiftItemsUp(pos);          						// move everything over to make room if needed
			array[pos] = item;          						// insert item
		}
	
		/**
		 * remove an item via its position in the array 
		 */
		T remove (size_t pos){  
			if (pos <= size){         							// if a valid position request
				T item = array[pos];    						// need to resize array
				shiftItemsDown(pos);    						// and shift everything down 1 spot that was after this item
				size -- ;               						// reduce size of array
				return item;            						// retun the removed item
			}
			throw std::invalid_argument("item not in array");            
		}

		/**
		 * remove duplicates from the list
		 */
		void removeDuplicates(){
		   size_t index = 0;									// starting index (at front of array)	
		   T current_obejct = array[index];						// get the first object from the array
		   while (index != size){								// run loop until index == the size of the array
				size_t copies = 0;								// track number of copies of the current item being checked
				for (size_t i = index ; i < size - 1; i ++){	// loop through the array
					if (current_obejct == array[i + 1]){		// if the iterated object == current object
						copies ++;								// increment copies present
					}
				}
				if (copies > 0){								// if copies of current object present
					for (size_t i = 0 ; i < copies ; i ++){		// remove current object for however many times it was duplicated
						remove(current_obejct);
					}	
					index = 0;									// if copies were present and items removed, start the loop over from the start // since remove removes items from front a new front will be present
				}
				else {
					index ++;									// otherwise move on to the next item in the array and check the remainder of the array against it
				}
				current_obejct = array[index];					// set the current object accordingly
		   }
		}
		   
		/**
		 * reverse items in a list
		 */
		void reverse(){
			T* temp = new T[size];                               // set up temp array
			size_t index = 0;                                    // index for temp array to start at front
			for (size_t i = size ; i > 0 ; i -- ){               // reverse iterate through current array
				temp[index] = array[i-1];                        // place items from back of current array into front of temp
				index ++;                                        // increment temp index
			}
			delete[] array;
			array = temp;                                        // set old array pointer equal to the temp 
		}

		/**
		 * appends another list to this list
		 */
		void append(A_List &list){								// resize until enough space availabe for the append							
			while (this->size + list.length() >= this->capacity){
				resize();
			}													// starting position for appending to current array (at the back) 
			size_t starting_index = this->size; 				// now can start to append, starting from back of this->array for the length of the incoming list													
			for (size_t i = 0 ; i < list.length() ; i ++ ){
				this->array[starting_index + i] = list.get_array()[i];
				this->size ++; 									// increase size of current array for each element added
			}
		}

		/**
		 *  print list contents
		 */
		void print(){
			cout << "[";
			for (size_t i = 0 ; i < size ; i ++ ){
				if (i == size - 1){
					cout << array[i];
				}
				else if (i < size){
					cout << array[i] << ",";
				}
			}
			cout << "]";
			cout << endl;
		}

		/**
		 * operator overload for []
		 */
		T& operator[](int index)
		{
			return array[index];
		}

};

#endif
