#ifndef ALGORITHM_TEMPLATE_CPP_HEAPSORT_H
#define ALGORITHM_TEMPLATE_CPP_HEAPSORT_H

#include <vector>
#include "../heap/max_heap.h"
#include <iostream>

template <typename T>
class Heapsort {
public:
    Heapsort() = delete;  // 删除默认构造函数，该类不需要构造对象
    static void sort(std::vector<T> &arr);  // 排序(默认升序)

private:
    // data[0, n)形成的最大堆中，对索引idx的元素进行siftDown
    static void siftDown(std::vector<T> &arr, int n, int idx);
};

template<typename T>
void Heapsort<T>::siftDown(std::vector<T> &arr, int n, int idx) {
    while (idx * 2 + 1 < n) {
        int j = idx * 2 + 1;
        if (j + 1 < n && arr[j + 1] > arr[j])  // 比较左右孩子
            j++;  // 指向右孩子
        if (arr[idx] > arr[j])  // 比较当前结点和其较大的孩子
            break;
        std::swap(arr[idx], arr[j]);
        idx = j;
    }
}

template<typename T>
void Heapsort<T>::sort(std::vector<T> &arr) {
    // 最简单的实现方法
//    MaxHeap<T> maxHeap;
//    for (auto e : arr)
//        maxHeap.add(e);
//
//    for (int i = 0; i < arr.size(); i++)
//        arr[arr.size() - i - 1] = maxHeap.extractMax();

    // 原地堆排序
    if (arr.size() <= 1)
        return;

    for (int i = (arr.size() - 2) / 2; i >= 0; i--)
        siftDown(arr, arr.size(), i);

    for (int i = arr.size() - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        siftDown(arr, i, 0);
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_HEAPSORT_H
