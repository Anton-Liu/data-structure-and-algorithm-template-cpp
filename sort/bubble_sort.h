#ifndef ALGORITHM_TEMPLATE_CPP_BUBBLE_SORT_H
#define ALGORITHM_TEMPLATE_CPP_BUBBLE_SORT_H

#include <vector>

template <typename T>
class BubbleSort {
public:
    BubbleSort() = delete;
    static void sort(std::vector<T> &arr);  // 优化版本2
    static void sort1(std::vector<T> &arr);  // 最简单的冒泡排序
    static void sort2(std::vector<T> &arr);  // 优化版本1
};

template<typename T>
void BubbleSort<T>::sort(std::vector<T> &arr) {
    for (int i = 0; i < arr.size() - 1;) {
        int lastSwappedIndex = 0;
        for (int j = 0; j < arr.size() - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                lastSwappedIndex = j + 1;
            }
        if (lastSwappedIndex == 0)
            break;
        i = arr.size() - lastSwappedIndex;
    }
}

template<typename T>
void BubbleSort<T>::sort1(std::vector<T> &arr) {
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = 0; j < arr.size() - i - 1; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

template<typename T>
void BubbleSort<T>::sort2(std::vector<T> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        bool isSwapped = false;
        for (int j = 0; j < arr.size() - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        if (!isSwapped)
            break;
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_BUBBLE_SORT_H
