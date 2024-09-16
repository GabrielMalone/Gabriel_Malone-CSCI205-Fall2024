#include "Deque.h"
#include <math.h>
#include <cassert>
#include <string>
#include <iostream>

// Creates a Deque with default capacity of 100 items
template <typename T>
Deque<T>::Deque(){
	capacity 	= 100;			// default capacity
	size 		= 0;
	front_index = 0;
	back_index 	= capacity - 1; // back index points to last item in array
	array = new T[capacity]{};	// create dynamic memory for array of template type T
}

// Creates a Deque with given capacity (size of underlying array)
template <typename T>
Deque<T>::Deque(int cap){
	capacity 	= cap;			// set capacity
	size 		= 0;
	front_index = 0;
	back_index 	= capacity - 1;	// back index points to last item in array
	// =====================================================
	// || TO DO: Create dynamic memory for the array of T ||
	// =====================================================
	array = new T[capacity]{}; // curly braces to initialize to default values / may impact performance
}

// Frees dynamic memory
template <typename T>
Deque<T>::~Deque(){
	// ==========================================
	// || TO DO #1: De-allocate dynamic memory ||
	// ==========================================
	delete[] array;
	array = nullptr; // if don't do this, the memory that was just freed is still pointed to. can cause issues.
	size = 0;
	//std::cout << "destructor called" << std::endl;
}

// Pushes an item to the front of the deque
template <typename T>
void Deque<T>::push_front(T item){
	// ==================================
	// || TO DO #2: Handle wrap around ||
	// ==================================
	if (front_index > capacity - 1) 			// minus 1 for index = 0
	{
		front_index = front_index % capacity; 	// if over the capacity, start back at the front / 0
	}
	array[front_index++] = item;				// add item to front of array
	size++;										// increment size
}

// Pushes an item to the back of the deque
template <typename T>
void Deque<T>::push_back(T item){
	// ==================================
	// || TO DO #3: Handle wrap around ||
	// ==================================
	// if index reaches below zero 
	// e.g. -1, then should wrap around to the other end (original back index -> capacity - 1)
	if (back_index < 0)
	{	
		if (abs(back_index) > capacity - 1){			// if back index has gone into the negative beyond the capacity of array
			back_index = abs(back_index) % capacity;	// wrap the back index back around to the end of the array
		} else { 
			back_index = capacity - abs(back_index);	// otherwise, if the back index has gone into the negative within capacity
		}												// just take the abs value of the back index from capacity to wrap it around
	}
	array[back_index--] = item;	// add item to back of array
	size++;						// increment size
}

// Removes the item at the front of the deque and returns it
template <typename T>
T Deque<T>::remove_front(){
	// ==================================
	// || TO DO #4: Handle wrap around ||
	// ==================================
	front_index -- ;				// shift front index back
	size--;							// decrement size
	// if index reaches below zero and there are still items in array (size > 0) 
	// then wrap around to other end like push_back logic above ^
	if (front_index < 0)
	{
		if (abs(front_index) > capacity -1){
			front_index = abs(front_index) % capacity;
		} else {
			front_index = capacity - (abs(front_index));
		}
	}
	T temp = array[front_index];	// get item at front of array
	return temp;					// return item
	
}

// Removes the item at the back of the deque and returns it
template <typename T>
T Deque<T>::remove_back(){
	// ==================================
	// || TO DO #5: Handle wrap around ||
	// ==================================
	back_index ++;
	size--;										// decrement size
	if (back_index > capacity - 1) 				// minus 1 for index = 0
	{
		back_index = back_index % capacity; 	// if over the capacity, start back at the front / 0
	}
	T temp = array[back_index];					// get item at back of array
						
	return temp;								// return item
}

// Returns whether or not the deque is full
template <typename T>
bool Deque<T>::is_full(){
	return size == capacity;		// if size == capacity, then the deque is full
}

// Returns whether or not the deque is empty
template <typename T>
bool Deque<T>::is_empty(){
	return size == 0;				// if size == 0, then the deque is empty
}

// member functions defined outside the class need their own template declaration
template <typename T>
T& Deque<T>::operator[](int index) // now returns a T&
{
    assert(index >= 0 && index < capacity);
    return array[index];
}