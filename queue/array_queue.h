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
            data(LazyDynamicArray<T>()) { }
    ArrayQueue(int capacity):
            data(LazyDynamicArray<T>(capacity)) { }

    bool isEmpty() const override { return data.isEmpty(); }
    int getSize() const override { return data.getSize(); }
    int getCapacity() const override { return data.getCapacity(); }
    T getFront() const override { return data.getFirst(); }

    void enqueue(const T &e) override { data.addLast(e); };
    void dequeue() override { data.removeFirst(); };
protected:
    LazyDynamicArray<T> data;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayQueue<T> &arrayQueue) {
    int size = arrayQueue.data.getSize();
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
        os << (arrayQueue.data)[i];
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
