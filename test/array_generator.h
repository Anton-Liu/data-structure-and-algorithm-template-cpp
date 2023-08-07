//
// Created by Anton Liu on 2023/8/7.
//

#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_GENERATOR_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_GENERATOR_H

#include <vector>
#include <random>

class ArrayGenerator {
public:
    ArrayGenerator() = delete;
    static std::vector<int> generateOrderedIntArray(size_t n);
    static std::vector<int> generateRandomIntArray(size_t n, int lowerBound, int upperBound);  // [lowerBound, upperBound]
    static std::vector<double> generateOrderedFloatArray(size_t n);
    static std::vector<double> generateRandomFloatArray(size_t n, double lowerBound, double upperBound);  // [lowerBound, upperBound]
};

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_GENERATOR_H
