#ifndef ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H

#include <iostream>
#include "heap.h"

template <typename T> class MaxHeap;

template <typename T>
std::ostream &operator<<(std::ostream &, const MaxHeap<T> &);

template <typename T>
class MaxHeap : public Heap<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const MaxHeap<T> &);
public:
    MaxHeap():
        data(new std::vector<T>()) { };
    explicit MaxHeap(const std::vector<T> &arr);  // heapify
    MaxHeap(const MaxHeap<T> &rhs);
    MaxHeap &operator=(const MaxHeap<T> &rhs);

    bool isEmpty() const override { return data -> empty(); }
    int getSize() const override { return data -> size(); };
    T getTop() const override;

    void add(const T &e) override;
    T extractTop() override;
    T replace(const T &e) override;

    ~MaxHeap() override { delete data; }
private:
    std::vector<T> *data;

    int parent(int idx) const;
    int leftChild(int idx) const { return idx * 2 + 1; };
    int rightChild(int idx) const { return idx * 2 + 2; };

    void siftUp(int idx) override;
    void siftDown(int idx) override;
    void swap(MaxHeap<T> &rhs);
};

// heapify
template<typename T>
MaxHeap<T>::MaxHeap(const std::vector<T> &arr) {
    data = new std::vector<T>(arr);
    for (int i = parent(arr.size() - 1); i >= 0; i--)
        siftDown(i);
}

template<typename T>
MaxHeap<T>::MaxHeap(const MaxHeap<T> &rhs) {
    auto size = rhs.data -> size();
    data = new std::vector<T>(size);
    for (auto i = 0; i < size; i++)
        (*data)[i] = (*rhs.data)[i];
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
T MaxHeap<T>::getTop() const {
    if (data -> size() == 0)
        throw std::runtime_error("当前堆为空！");

    return (*data)[0];
}

template<typename T>
void MaxHeap<T>::siftUp(int idx) {
    while (idx > 0) {
        auto pi = parent(idx);
        if ((*data)[idx] > (*data)[pi]) {
            std::swap((*data)[idx], (*data)[pi]);
            idx = pi;
        }
        else
            break;
    }
}

template<typename T>
void MaxHeap<T>::add(const T &e) {
    data -> push_back(e);
    siftUp(data -> size() - 1);
}

template<typename T>
void MaxHeap<T>::siftDown(int idx) {
    auto size = data -> size();
    while (leftChild(idx) < size) {
        auto j = leftChild(idx);
        if (j + 1 < size && (*data)[j + 1] > (*data)[j])  // 比较左右孩子
            j++;  // 指向右孩子
        if ((*data)[idx] >= (*data)[j])  // 比较当前结点和其较大的孩子
            break;
        std::swap((*data)[idx], (*data)[j]);
        idx = j;
    }
}

template<typename T>
T MaxHeap<T>::extractTop() {
    auto ret = getTop();
    std::swap((*data)[0], (*data)[data -> size() - 1]);
    data -> pop_back();
    siftDown(0);

    return ret;
}

template<typename T>
T MaxHeap<T>::replace(const T &e) {
    auto ret = getTop();
    (*data)[0] = e;
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
    auto size = rhs.getSize();
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

#endif //ALGORITHM_TEMPLATE_CPP_MAX_HEAP_H
