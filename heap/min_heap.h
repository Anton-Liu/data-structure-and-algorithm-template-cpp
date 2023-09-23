#ifndef ALGORITHM_TEMPLATE_CPP_MIN_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_MIN_HEAP_H

#include <iostream>
#include "heap.h"

template <typename T> class MinHeap;

template <typename T>
std::ostream &operator<<(std::ostream &, const MinHeap<T> &);

template <typename T>
class MinHeap : public Heap<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const MinHeap<T> &);
public:
    MinHeap():
            data(new std::vector<T>()) { };
    explicit MinHeap(const std::vector<T> &arr);  // heapify
    MinHeap(const MinHeap<T> &rhs);
    MinHeap &operator=(const MinHeap<T> &rhs);

    bool isEmpty() const override { return data -> empty(); }
    int getSize() const override { return data -> size(); };
    T getTop() const override;

    void add(const T &e) override;
    T extractTop() override;
    T replace(const T &e) override;

    ~MinHeap() override { delete data; }
private:
    int parent(int idx) const override;
    int leftChild(int idx) const override { return idx * 2 + 1; };
    int rightChild(int idx) const override { return idx * 2 + 2; };
    void siftUp(int idx) override;
    void siftDown(int idx) override;
    void swap(MinHeap<T> &rhs);

private:
    std::vector<T> *data;
};


template<typename T>
int MinHeap<T>::parent(int idx) const {
    if (idx == 0)
        throw std::runtime_error("index-0没有父结点");

    return (idx - 1) / 2;
}

template<typename T>
MinHeap<T>::MinHeap(const std::vector<T> &arr) {
    data = new std::vector<T>(arr);
    for (int i = parent(arr.size() - 1); i >= 0; i--)
        siftDown(i);
}

template<typename T>
void MinHeap<T>::swap(MinHeap<T> &rhs) {
    std::swap(data, rhs.data);
}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap<T> &rhs) {
    int size = rhs.data -> size();
    data = new std::vector<T>(size);
    for (int i = 0; i < size; i++)
        (*data)[i] = (*rhs.data)[i];
}

template<typename T>
MinHeap<T> &MinHeap<T>::operator=(const MinHeap<T> &rhs) {
    MinHeap<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
T MinHeap<T>::getTop() const {
    if (data -> size() == 0)
        throw std::runtime_error("当前堆为空！");

    return (*data)[0];
}

template<typename T>
void MinHeap<T>::add(const T &e) {
    data -> push_back(e);
    siftUp(data -> size() - 1);
}

template<typename T>
T MinHeap<T>::extractTop() {
    T ret = getTop();

    std::swap((*data)[0], (*data)[data -> size() - 1]);
    data -> pop_back();
    siftDown(0);

    return ret;
}

template<typename T>
T MinHeap<T>::replace(const T &e) {
    T ret = getTop();

    (*data)[0] = e;
    siftDown(0);

    return ret;
}

template<typename T>
void MinHeap<T>::siftUp(int idx) {
    while (idx > 0) {
        int pi = parent(idx);
        if ((*data)[idx] < (*data)[pi]) {
            std::swap((*data)[idx], (*data)[pi]);
            idx = pi;
        }
        else
            break;
    }
}

template<typename T>
void MinHeap<T>::siftDown(int idx) {
    int size = data -> size();
    while (leftChild(idx) < size) {
        int j = leftChild(idx);
        if (j + 1 < size && (*data)[j + 1] < (*data)[j])  // 比较左右孩子
            j++;  // 指向右孩子
        if ((*data)[idx] <= (*data)[j])  // 比较当前结点和其较大的孩子
            break;
        std::swap((*data)[idx], (*data)[j]);
        idx = j;
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const MinHeap<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << "堆的大小：" << size << "\n"
       << "堆的内容(数组表示)：" << "\nindex: [";
    if (size == 0) {
        os << "]\n";
    }
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
        os << (*rhs.data)[0];
        for (int i = 1; i < size; i++)
            os << ", " << (*rhs.data)[i];
        os << "]\n";
    }

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_MIN_HEAP_H
