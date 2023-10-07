#ifndef ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H
#define ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H

#include <vector>

template <typename T>
class InsertionSort {
public:
    InsertionSort() = delete;  // 删除默认构造函数，该类不需要构造对象

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
    static void sort(std::vector<T> &arr, int l, int r);
};

template<typename T>
void InsertionSort<T>::sort(std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        auto e = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > e; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = e;
    }
}

template<typename T>
void InsertionSort<T>::sort(std::vector<T> &arr, int l, int r) {
    if (l >= r)
        return;
    if (r >= arr.size())
        throw std::runtime_error("索引超过数组范围！");

    for (int i = l + 1; i <= r; i++) {
        auto e = arr[i];
        int j;
        for (j = i - 1; j >= l && arr[j] > e; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = e;
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_INSERTION_SORT_H
