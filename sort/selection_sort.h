#ifndef ALGORITHM_TEMPLATE_CPP_SELECTION_SORT_H
#define ALGORITHM_TEMPLATE_CPP_SELECTION_SORT_H

#include <vector>

template <typename T>
class SelectionSort {
public:
    SelectionSort() = delete;  // 删除默认构造函数，该类不需要构造对象

    static void sort(std::vector<T> &arr);  // 排序(默认升序)
};

template<typename T>
void SelectionSort<T>::sort(std::vector<T> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        std::swap(arr[i], arr[minIndex]);
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_SELECTION_SORT_H
