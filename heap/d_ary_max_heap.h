#ifndef ALGORITHM_TEMPLATE_CPP_D_ARY_MAX_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_D_ARY_MAX_HEAP_H

#include <iostream>
#include "heap.h"

template <typename T> class DAryMaxHeap;

template <typename T>
std::ostream &operator<<(std::ostream &, const DAryMaxHeap<T> &);

template <typename T>
class DAryMaxHeap : public Heap<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const DAryMaxHeap<T> &);
public:
    DAryMaxHeap():
            data(new std::vector<T>()), d(2) { };
    explicit DAryMaxHeap(int d):
            data(new std::vector<T>()), d(d) { };
    explicit DAryMaxHeap(const std::vector<T> &arr, int d = 2);  // heapify
    DAryMaxHeap(const DAryMaxHeap<T> &rhs);
    DAryMaxHeap &operator=(const DAryMaxHeap<T> &rhs);

    bool isEmpty() const override { return data -> empty(); }
    int getSize() const override { return data -> size(); };
    T getTop() const override;

    void add(const T &e) override;
    T extractTop() override;
    T replace(const T &e) override;

    ~DAryMaxHeap() override { delete data; }
private:
    int parent(int idx) const;
    void siftUp(int idx) override;
    void siftDown(int idx) override;
    void swap(DAryMaxHeap<T> &rhs);

private:
    std::vector<T> *data;
    int d;
};

// heapify
template<typename T>
DAryMaxHeap<T>::DAryMaxHeap(const std::vector<T> &arr, int d) {
    this -> d = d;
    data = new std::vector<T>(arr);
    for (int i = parent(arr.size() - 1); i >= 0; i--)
        siftDown(i);
}

template<typename T>
DAryMaxHeap<T>::DAryMaxHeap(const DAryMaxHeap<T> &rhs) {
    int size = rhs.data -> size();
    d = rhs.d;
    data = new std::vector<T>(size);
    for (int i = 0; i < size; i++)
        (*data)[i] = (*rhs.data)[i];
}

template<typename T>
void DAryMaxHeap<T>::swap(DAryMaxHeap<T> &rhs) {
    using std::swap;
    swap(data, rhs.data);
    swap(d, rhs.d);
}

template<typename T>
DAryMaxHeap<T> &DAryMaxHeap<T>::operator=(const DAryMaxHeap<T> &rhs) {
    DAryMaxHeap<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
T DAryMaxHeap<T>::getTop() const {
    if (data -> size() == 0)
        throw std::runtime_error("当前堆为空！");

    return (*data)[0];
}

template<typename T>
void DAryMaxHeap<T>::siftUp(int idx) {
    while (idx > 0) {
        int pi = parent(idx);
        if ((*data)[idx] > (*data)[pi]) {
            std::swap((*data)[idx], (*data)[pi]);
            idx = pi;
        }
        else
            break;
    }
}

template<typename T>
void DAryMaxHeap<T>::add(const T &e) {
    data -> push_back(e);
    siftUp(data -> size() - 1);
}

template<typename T>
void DAryMaxHeap<T>::siftDown(int idx) {
    int size = data -> size();
    int leftmostChild = idx * d + 1;
    int rightmostChild = idx * d + d;
    while (leftmostChild < size) {
        int maxChild = leftmostChild;
        for (int i = leftmostChild + 1; i <= rightmostChild; i++)
            if (i < size && (*data)[i] > (*data)[maxChild])
                maxChild = i;  // 指向值最大的孩子
        if ((*data)[idx] >= (*data)[maxChild])  // 比较当前结点和最大的孩子
            break;
        std::swap((*data)[idx], (*data)[maxChild]);
        idx = maxChild;
        leftmostChild = idx * d + 1;
        rightmostChild = idx * d + d;
    }
}

template<typename T>
T DAryMaxHeap<T>::extractTop() {
    T ret = getTop();
    std::swap((*data)[0], (*data)[data -> size() - 1]);
    data -> pop_back();
    siftDown(0);

    return ret;
}

template<typename T>
T DAryMaxHeap<T>::replace(const T &e) {
    T ret = getTop();
    (*data)[0] = e;
    siftDown(0);

    return ret;
}

template<typename T>
int DAryMaxHeap<T>::parent(int idx) const {
    if (idx == 0)
        throw std::runtime_error("index-0没有父结点");

    return (idx - 1) / d;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const DAryMaxHeap<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << rhs.d << "叉堆的大小：" << size << "\n"
       << rhs.d << "叉堆的内容(数组表示)：" << "\nindex: [";
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

#endif //ALGORITHM_TEMPLATE_CPP_D_ARY_MAX_HEAP_H
