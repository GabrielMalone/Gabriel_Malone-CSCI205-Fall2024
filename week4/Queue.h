#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template <typename T> class Queue : public Deque<T> {
    public:
        T* head;
        T* tail;
        void enqueu(T item);
        void dequeue();
};

#include "Queue.cpp"

#endif