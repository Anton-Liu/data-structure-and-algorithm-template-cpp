#ifndef ALGORITHM_TEMPLATE_CPP_MERGE_SORT_WITH_OPTIMIZATION_H
#define ALGORITHM_TEMPLATE_CPP_MERGE_SORT_WITH_OPTIMIZATION_H

#include <vector>
#include <algorithm>
#include "insertion_sort.h"

template <typename T>
class MergeSortWithOptimization {
public:
    MergeSortWithOptimization() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)

private:
    static void sort(std::vector<T> &arr, int l, int r, std::vector<T> &tmp);
    static void merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp);
};

template<typename T>
void MergeSortWithOptimization<T>::sort(std::vector<T> &arr) {
    // 优化：只在排序开始时拷贝一次数组
    // 如果每次都在merge中拷贝，每个非叶结点都会拷贝一次
    std::vector<T> tmp(arr.size());
    sort(arr, 0, arr.size() - 1, tmp);
}

template<typename T>
void MergeSortWithOptimization<T>::sort(std::vector<T> &arr, int l, int r, std::vector<T> &tmp) {
    // 优化：插入排序
    // 数组元素数目越少，越接近有序数组
    if (r - l <= 15) {
        InsertionSort<T>::sort(arr, l, r);
        return;
    }

    auto mid = l + (r - l) / 2;
    sort(arr, l, mid, tmp);
    sort(arr, mid + 1, r, tmp);

    // 优化：增加if判断
    // 若arr[mid] <= arr[mid + 1]，没必要进行merge
    // 优化后，对于有序数组，归并排序时间复杂度为O(n)
    if (arr[mid] > arr[mid + 1])
        merge(arr, l, mid, r, tmp);
}

template<typename T>
void MergeSortWithOptimization<T>::merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp) {
    // 把arr[l..r]拷贝到tmp[l..r]上
    std::copy(arr.begin() + l, arr.begin() + r + 1, tmp.begin() + l);

    auto i = l;
    auto j = mid + 1;

    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = tmp[j];
            j++;
        }
        else if (j > r) {
            arr[k] = tmp[i];
            i++;
        }
        else if (tmp[i] <= tmp[j]) {
            arr[k] = tmp[i];
            i++;
        }
        else {
            arr[k] = tmp[j];
            j++;
        }
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_MERGE_SORT_WITH_OPTIMIZATION_H
