#include "Stack.h"

// push item using deque's pushback method
template <typename T>
void Stack<T>::push(T item){
    Deque<T>::push_back(item);   
}

// stack is LIFO
// peek returns element that is next to be removed
// this should be current last element in list
template <typename T>
T Stack<T>::peek(){
    return Deque<T>::array[Deque<T>::back_index+1];
}

// removes the last item put into the stack
// reduces size of stack by 1
template <typename T>
void Stack<T>::pop(){
    Deque<T>::remove_back(); 
}