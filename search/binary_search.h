#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_H

#include <vector>

class BinarySearch {
public:
    BinarySearch() = delete;

    template <typename T>
    static int search(const std::vector<T> &data, const T &target);  // 二分查找值为target的元素对应下标，不存在返回-1

    // 另一种循环不变量的实现方式
    template <typename T>
    static int search2(const std::vector<T> &data, const T &target);  // 二分查找值为target的元素对应下标，不存在返回-1
};

template<typename T>
int BinarySearch::search(const std::vector<T> &data, const T &target) {
    // 在[l, r]范围内查找target
    int l = 0;
    int r = data.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (data[mid] == target)
            return mid;
        if (data[mid] < target)
            l = mid + 1;
        else  // data[mid] > target
            r = mid - 1;
    }
    return -1;
}

template<typename T>
int BinarySearch::search2(const std::vector<T> &data, const T &target) {
    // 在[l, r)范围内查找target
    int l = 0;
    int r = data.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] == target)
            return mid;
        if (data[mid] < target)
            l = mid + 1;  // 继续在[mid + 1, r)内寻找解
        else
            r = mid;  // 继续在[l, mid)内寻找解
    }
    return -1;
}

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_H
