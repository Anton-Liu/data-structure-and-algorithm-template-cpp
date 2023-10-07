#ifndef ALGORITHM_TEMPLATE_CPP_PRIORITY_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_PRIORITY_QUEUE_H

#include "queue.h"
#include "../heap/max_heap.h"

template <typename T> class PriorityQueue;

template <typename T>
std::ostream &operator<<(std::ostream &, const PriorityQueue<T> &);

template <typename T>
class PriorityQueue : public Queue<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const PriorityQueue<T> &);
public:
    PriorityQueue():
        heap(MaxHeap<T>()) { }
    explicit PriorityQueue(int capacity):
        heap(MaxHeap<T>(capacity)) { }
    PriorityQueue(const PriorityQueue &rhs):
        heap(rhs.heap) { }
    PriorityQueue<T> &operator=(const PriorityQueue<T> &rhs);

    bool isEmpty() const override { return heap.isEmpty(); };
    int getSize() const override { return heap.getSize(); };
    T getFront() const override { return heap.getTop(); }

    void enqueue(const T &e) override { heap.add(e); };
    void dequeue() override { heap.extractTop(); };
    void swap(PriorityQueue<T> &rhs) { std::swap(heap, rhs.heap); }

private:
    MaxHeap<T> heap;
};

template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> &rhs) {
    PriorityQueue<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const PriorityQueue<T> &rhs) {
    auto size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';


    // 队列信息
    os << "队列的长度：" << size << "\n"
       << "队列的内容：" << "queue front[";

    MaxHeap<T> tmp(rhs.heap);
    if (size == 0) {
        os << "]\n";
    }
    else {
        for (int i = 0; i < size; i++) {
            if (i != size - 1)
                os << tmp.extractTop() << ", ";
            else
                os << tmp.extractTop() << "]\n";
        }
    }

        // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_PRIORITY_QUEUE_H
