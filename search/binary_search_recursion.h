#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_RECURSION_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_RECURSION_H

#include <vector>

class BinarySearchRecursion {
public:
    BinarySearchRecursion() = delete;

    template <typename T>
    static int search(const std::vector<T> &data, const T &target);  // 二分查找值为target的元素对应下标，不存在返回-1

private:
    template <typename T>
    static int search(const std::vector<T> &data, int l, int r, const T &target);
};

template<typename T>
int BinarySearchRecursion::search(const std::vector<T> &data, const T &target) {
    return search(data, 0, data.size() - 1, target);
}

template<typename T>
int BinarySearchRecursion::search(const std::vector<T> &data, int l, int r, const T &target) {
    if (l > r)
        return -1;

    auto mid = l + (r - l) / 2;
    if (data[mid] == target)
        return mid;
    if (data[mid] < target)
        return search(data, mid + 1, r, target);
    return search(data, l, mid - 1, target);  // data[mid] > target
}

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_RECURSION_H
