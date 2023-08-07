#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_HELPER_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_HELPER_H

#include <vector>
#include <iostream>

class ArrayHelper {
public:
    ArrayHelper() = delete;

    // 生成数组
    static std::vector<int> generateOrderedIntArray(size_t n);
    static std::vector<int> generateRandomIntArray(size_t n, int lowerBound, int upperBound);  // [lowerBound, upperBound]
    static std::vector<double> generateOrderedFloatArray(size_t n);
    static std::vector<double> generateRandomFloatArray(size_t n, double lowerBound, double upperBound);  // [lowerBound, upperBound]

    // 打印数组
    template <typename T> static void printArray(const std::vector<T> &arr);
};

template<typename T>
void ArrayHelper::printArray(const std::vector<T> &arr) {
    if (arr.size() == 0)
        return;
    std::cout << "(1行10个元素)\n " << arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (i % 10 == 0) std::cout << std::endl;
        std::cout << ' ' << arr[i];
    }
    std::cout << std::endl;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_HELPER_H
