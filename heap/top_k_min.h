#ifndef ALGORITHM_TEMPLATE_CPP_TOP_K_MIN_H
#define ALGORITHM_TEMPLATE_CPP_TOP_K_MIN_H

#include "max_heap.h"
#include <vector>

/**
 * TopK问题：
 *     选出N个元素中最小的K个元素
 *     维护一个大根堆
 */
template <typename T>
class TopKMin {
public:
    TopKMin() = delete;
    static std::vector<T> getTopK(const std::vector<T> &arr, int k);
};

template<typename T>
std::vector<T> TopKMin<T>::getTopK(const std::vector<T> &arr, int k)
{
    if (arr.size() < k)
        throw std::runtime_error("k取值需小于数组长度！");

    MaxHeap<T> heap;
    for (int i = 0; i < k; i++)
        heap.add(arr[i]);

    for (int i = k; i < arr.size(); i++)
        if (!heap.isEmpty() && arr[i] < heap.getTop())
            heap.replace(arr[i]);

    std::vector<T> ret(k);
    for (int i = 0; i < k; i++)
        ret[i] = heap.extractTop();

    return ret;
}

#endif //ALGORITHM_TEMPLATE_CPP_TOP_K_MIN_H
