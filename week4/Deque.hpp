// GABRIEL MALONE / CSCI205 / LAB 3

#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>
#include <iomanip>

template <typename T> class Deque{
	private:
		//Private member variables to manage insertion and removal points
		size_t size = 0;		        // number of items in the deque
		size_t capacity = 100;	        // size of the array (Default = 100)
		size_t front = 0;		        // index of the front of the deque
		size_t back = capacity-1;       // 0 index adjust
		size_t head = 0;	            // index of the head of the list
		size_t tail = capacity - 1;		// index of the tail of the list
		T* array;			            // array to store items (pointer to type T, to be determined at run time)

		//Helper function to resize the array
		void resize(){
			if (size == capacity)
			{

				size_t old_capacity = capacity; // for resorting / unwrapping array on resize
				front = capacity;               // set front to the beginning of the new expansion
				capacity = capacity * 2;        // size of next array = double current array
				T* dbl_array_temp ;             // instantiate new array
				back = capacity - 1;            // back_index = capacity - 1
				tail = size - 1;                // new tail is the size of the previous array

				dbl_array_temp = new T[capacity];
				// copy contents from old array in order
				// start from the current head position to the end of the array
				for (int i = head; i < old_capacity; i ++)
				{
					// zero out the head position for the new array
					dbl_array_temp[i - head] = array[i];
				}
				// then get what was at the front of the array if head was not at front
				// and continue where left off from last loop
				for (int i = 0; i < head; i ++)
				{
					dbl_array_temp[i + (old_capacity - head)] = array[i];
				}
				head = 0; // re-set head back to front index
				// delete og array pointer
				delete [] array;
				// set array pointer to the new, bigger temp array
				array = dbl_array_temp;

			}
			// ANSWER: What is the big O notation for this function? How did you come to that conclusion?
				// Linear due to the one for-loop to copy contents of old array to new array
		}

	public:
		//Constructs a Deque with default capacity of 100 items
		Deque(){
			capacity= 100;
			array	= new T[capacity]; // create dynamic memory for array of template type T
		}					

		//Constructs a Deque with given capacity (size of underlying array)
		Deque(size_t cap){
			capacity 	= cap;			// set capacity
			size 		= 0;
			front       = 0;
			back 	    = capacity - 1;	// back index points to last item in array
			array = new T[capacity];
		}

		// Constructs a Deque with given array of items and size
		Deque(T* arr, size_t o_size){
			// ensure the array is not null. Throw an invalid argument exception if it is
			if (arr == nullptr)
			{
				throw std::invalid_argument("array is null");
			} else {
				// set the capacity to double the size of the array
				capacity = o_size * 2;
				T* temp_array = new T[capacity];
				// copy contents from old array
				for (int i = 0; i < o_size; i++) {
					temp_array[i] = arr[i];
				}
				// delete old pointer
				delete[] array;
				// point og array at temp array
				array = temp_array;
			}

		}

		//Free dynamic memory allocated for the Deque
		~Deque(){
			delete[] array;
		}

		// return capacity of array
		size_t getCapacity(){
			return capacity;
		}

		void setCapacity(size_t cap){
			this->capacity = cap;
		}

		//Adds an item to the front of the deque
		void push_front(T item){
			if (!this->full())                      // if array is not full
			{
				front = (front) % capacity;		    // if over the capacity, wrap
				array[front] = item;                // add item to front of array
				size++;                             // increase size of array
				front ++;

			} else {                                // if array full, resize
				this->resize();
				push_front(item);
			}
			// note: no need to check if you are at the end of the array
			// modulus division will take care of that for you
		}

		//Adds an item to the back of the deque
		void push_back(T item)	{
			// if array is not full, wrap around
			if (!this->full())
			{
				// wrap around if necessary
				back = (back + capacity) % capacity;
				// add item to back of array
				array[back] = item;
				// increment size
				size++;
				// decrement back index
				back -- ;
			} else {
				this->resize();
				push_back(item);
			}
		}

		//Removes the item at the front of the deque and returns it
		T pop_front(){
			T temp = array[front - 1];	                // get item at front of array (need to shift back to last item entered)
			front = (front - 1 + capacity) % capacity; 	// wrap around if necessary
			size -- ;				                    // decrement size
			return temp ;			                    // return item
		}

		//Removes the item at the back of the deque and returns it
		T pop_back(){
			back = (back + 1) % capacity; 	            // wrap around if necessary
			T temp = array[back];	                    // get item at back of array
			size -- ;				                    // decrement size
			return temp ;			                    // return item
		}

		void remove_head(){
			// move head forward
			head = ( head + 1 ) % capacity;
			// reduce size of array
			size -- ;
		}

		void remove_taIl(){
			// move tail back
			tail = ( tail - 1 + capacity ) % capacity ;
			// reduce size of array
			size -- ;
		}

		//Returns whether the deque is full
		bool full(){
			return size == capacity;
		}

		//Returns whether the deque is empty
		bool empty(){
			return size == 0;
		}

		//Returns the number of items in the deque
		size_t array_size(){
			return size;
		}

		T* get_array(){
			return array;
		}

		//show element at the front
		T show_front(){
			return array[front - 1]; // - 1 to adjust for the increment when pushing
		}

		//show element at the back
		T show_back(){
			return array[back + 1]; // +1 to adjust for decrement when pushing back
		}

		//show element at the head
		T show_head(){
			return array[head]; // - 1 to adjust for the increment when pushing
		}

		//show element at the tail
		T show_tail(){
			return array[tail]; // +1 to adjust for decrement when pushing back
		}

		// operator overload for []
		T& operator[](int index)
		{
			return array[index];
		}


};

#endif
