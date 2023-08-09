#ifndef ALGORITHM_TEMPLATE_CPP_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_QUEUE_H

template <typename T>
class Queue {
public:
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual int getCapacity() const = 0;
    virtual T getFront() const = 0;
    virtual void enqueue(const T &e) = 0;
    virtual void dequeue() = 0;
    virtual ~Queue() { };
};

#endif //ALGORITHM_TEMPLATE_CPP_QUEUE_H
