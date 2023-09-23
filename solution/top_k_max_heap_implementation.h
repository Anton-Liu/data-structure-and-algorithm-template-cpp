#ifndef ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_HEAP_IMPLEMENTATION_H
#define ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_HEAP_IMPLEMENTATION_H

#include "../heap/min_heap.h"
#include <vector>

/**
 * TopK问题：
 *     选出n个元素中最大的K个元素
 *     维护一个小根堆
 * 注：
 *    使用快排解决性能更优，但必须读入所有数据才能求解；
 *    堆实现的优势在于不需要一次性知道所有数据就能求解，
 *    非常适合处理数据流、极大规模的数据
 *    时间复杂度：O(nlogK)
 *    空间复杂度：O(K)
 */
template <typename T>
class TopKMaxHeapImplementation {
public:
    TopKMaxHeapImplementation() = delete;
    static std::vector<T> getTopK(const std::vector<T> &arr, int k);
};

template<typename T>
std::vector<T> TopKMaxHeapImplementation<T>::getTopK(const std::vector<T> &arr, int k)
{
    if (arr.size() < k)
        throw std::runtime_error("k取值需小于数组长度！");

    MinHeap<T> heap;
    for (int i = 0; i < k; i++)
        heap.add(arr[i]);

    for (int i = k; i < arr.size(); i++)
        if (!heap.isEmpty() && arr[i] > heap.getTop())
            heap.replace(arr[i]);

    std::vector<T> ret(k);
    for (int i = 0; i < k; i++)
        ret[i] = heap.extractTop();

    return ret;
}

#endif //ALGORITHM_TEMPLATE_CPP_TOP_K_MAX_HEAP_IMPLEMENTATION_H
