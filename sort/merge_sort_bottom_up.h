#ifndef ALGORITHM_TEMPLATE_CPP_MERGE_SORT_BOTTOM_UP_H
#define ALGORITHM_TEMPLATE_CPP_MERGE_SORT_BOTTOM_UP_H

#include <vector>
#include <algorithm>

template <typename T>
class MergeSortBottomUp {
public:
    MergeSortBottomUp() = delete;

    static void sort(std::vector<T> &arr);
private:
    static void merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp);
};

template<typename T>
void MergeSortBottomUp<T>::sort(std::vector<T> &arr) {
    int n = arr.size();
    std::vector<T> tmp(n);

    // sz表示合并的区间长度
    for (int sz = 1; sz < n; sz += sz) {
        // 遍历两个合并区间的起始位置i
        // 合并arr[i, i + sz - 1]和arr[i + sz, MIN(i + sz + sz - 1, n - 1)]
        for (int i = 0; i + sz < n; i += sz + sz)
            if (arr[i + sz - 1] > arr[i + sz])  // 优化，必要时才merge
                merge(arr, i, i + sz - 1, std::min(i + sz + sz - 1, n - 1), tmp);
    }
}

template<typename T>
void MergeSortBottomUp<T>::merge(std::vector<T> &arr, int l, int mid, int r, std::vector<T> &tmp) {
    // 把arr[l..r]拷贝到tmp[l..r]上
    std::copy(arr.begin() + l, arr.begin() + r + 1, tmp.begin() + l);

    int i = l;
    int j = mid + 1;

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

#endif //ALGORITHM_TEMPLATE_CPP_MERGE_SORT_BOTTOM_UP_H
