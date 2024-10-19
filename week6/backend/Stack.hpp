//
// Created by Gabriel Malone on 9/17/24.
//

#ifndef STACK_HPP
#define STACK_HPP

#include "Deque.hpp"

template <typename T> class Stack {
private:
	// instantiate a Deque from which to call deque methods
	Deque<T> stack_deque;

public:

	Stack() = default; // my IDE suggested this

	// overloaded constructor
	Stack(size_t cap){
		stack_deque.setCapacity(cap);
	}

	// check out the next item to be popped
	T peek(){
		return stack_deque.show_front();
	}

	// pop the last item entered into the stack
	T pop(){
		return stack_deque.pop_front();
	}

	// push an item to the top of the stack
	void push(T item){
		stack_deque.push_front(item);
	}

	// get the current number of elements in the stack
	size_t stack_size(){
		return stack_deque.array_size();
	}

	// get the current capacity of the stack
	size_t stack_capacity(){
		return stack_deque.getCapacity();
	}

	// checks if array is empty
	bool is_empty(){
		return stack_deque.array_size() == 0;
	}

	// checks if stack is full
	bool is_full(){
		return stack_deque.array_size() == stack_deque.getCapacity();
	}

	// operator overload for []
	T& operator[](int index)
	{
		return stack_deque.get_array()[index];
	}
};


#endif
