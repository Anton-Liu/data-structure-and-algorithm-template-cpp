#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_QUEUE_H

#include "../linked_list/single_linked_list_with_tail_pointer.h"
#include "queue.h"
#include <iostream>

/**
 * 使用带尾指针的单链表实现
 */

template <typename T>
class LinkedListQueue;

template <typename T>
std::ostream &operator<<(std::ostream &, const LinkedListQueue<T> &);

template <typename T>
class LinkedListQueue : public Queue<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LinkedListQueue<T> &arrayQueue);
public:
    LinkedListQueue():
            data(new SingleLinkedListWithTailPointer<T>()) { }

    LinkedListQueue(const LinkedListQueue<T> &rhs):
            data(new SingleLinkedListWithTailPointer<T>(*rhs.data)) { }
    LinkedListQueue<T> &operator=(const LinkedListQueue &rhs);

    int getSize() const override { return data -> getSize(); }
    bool isEmpty() const override { return data -> isEmpty(); }
    T getFront() const override { return data -> getFirst(); }

    void enqueue(const T &e) override { data -> addLast(e); };
    void dequeue() override { data -> removeFirst(); };

    void swap(LinkedListQueue<T> &rhs);

    virtual ~LinkedListQueue() { delete data; };
private:
    SingleLinkedListWithTailPointer<T> *data;
};

template<typename T>
void LinkedListQueue<T>::swap(LinkedListQueue<T> &rhs) {
    using std::swap;
    swap(data, rhs.data);
}

template<typename T>
LinkedListQueue<T> &LinkedListQueue<T>::operator=(const LinkedListQueue &rhs) {
    LinkedListQueue<T>(rhs).swap(*this);
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedListQueue<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 队列信息
    os << "队列的长度：" << size << "\n"
       << "队列的内容：" << "queue front[";
    auto tmp = rhs;
    for (int i = 0; i < size; i++) {
        os << tmp.getFront();
        tmp.dequeue();
        if (i != size - 1)
            os << ", ";
    }
    os << "]tail\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}


#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_QUEUE_H
