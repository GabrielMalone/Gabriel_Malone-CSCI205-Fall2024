// GABRIEL MALONE / CSCI205 / LAB 3

#ifndef List_H
#define List_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T> class List{
	private:
		//Private member variables to manage insertion and removal points
		size_t size = 0;		            // number of items in the List
		size_t capacity = 100;	            // size of the array (Default = 100)
		size_t front = 0;		            // index of the front of the List
		size_t back = capacity-1;           // 0 index adjust
		size_t head = 0;	                // index of the head of the list
		size_t tail = capacity - 1;		    // index of the tail of the list
		T* array;			                // array to store items (pointer to type T, to be determined at run time)

		//Helper function to resize the array
		void resize(){
            size_t old_capacity = capacity; // for resorting / unwrapping array on resize
            capacity = capacity * 2;        // size of next array = double current array
            T* dbl_array_temp ;             // instantiate new array
            dbl_array_temp = new T[capacity];
            // copy contents from old array in order
            // start from the current head position to the end of the array
            for (size_t i = 0 ; i < old_capacity; i ++)
            {
                // zero out the head position for the new array
                dbl_array_temp[i] = array[i];
            }
            // set array pointer to the new, bigger temp array
            array = dbl_array_temp;
		}

	public:
		//Constructs a List with default capacity of 100 items
		List(){
			capacity= 10;
			array	= new T[capacity]; // create dynamic memory for array of template type T
		}					

		//Constructs a List with given capacity (size of underlying array)
		List(size_t cap){
            capacity = cap;
			array = new T[cap];
		}

		// Constructs a List with given array of items and size
		List(T* arr, size_t o_size){
			// ensure the array is not null. Throw an invalid argument exception if it is
			if (arr == nullptr)
			{
				throw std::invalid_argument("array is null");
			} else {
				// set the capacity to double the size of the array
				capacity = o_size * 2;
				T* temp_array = new T[capacity];
				// copy contents from old array
				for (size_t i = 0; i < o_size; i++) {
					temp_array[i] = arr[i];
				}
				// delete old pointer
				// delete[] array;
				// point og array at temp array
				array = temp_array;
			}

		}

		//Free dynamic memory allocated for the List
		~List(){
			delete[] array;
		}

		// return capacity of array
		size_t getCapacity(){
			return capacity;
		}

		//Returns whether the List is full
		bool full(){
			return size == capacity;
		}

		//Returns whether the List is empty
		bool empty(){
			return size == 0;
		}

		//Returns the number of items in the List
		size_t length(){
			return size;
		}

        // returns pointer to the array
		T* get_array(){
			return array;
		}

        // get item at position
        T get(size_t pos){
            // if invalid index
            if (pos > capacity || pos < 0){
                throw std::invalid_argument("index out of bounds");
            }
            // otherwise
            return array[pos];
        }

        // how many items in list 
        // since keeping track of this data already, 0(1)
        size_t count(){
            return size;
        }

        // find item and return its position
        int find(T item){
            for (size_t i = 0 ; i < size ; i ++){
                if (item == array[i]){
                    return (int)i;
                }
            }
            // if nothing found return -1;
            return -1;
        }

        // insert item at position
        void insert(T item, size_t pos){
            // if index out of bounds
            if (pos > capacity || pos < 0){
                throw std::invalid_argument("index out of bounds");
            }
            size ++ ;                   // increaes size first to make the extra room for shifting
            if (full()){                // increae capacity if needed
                resize();
            }
            shiftItemsUp(pos);          // move everything over to make room if needed
            array[pos] = item;          // insert item
        }

        T remove(T item){
            // find the item first and return that position
            int pos = find(item);
            // if found then shift
            if (pos > -1){              // if a valid position request
                T item = array[pos];    // get item
                shiftItemsDown(pos);    // need to resize array
                size -- ;               // reduce size of array
                return item;            // retun the removed item
            }
            throw std::invalid_argument("item not in array");
        }
        
        // remove an item via its position in the array 
        T remove (size_t pos){  
            if (pos <= size){           // if a valid position request
                T item = array[pos];    // need to resize array
                shiftItemsDown(pos);    // and shift everything down 1 spot that was after this item
                size -- ;               // reduce size of array
                return item;            // retun the removed item
            }
            throw std::invalid_argument("item not in array");            
        }

        // for operations that remove items from the array
        void shiftItemsDown(size_t pos){
            size_t index = pos;                                 // set index to the current elelment being removed
            for (size_t i = 0 ; i < size - pos - 1; i ++ ){     // iterate for the distance from current position to end of array (to where the end of values are located anyway) - 1 for decreased size of array
                array[index] = array[index + 1];                // set the current item equal to the next item
                index ++;                                       // repeat ^
            }
        }

        // for operations that add items to the array
        void shiftItemsUp(size_t pos){
            // iterate backwards? yee
            size_t index = size;
            for (size_t i = size ; i > pos ; i -- ){
                array[index] = array[index - 1];
                index --;
            }
        }

        // remove duplicates from the list
        void removeDuplicates(){
            size_t index = 0;                                   // start looking from the front of the array
            T current_item = array[index];                      // current item will start at the front
            for (size_t i = index + 1 ; i < size; i ++ ){       // iterate through list (+1 so the current item doesn't check itself)
                T array_item = array[i];                        // the current array item (for debugging)
                if (current_item == array_item){                // if the current item equals anything in the remainder of the array
                    remove(current_item);                       // remove the current item
                    index = 0;                                  // reset the idnex to 0 to start a new search for duplicates
                    current_item = array[index];                // get new current item      
                }                                               
            }
            if (size == 2){                                     // get any stragglers if array drops to size 2 / since the range of the for loop above stops working at 2 items. 
                if (array[0] == array[1]){
                    remove(array[0]);
                }
            }
        }
           

        // reverse items in a list
        void reverse(){
            T* temp = new T[size];                               // set up temp array
            size_t index = 0;                                    // index for temp array to start at front
            for (size_t i = size ; i > 0 ; i -- ){               // reverse iterate through current array
                temp[index] = array[i-1];                        // place items from back of current array into front of temp
                index ++;                                        // increment temp index
            }
            array = temp;                                        // set old array pointer equal to the temp 
        }

        // print list contents
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

        // operator overload for []
		T& operator[](int index)
		{
			return array[index];
		}

};

#endif
