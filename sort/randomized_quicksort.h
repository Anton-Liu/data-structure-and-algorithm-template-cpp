#ifndef ALGORITHM_TEMPLATE_CPP_RANDOMIZED_QUICKSORT_H
#define ALGORITHM_TEMPLATE_CPP_RANDOMIZED_QUICKSORT_H

#include <vector>
#include <random>

/**
 * 随机化的快速排序
 * partition过程：
 *      每次都随机选一个区间内的元素作为pivot，分割小于和大于等于两个两个区域
 * 存在问题：
 *      对于元素全都相同的数组，划分极端不平均
 *      导致时间复杂度退化为O(n^2)
 *      递归深度O(n)，可能造成栈溢出
 */

template <typename T>
class RandomizedQuicksort {
public:
    RandomizedQuicksort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)

private:
    static void sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e);

    /*
     * 随机化的partition，pivot: [l, r]上的随机位置
     * 返回partition过程后pivot值所在的最终位置
     * 当前考虑位置: i
     * 中间位置：j，小于arr[l]的最后一个位置
     * 小于arr[l]的区域: arr[l + 1, j]
     * 大于等于arr[l]的区域: arr[j + 1, i - 1]
     */
    static int partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};


template<typename T>
void RandomizedQuicksort<T>::sort(std::vector<T> &arr) {
    std::default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建
    sort(arr, 0, arr.size() - 1, e);
}

template<typename T>
void RandomizedQuicksort<T>::sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    if (l >= r)
        return;

    auto pivot = partition(arr, l, r, e);
    sort(arr, l, pivot - 1, e);
    sort(arr, pivot + 1, r, e);
}

template<typename T>
int RandomizedQuicksort<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    std::uniform_int_distribution<int> u(l, r);
    auto p = u(e);
    std::swap(arr[p], arr[l]);

    auto j = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[l]) {
            j++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[l], arr[j]);
    return j;
}

#endif //ALGORITHM_TEMPLATE_CPP_RANDOMIZED_QUICKSORT_H
