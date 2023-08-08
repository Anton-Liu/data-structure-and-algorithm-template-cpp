#ifndef ALGORITHM_TEMPLATE_CPP_LINEAR_SEARCH_H
#define ALGORITHM_TEMPLATE_CPP_LINEAR_SEARCH_H

#include <vector>

class LinearSearch {
public:
    LinearSearch() = delete;

    template <typename T>
    static int search(const std::vector<T> &data, const T &target);  // 线性查找值为target的元素对应下标，不存在返回-1
};

#include <iostream>
template<typename T>
int LinearSearch::search(const std::vector<T> &data, const T &target) {
    std::cout << data.size() << std::endl;
    for (int i = 0; i < data.size(); i++) {
        if (target == data[i])
            return i;
    }
    return -1;
}


#endif //ALGORITHM_TEMPLATE_CPP_LINEAR_SEARCH_H
