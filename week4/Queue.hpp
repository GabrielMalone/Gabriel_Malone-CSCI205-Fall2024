//
// Created by Gabriel Malone on 9/17/24.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Deque.hpp"

template <typename T> class Queue {

private:
	// instantiate a Deque from which to call deque methods
	Deque<T> stack_deque;

public:
	// my IDE suggested this
	Queue()= default;

	// overloaded constructor
	Queue(size_t cap){
		stack_deque.setCapacity(cap);
	}

	// show what is at front of queue
	T front_element(){
		return stack_deque.show_front();
	}

	// show what is at front of queue
	T back_element(){
		return stack_deque.show_back();
	}

	// place element at back of queue
	void enqueue(T item){
		stack_deque.push_front(item);
	}

	// pop element from front of queue
	T dequeue(){
		return stack_deque.pop_front();
	}

	// get the current number of elements in the stack
	size_t queue_size(){
		return stack_deque.array_size();
	}

	// get the current capacity of the stack
	size_t queue_capacity(){
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
