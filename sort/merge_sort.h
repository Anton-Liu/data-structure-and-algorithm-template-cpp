#ifndef ALGORITHM_TEMPLATE_CPP_MERGE_SORT_H
#define ALGORITHM_TEMPLATE_CPP_MERGE_SORT_H

#include <vector>

template <typename T>
class MergeSort {
public:
    MergeSort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
private:
    static void sort(std::vector<T> &arr, int l, int r);
    static void merge(std::vector<T> &arr, int l, int mid, int r);
};

template<typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    sort(arr, 0, arr.size() - 1);
}

template<typename T>
void MergeSort<T>::sort(std::vector<T> &arr, int l, int r) {
    if (l >= r)
        return;

    int mid = l + (r - l) / 2;
    sort(arr, l, mid);
    sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

template<typename T>
void MergeSort<T>::merge(std::vector<T> &arr, int l, int mid, int r) {
    std::vector<T> tmp(arr.begin() + l, arr.begin() + r + 1);  // 拷贝未合并前的arr

    int i = l;
    int j = mid + 1;

    // 确定合并，arr[k]填
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = tmp[j - l];
            j++;
        }
        else if (j > r) {
            arr[k] = tmp[i - l];
            i++;
        }
        else if (tmp[i - l] <= tmp[j - l]) {
            arr[k] = tmp[i - l];
            i++;
        }
        else {
            arr[k] = tmp[j - l];
            j++;
        }
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_MERGE_SORT_H
