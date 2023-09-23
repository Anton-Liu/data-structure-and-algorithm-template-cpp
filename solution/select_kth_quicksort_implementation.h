#ifndef ALGORITHM_TEMPLATE_CPP_SELECT_KTH_QUICKSORT_IMPLEMENTATION_H
#define ALGORITHM_TEMPLATE_CPP_SELECT_KTH_QUICKSORT_IMPLEMENTATION_H

#include <vector>
#include <random>

/**
 * SelectK问题：
 *     查找数组中第K小的元素
 *     利用快排每次确定一个元素正确位置的性质
 */

template <typename T>
class SelectKthQuicksortImplementation {
public:
    SelectKthQuicksortImplementation() = delete;

    static T getKthNum(std::vector<T> &arr, int k);  // 获取第k小的元素
private:
    static T sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e);

    static int partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};

template<typename T>
T SelectKthQuicksortImplementation<T>::getKthNum(std::vector<T> &arr, int k) {
    std::default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建
    return sort(arr, 0, arr.size() - 1, k, e);
}

template<typename T>
T SelectKthQuicksortImplementation<T>::sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e) {
    int pivot = partition(arr, l, r, e);
    if (pivot == k)
        return arr[k];
    else if (pivot < k)
        return sort(arr, pivot + 1, r, k, e);
    else
        return sort(arr, l, pivot - 1, k, e);
}

template<typename T>
int SelectKthQuicksortImplementation<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    std::uniform_int_distribution<int> u(l, r);
    int p = u(e);
    std::swap(arr[p], arr[l]);

    int i = l + 1, j = r;
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

#endif //ALGORITHM_TEMPLATE_CPP_SELECT_KTH_QUICKSORT_IMPLEMENTATION_H
