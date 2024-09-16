#ifndef STACK_H
#define STACK_H

#include "Deque.h"

template <typename T> class Stack : public Deque<T> {
    public:
        T peek();
        void pop();
        void push(T item); 
};

#include "Stack.cpp"

#endif