#ifndef DEQUE_H
#define DEQUE_H

template <typename T> class Deque{	// template class. Type T is a placeholder that's defined at instantiation
	public:
		int size;					// tracks current queue size
		int capacity;				// tracks max queue capacity
		int front_index;			// tracks index of front of queue
		int back_index;				// tracks index of back of queue
		T* array;					// pointer to underlying array
		Deque();					//Constructs a Deque with default capacity of 100 items
		Deque(int cap);				//Constructs a Deque with given capacity (size of underlying array)
		Deque(const Deque&) = delete; // prevent copying // taken from learn.cpp
		Deque& operator=(const Deque&) = delete; // prevent copying // taken from learn.cpp
		~Deque();					//Frees dynamic memory
		void push_front(T item);	//Pushes an item to the front of the deque
		void push_back(T item);		//Pushes an item to the back of the deque
		T remove_front();			//Removes the item at the front of the deque and returns it
		T remove_back();			//Removes the item at the back of the deque and returns it
		bool is_full();				//Returns whether or not the deque is full
		bool is_empty();			//Returns whether or not the deque is empty
		T& operator[](int index); 	// templated operator[] function defined below
};

#include "Deque.cpp"				// do this to avoid linking errors
									// you could also copy the contents of Deque.cpp here
									// but that's not as clean
#endif
