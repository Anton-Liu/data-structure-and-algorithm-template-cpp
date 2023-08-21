#ifndef ALGORITHM_TEMPLATE_CPP_QUICKSORT_H
#define ALGORITHM_TEMPLATE_CPP_QUICKSORT_H

#include <vector>

/**
 * 最基本的快速排序
 * partition过程：
 *      每次都选第一个元素作为pivot，分割小于和大于等于两个两个区域
 * 存在问题：
 *      每次选第一个元素，划分极端不平均
 *      导致时间复杂度退化为O(n^2)
 *      递归深度O(n)，可能造成栈溢出
 */

template <typename T>
class Quicksort {
public:
    Quicksort() = delete;

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
private:
    static void sort(std::vector<T> &arr, int l, int r);

    /*
     * 最基本的partition，pivot: l
     * 返回partition过程后pivot值所在的最终位置
     * 当前考虑位置: i
     * 中间位置：j，小于arr[l]的最后一个位置
     * 小于arr[l]的区域: arr[l + 1, j]
     * 大于等于arr[l]的区域: arr[j + 1, i - 1]
     */
    static int partition(std::vector<T> &arr, int l, int r);
};

template<typename T>
void Quicksort<T>::sort(std::vector<T> &arr) {
    sort(arr, 0, arr.size() - 1);
}

template<typename T>
void Quicksort<T>::sort(std::vector<T> &arr, int l, int r) {
    if (l >= r)
        return;

    int pivot = partition(arr, l, r);
    sort(arr, l, pivot - 1);
    sort(arr, pivot + 1, r);
}

template<typename T>
int Quicksort<T>::partition(std::vector<T> &arr, int l, int r) {
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

#endif //ALGORITHM_TEMPLATE_CPP_QUICKSORT_H
