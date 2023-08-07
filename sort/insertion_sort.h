//
// Created by Anton Liu on 2023/8/7.
//

#ifndef ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H
#define ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H

#include <vector>

template <typename T>
class InsertionSort {
public:
    InsertionSort() = delete;  // 删除默认构造函数，该类不需要构造对象
    static void sort(std::vector<T> &arr);  // 排序(默认升序)
};

template<typename T>
void InsertionSort<T>::sort(std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        T e = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > e; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = e;
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H
