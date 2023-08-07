//
// Created by Anton Liu on 2023/8/7.
//

#ifndef ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H
#define ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H

#include <vector>

class SortingHelper {
public:
    SortingHelper() = delete;

    template <typename T> static bool isSorted(std::vector<T> arr);  // 默认升序
};

template<typename T>
bool SortingHelper::isSorted(std::vector<T> arr) {
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1])
            return false;
    return true;
}

#endif //ALGORITHM_TEMPLATE_CPP_SORTING_HELPER_H
