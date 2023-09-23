#ifndef ALGORITHM_TEMPLATE_CPP_SELECT_KTH_HEAP_IMPLEMENTATION_H
#define ALGORITHM_TEMPLATE_CPP_SELECT_KTH_HEAP_IMPLEMENTATION_H

#include <vector>
#include "../heap/max_heap.h"

/**
 * SelectK问题：
 *     查找数组中第K(1-base)小的元素
 *     通过查找最小的K个元素的TopK问题解决
 *     时间复杂度：O(nlogK)
 *     空间复杂度：O(K)
 */

template <typename T>
class SelectKthHeapImplementation {
public:
    SelectKthHeapImplementation() = delete;

    static T getKthNum(const std::vector<T> &arr, int k);  // 获取第k小的元素
};

template<typename T>
T SelectKthHeapImplementation<T>::getKthNum(const std::vector<T> &arr, int k) {
    if (arr.size() < k)
        throw std::runtime_error("k取值需小于等于数组长度！");
    if (k <= 0)
        throw std::runtime_error("k必须大于0！");

    MaxHeap<T> heap;
    for (int i = 0; i < k; i++)
        heap.add(arr[i]);

    for (int i = k; i < arr.size(); i++)
        if (!heap.isEmpty() && arr[i] < heap.getTop())
            heap.replace(arr[i]);
    return heap.getTop();
}

#endif //ALGORITHM_TEMPLATE_CPP_SELECT_KTH_HEAP_IMPLEMENTATION_H
