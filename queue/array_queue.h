#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_QUEUE_H

#include "../array/lazy_dynamic_array.h"
#include "queue.h"
#include <memory>
#include <iostream>

template <typename T>
class ArrayQueue;

template <typename T>
std::ostream &operator<<(std::ostream &, const ArrayQueue<T> &);

template <typename T>
class ArrayQueue : public Queue<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const ArrayQueue<T> &arrayQueue);
public:
    ArrayQueue():
        arr(new LasyDynamicArray<T>()) { }
    ArrayQueue(int capacity):
        arr(new LasyDynamicArray<T>(capacity)) { }
    bool isEmpty() const { return arr -> isEmpty(); }
    int getsize() const { return arr -> getSize(); }
    int getCapacity() const { return arr -> getCapacity(); }
    T getFront() const { return arr -> getFirst(); }
    void enqueue(const T &e) { arr -> addLast(e); };
    void dequeue() { arr -> removeFirst(); };
protected:
    std::unique_ptr<LasyDynamicArray<T>> arr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayQueue<T> &arrayQueue) {
    int size = arrayQueue.arr -> getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 队列信息
    os << "队列的长度：" << size << "，"
       << "队列的容量：" << arrayQueue.getCapacity() << '\n'
       << "队列的内容：" << "queue front[";
    for (int i = 0; i < size; i++) {
        os << (*arrayQueue.arr)[i];
        if (i != size - 1)
            os << ", ";
    }
    os << "]tail\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_QUEUE_H
