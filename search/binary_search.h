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

    // >=target的最小值实现
    template <typename T>
    static int search3(const std::vector<T> &data, const T &target);  // 二分查找值为target的元素对应下标，不存在返回-1

    // upper，返回大于target值的最小值的索引
    // 若target值大于等于最后一个元素，则upper结果返回最后一个元素之后的索引(越界)
    // 因此结果的范围是：[0, data.size()]
    template <typename T>
    static int upper(const std::vector<T> &data, const T &target);

    // upperCeil，在可能含有重复的数组中
    // 1 若存在等于target的若干元素，返回最大(右)的索引
    // 2 若不存在等于target元素，返回upper
    template <typename T>
    static int upperCeil(const std::vector<T> &data, const T &target);

    // lowerCeil，在可能含有重复的数组中
    // 1 若存在等于target的若干元素，返回最小(左)的索引
    // 2 若不存在等于target元素，返回upper
    template <typename T>
    static int lowerCeil(const std::vector<T> &data, const T &target);

    // lower，返回小于target值的最大值的索引
    // 若target值小于等于第一个元素，则lower结果返回第一个元素之前的索引-1(越界)
    // 因此结果的范围是：[-1, data.size() - 1]
    template <typename T>
    static int lower(const std::vector<T> &data, const T &target);

    // upperFloor，在可能含有重复的数组中
    // 1 若存在等于target的若干元素，返回最大(右)的索引
    // 2 若不存在等于target元素，返回lower
    template <typename T>
    static int upperFloor(const std::vector<T> &data, const T &target);

    // lowerFloor，在可能含有重复的数组中
    // 1 若存在等于target的若干元素，返回最小(左)的索引
    // 2 若不存在等于target元素，返回lower
    template <typename T>
    static int lowerFloor(const std::vector<T> &data, const T &target);
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


template<typename T>
int BinarySearch::search3(const std::vector<T> &data, const T &target) {
    // 在[l, r]范围内查找target
    int l = 0;
    int r = data.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    return (l < data.size() && data[l] == target) ? l : -1;  // l和r必定相等，也可以返回r
}


template<typename T>
int BinarySearch::upper(const std::vector<T> &data, const T &target) {
    int l = 0;
    int r = data.size();

    // 在data[l, r]中寻找解(必定有解)
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] <= target)
            l = mid + 1;
        else  // data[mid] > target
            r = mid;  // data[r]本身可能就是答案
    }
    return l;  // l和r必定相等，也可以返回r
}

template<typename T>
int BinarySearch::upperCeil(const std::vector<T> &data, const T &target) {
    int u = upper(data, target);
    return (u - 1 >= 0 && data[u - 1] == target) ? u - 1 : u;
}

template<typename T>
int BinarySearch::lowerCeil(const std::vector<T> &data, const T &target) {
    int l = 0;
    int r = data.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (data[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;  // l和r必定相等，也可以返回r
}

template<typename T>
int BinarySearch::lower(const std::vector<T> &data, const T &target) {
    int l = -1;
    int r = data.size() - 1;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;  // 大坑！要保证l和r相邻时，
                                        // 计算得到的mid == r(上取整)
                                        // 这样才能保证每次查找过程的搜索空间在缩小
        if (data[mid] < target)
            l = mid;
        else  // data[mid] >= target
            r = mid - 1;
    }
    return l;  // l和r必定相等，也可以返回r
}

template<typename T>
int BinarySearch::upperFloor(const std::vector<T> &data, const T &target) {
    int l = -1;
    int r = data.size() - 1;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;  // 大坑！要保证l和r相邻时，
                                    // 计算得到的mid == r(上取整)
                                    // 这样才能保证每次查找过程的搜索空间在缩小
        if (data[mid] <= target)
            l = mid;
        else  // data[mid] > target
            r = mid - 1;
    }
    return l;  // l和r必定相等，也可以返回r
}

template<typename T>
int BinarySearch::lowerFloor(const std::vector<T> &data, const T &target) {
    int l = lower(data, target);
    return (l + 1 < data.size() && data[l + 1] == target) ? l + 1 : l;
}

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_H
