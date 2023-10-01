#ifndef ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H
#define ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H

#include <vector>
#include <string>
#include "../sort/insertion_sort.h"
#include "../sort/selection_sort.h"
#include "../sort/merge_sort.h"
#include "../sort/merge_sort_with_insertion_sort_optimization.h"
#include "../sort/quicksort.h"
#include "../sort/quicksort_with_insertion_sort_optimization.h"
#include "../sort/randomized_quicksort.h"
#include "../sort/two_way_randomized_quicksort.h"
#include "../sort/three_way_randomized_quicksort.h"
#include "../sort/heapsort.h"
#include "../sort/bubble_sort.h"
#include "../sort/shellsort.h"
#include <stdexcept>
#include <iostream>

class SortingHelper {
public:
    SortingHelper() = delete;

    template <typename T> static bool isSorted(const std::vector<T> &arr);  // 默认升序
    template <typename T> static void sortTest(const std::string &sortName, std::vector<T> &arr);  // 测试一个排序算法
};

template<typename T>
bool SortingHelper::isSorted(const std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1])
            return false;
    return true;
}

template<typename T>
void SortingHelper::sortTest(const std::string &sortName, std::vector<T> &arr) {
    clock_t startTime = clock();
    if (sortName == "InsertionSort")
        InsertionSort<T>::sort(arr);
    else if (sortName == "SelectionSort")
        SelectionSort<T>::sort(arr);
    else if (sortName == "MergeSort")
        MergeSort<T>::sort(arr);
    else if (sortName == "MergeSortWithInsertionSortOptimization")
        MergeSortWithInsertionSortOptimization<T>::sort(arr);
    else if (sortName == "Quicksort")
        Quicksort<T>::sort(arr);
    else if (sortName == "QuicksortWithInsertionSortOptimization")
        QuicksortWithInsertionSortOptimization<T>::sort(arr);
    else if (sortName == "RandomizedQuicksort")
        RandomizedQuicksort<T>::sort(arr);
    else if (sortName == "TwoWayRandomizedQuicksort")
        TwoWayRandomizedQuicksort<T>::sort(arr);
    else if (sortName == "ThreeWayRandomizedQuicksort")
        ThreeWayRandomizedQuicksort<T>::sort(arr);
    else if (sortName == "Heapsort")
        Heapsort<T>::sort(arr);
    else if (sortName == "BubbleSort")
        BubbleSort<T>::sort(arr);
    else if (sortName == "BubbleSort1")
        BubbleSort<T>::sort1(arr);
    else if (sortName == "BubbleSort2")
        BubbleSort<T>::sort2(arr);
    else if (sortName == "Shellsort")
        Shellsort<T>::sort(arr);
    else
        throw std::runtime_error("排序名称不存在，检查排序名称是否正确！");
    clock_t endTime = clock();
    if (!isSorted(arr))
        throw std::runtime_error("排序算法不正确！");
    std::cout << sortName << ": "
              << arr.size() << "(size), "
              << static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
}

#endif //ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H
