#ifndef ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H

#include <iostream>
#include "heap.h"
#include "../array/lazy_dynamic_array.h"

template <typename T> class MaxHeap;

template <typename T>
std::ostream &operator<<(std::ostream &, const MaxHeap<T> &);

template <typename T>
class MaxHeap : public Heap<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const MaxHeap<T> &);
public:
    MaxHeap():
        data(new LazyDynamicArray<T>()) { };
    explicit MaxHeap(int capacity):
        data(new LazyDynamicArray<T>(10)) { };
    MaxHeap(const LazyDynamicArray<T> &arr);  // heapify
    MaxHeap(const MaxHeap<T> &rhs);
    MaxHeap &operator=(const MaxHeap<T> &rhs);

    bool isEmpty() const override { return data -> isEmpty(); }
    int getSize() const override { return data -> getSize(); };
    T findMax() const override;

    void add(const T &e) override;
    T extractMax() override;
    T replace(const T &e) override;

    ~MaxHeap() override;
private:
    int parent(int idx) const override;
    int leftChild(int idx) const override { return idx * 2 + 1; };
    int rightChild(int idx) const override { return idx * 2 + 2; };
    void siftUp(int idx) override;
    void siftDown(int idx) override;
    void swap(MaxHeap<T> &rhs);

private:
    LazyDynamicArray<T> *data;
};

template<typename T>
MaxHeap<T>::~MaxHeap() {
    delete data;
}

// heapify
template<typename T>
MaxHeap<T>::MaxHeap(const LazyDynamicArray<T> &arr) {
    data = new LazyDynamicArray<T>(arr);
    for (int i = parent(arr.getSize() - 1); i >= 0; i--)
        siftDown(i);
}

template<typename T>
MaxHeap<T>::MaxHeap(const MaxHeap<T> &rhs) {
    data = new LazyDynamicArray<T>(rhs.getSize());
    for (int i = 0; i < rhs.getSize(); i++)
        data[i] = rhs.data[i];
}

template<typename T>
void MaxHeap<T>::swap(MaxHeap<T> &rhs) {
    std::swap(data, rhs.data);
}

template<typename T>
MaxHeap<T> &MaxHeap<T>::operator=(const MaxHeap<T> &rhs) {
    MaxHeap<T>(rhs).swap(*this);
    return *this;
}


template<typename T>
T MaxHeap<T>::findMax() const {
    if (data -> getSize() == 0)
        throw std::runtime_error("当前堆为空！");

    return data -> get(0);
}

template<typename T>
void MaxHeap<T>::siftUp(int idx) {
    while (idx > 0) {
        int pi = parent(idx);
        if (data -> get(idx) > data -> get(pi)) {
            data -> swap(idx, pi);
            idx = pi;
        }
        else
            break;
    }
}

template<typename T>
void MaxHeap<T>::add(const T &e) {
    data -> addLast(e);
    siftUp(data -> getSize() - 1);
}

template<typename T>
void MaxHeap<T>::siftDown(int idx) {
    while (leftChild(idx) < data -> getSize()) {
        int j = leftChild(idx);
        if (j + 1 < data -> getSize() && data -> get(j + 1) > data -> get(j))  // 比较左右孩子
            j++;  // 指向右孩子
        if (data -> get(idx) > data -> get(j))  // 比较当前结点和其较大的孩子
            break;
        data -> swap(idx, j);
        idx = j;
    }
}

template<typename T>
T MaxHeap<T>::extractMax() {
    T ret = findMax();
    data -> swap(0, data -> getSize() - 1);
    data -> removeLast();
    siftDown(0);

    return ret;
}

template<typename T>
T MaxHeap<T>::replace(const T &e) {
    T ret = findMax();
    data -> set(0, e);
    siftDown(0);

    return ret;
}

template<typename T>
int MaxHeap<T>::parent(int idx) const {
    if (idx == 0)
        throw std::runtime_error("index-0没有父结点");

    return (idx - 1) / 2;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const MaxHeap<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << "堆的大小：" << size << "\n"
       << "堆的内容(数组表示)：" << "\nindex: [";

    for (int i = 0; i < size; i++) {
        if (i != size - 1)
            os << i << ", ";
        else
            os << i << "]\n";
    }
    os << "value: [";

    if (size == 0) {
        os << "]\n";
    }
    else {
        os << rhs.data -> get(0);
        for (int i = 1; i < size; i++)
            os << ", " << rhs.data -> get(i);
        os << "]\n";
    }

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H
