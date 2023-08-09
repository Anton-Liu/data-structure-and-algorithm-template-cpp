#ifndef ALGORITHM_TEMPLATE_CPP_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_QUEUE_H

template <typename T>
class Queue {
    virtual bool isEmpty() const = 0;
    virtual int getsize() const = 0;
    virtual int getCapacity() const = 0;
    virtual T getFront() const = 0;
    virtual void enqueue(const T &e) = 0;
    virtual void dequeue() = 0;
};

#endif //ALGORITHM_TEMPLATE_CPP_QUEUE_H
