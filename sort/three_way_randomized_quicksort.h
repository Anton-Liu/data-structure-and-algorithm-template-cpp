#ifndef ALGORITHM_TEMPLATE_CPP_THREE_WAY_RANDOMIZED_QUICKSORT_H
#define ALGORITHM_TEMPLATE_CPP_THREE_WAY_RANDOMIZED_QUICKSORT_H

#include <vector>
#include <random>
#include <utility>

/**
 * 随机化的三路快速排序
 * partition过程：
 *      每次都随机选一个区间内的元素作为pivot，分割小于、等于和大于等于三个区域
 * 优势：
 *      对于元素相同的数组，时间复杂度为O(n)
 */

template <typename T>
class ThreeWayRandomizedQuicksort {
public:
    ThreeWayRandomizedQuicksort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
private:
    static void sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e);

    /*
     * 随机化的partition，pivot: [l, r]上的随机位置
     * 通过两个边界lt、gt，将数组划分为小于、等于和大于三个区域
     * lt：less than，指向小于arr[l]的最右侧的位置
     * gt：greater than，指向大于arr[l]的最左侧的位置
     * i：指向当前考虑位置
     * 小于arr[l]的区域: arr[l + 1, lt]
     * 等于arr[l]的区域: arr[lt + 1, i - 1]
     * 大于arr[l]的区域: arr[gt, r]
     * 返回小于arr[l]的最右侧的位置和大于arr[l]的最左侧的位置
     */
    static std::pair<int, int> partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e);
};

template<typename T>
void ThreeWayRandomizedQuicksort<T>::sort(std::vector<T> &arr) {
    std::default_random_engine e;
    sort(arr, 0, arr.size() - 1, e);
}

template<typename T>
void ThreeWayRandomizedQuicksort<T>::sort(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    if (l >= r)
        return;

    auto border = partition(arr, l, r, e);
    sort(arr, l, border.first, e);
    sort(arr, border.second, r, e);
}

template<typename T>
std::pair<int, int>
ThreeWayRandomizedQuicksort<T>::partition(std::vector<T> &arr, int l, int r, std::default_random_engine &e) {
    std::uniform_int_distribution<int> u(l, r);
    int p = u(e);
    std::swap(arr[p], arr[l]);

    int lt = l, i = l + 1, gt = r + 1;
    while (i < gt) {
        if (arr[i] < arr[l]) {
            lt++;
            std::swap(arr[i], arr[lt]);
            i++;
        }
        else if (arr[i] == arr[l])
            i++;
        else {  // arr[i] > arr[l]
            gt--;
            std::swap(arr[i], arr[gt]);
        }
    }
    std::swap(arr[l], arr[lt]);
    return {lt - 1, gt};
}

#endif //ALGORITHM_TEMPLATE_CPP_THREE_WAY_RANDOMIZED_QUICKSORT_H
