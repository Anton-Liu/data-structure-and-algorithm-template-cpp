#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_H

template <typename T>
class LinkedList {
public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool contains(const T &e) const = 0;
    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;

    virtual void addFirst(const T &e) = 0;
    virtual void addLast(const T &e) = 0;
    virtual void removeFirst() = 0;
    virtual void removeLast() = 0;

    virtual ~LinkedList() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_H
