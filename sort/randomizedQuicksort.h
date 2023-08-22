#ifndef ALGORITHM_TEMPLATE_CPP_RANDOMIZEDQUICKSORT_H
#define ALGORITHM_TEMPLATE_CPP_RANDOMIZEDQUICKSORT_H

#include <vector>
#include <random>
using std::default_random_engine, std::uniform_real_distribution, std::uniform_int_distribution;

/**
 * 随机化的快速排序
 * partition过程：
 *      每次都随机选一个区间内的元素作为pivot，分割小于和大于等于两个两个区域
 */

template <typename T>
class RandomizedQuicksort {
public:
    RandomizedQuicksort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
private:
    static void sort(std::vector<T> &arr, int l, int r, default_random_engine &e);

    /*
     * 随机化的partition，pivot: [l, r]上的随机位置
     * 返回partition过程后pivot值所在的最终位置
     * 当前考虑位置: i
     * 中间位置：j，小于arr[l]的最后一个位置
     * 小于arr[l]的区域: arr[l + 1, j]
     * 大于等于arr[l]的区域: arr[j + 1, i - 1]
     */
    static int partition(std::vector<T> &arr, int l, int r, default_random_engine &e);
};


template<typename T>
void RandomizedQuicksort<T>::sort(std::vector<T> &arr) {
    default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建
    sort(arr, 0, arr.size() - 1, e);
}

template<typename T>
void RandomizedQuicksort<T>::sort(std::vector<T> &arr, int l, int r, default_random_engine &e) {
    if (l >= r)
        return;

    int pivot = partition(arr, l, r, e);
    sort(arr, l, pivot - 1, e);
    sort(arr, pivot + 1, r, e);
}

template<typename T>
int RandomizedQuicksort<T>::partition(std::vector<T> &arr, int l, int r, default_random_engine &e) {
    uniform_int_distribution<int> u(l, r);
    int p = u(e);
    std::swap(arr[p], arr[l]);

    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[l]) {
            j++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[l], arr[j]);
    return j;
}

#endif //ALGORITHM_TEMPLATE_CPP_RANDOMIZEDQUICKSORT_H
