#ifndef ALGORITHM_TEMPLATE_CPP_DEQUE_H
#define ALGORITHM_TEMPLATE_CPP_DEQUE_H

template <typename T>
class Deque {
public:
    virtual bool isEmpty() const = 0;
    virtual T getFront() const = 0;
    virtual T getLast() const = 0;
    virtual int getCapacity() const = 0;
    virtual int getSize() const = 0;

    virtual void addFront(const T &e) = 0;
    virtual void addLast(const T &e) = 0;
    virtual void removeFront() = 0;
    virtual void removeLast() = 0;
    virtual ~Deque() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_DEQUE_H
