#ifndef ALGORITHM_TEMPLATE_CPP_TWO_WAY_RANDOMIZED_QUICKSORT_H
#define ALGORITHM_TEMPLATE_CPP_TWO_WAY_RANDOMIZED_QUICKSORT_H

#include <vector>
#include <random>

/**
 * 随机化的双路快速排序
 * partition过程：
 *      每次都随机选一个区间内的元素作为pivot，分割小于等于和大于等于两个区域
 */

template <typename T>
class TwoWayRandomizedQuicksort {
public:
    TwoWayRandomizedQuicksort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
private:
    static void sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e);

    /*
     * 随机化的partition，pivot: [l, r]上的随机位置
     * 返回partition过程后pivot值所在的最终位置
     * 将等于arr[l]的部分分给小于等于和大于等于两个区域
     * 当前考虑位置: i(小于等于区域)、j(大于等于区域)
     * 小于等于arr[l]的区域: arr[l + 1, i - 1]
     * 大于等于arr[l]的区域: arr[j + 1, r]
     */
    static int partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};

template<typename T>
void TwoWayRandomizedQuicksort<T>::sort(std::vector<T> &arr) {
    std::default_random_engine e;  // 每次排序使用同一个随机数引擎对象，避免每次partition都创建
    sort(arr, 0, arr.size() - 1, e);
}

template<typename T>
void TwoWayRandomizedQuicksort<T>::sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    if (l >= r)
        return;

    int pivot = partition(arr, l, r, e);
    sort(arr, l, pivot - 1, e);
    sort(arr, pivot + 1, r, e);
}

template<typename T>
int TwoWayRandomizedQuicksort<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
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

#endif //ALGORITHM_TEMPLATE_CPP_TWO_WAY_RANDOMIZED_QUICKSORT_H
