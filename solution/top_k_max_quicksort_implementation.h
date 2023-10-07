#ifndef ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_QUICKSORT_IMPLEMENTATION_H
#define ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_QUICKSORT_IMPLEMENTATION_H

#include <vector>
#include <random>

/**
 * TopK问题：
 *     选出N个元素中最大的K(1-base)个元素
 *     快排实现
 * 注：
 *    相比堆实现，使用快排解决时间性能更优
 *    时间复杂度：O(n)
 *    空间复杂度：O(1)
 */

template <typename T>
class TopKMaxQuicksortImplementation {
public:
    TopKMaxQuicksortImplementation() = delete;

    static std::vector<T> getTopK(std::vector<T> &arr, int k);

private:
    static int sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e);
    static int partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};


template<typename T>
std::vector<T> TopKMaxQuicksortImplementation<T>::getTopK(std::vector<T> &arr, int k)
{
    if (arr.size() < k)
        throw std::runtime_error("k取值需小于等于数组长度！");
    if (k <= 0)
        throw std::runtime_error("k必须大于0！");

    k--;  // 1-base
    std::default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建

    auto r = sort(arr, 0, arr.size() - 1, k, e);
    std::vector<T> ret(k + 1);  // 1-base
    for (int i = 0; i <= r; i++)
        ret[i] = arr[i];

    return ret;
}

template<typename T>
int TopKMaxQuicksortImplementation<T>::sort(std::vector<T> &arr, int l, int r, int k, std::default_random_engine &e) {
    auto pivot = partition(arr, l, r, e);
    if (pivot == k)
      return pivot;
    else if (pivot < k)
        return sort(arr, pivot + 1, r, k, e);
    else
        return sort(arr, l, pivot - 1, k, e);
}

template<typename T>
int TopKMaxQuicksortImplementation<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    std::uniform_int_distribution<int> u(l, r);
    auto p = u(e);
    std::swap(arr[p], arr[l]);

    auto i = l + 1, j = r;
    while (true) {
        while (i <= j && arr[i] > arr[l])
            i++;
        while (i <= j && arr[l] > arr[j])
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

#endif //ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_QUICKSORT_IMPLEMENTATION_H
