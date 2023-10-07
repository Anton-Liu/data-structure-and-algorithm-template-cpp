#ifndef ALGORITHM_TEMPLATE_CPP_SELECT_K_H
#define ALGORITHM_TEMPLATE_CPP_SELECT_K_H

#include <vector>
#include <random>

/**
 * 查找数组中第k小的元素
 * 二分查找法非递归实现
 */

template <typename T>
class SelectK {
public:
    SelectK() = delete;

    static T getKthNum(std::vector<T> &arr, int k);  // 获取第k小的元素

private:
    static T sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e);
    static int partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};

template<typename T>
T SelectK<T>::getKthNum(std::vector<T> &arr, int k) {
    std::default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建

    return sort(arr, 0, arr.size() - 1, k, e);
}


template<typename T>
T SelectK<T>::sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e) {
    while (l <= r) {
        int pivot = partition(arr, l, r, e);

        if (pivot == k)
            return arr[pivot];
        if (pivot < k)
            l = pivot + 1;
        else
            r = pivot - 1;
    }

    throw std::runtime_error("无解！");
}

template<typename T>
int SelectK<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    std::uniform_int_distribution<int> u(l, r);
    auto p = u(e);
    std::swap(arr[p], arr[l]);

    auto i = l + 1, j = r;
    while (true) {
        while (i <= j && arr[i] < arr[l])
            i++;
        while (i <= j && arr[l] < arr[j])
            j--;

        if (i >= j)
            break;

        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }

    std::swap(arr[l], arr[j]);
    return j;
}

#endif //ALGORITHM_TEMPLATE_CPP_SELECT_K_H
