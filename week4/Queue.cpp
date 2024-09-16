#include "Queue.h"

// place item at back of queue
template <typename T>
void Queue<T>::enqueu(T item){
    Deque<T>::push_back(item);
}

// take item from front and put in back
// head and tail need to be tracked?
template <typename T>
void Queue<T>::dequeue(){
    Deque<T>::remove_front();
}