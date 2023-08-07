//
// Created by Anton Liu on 2023/8/7.
//

#include "array_generator.h"
using std::vector, std::default_random_engine, std::uniform_real_distribution, std::uniform_int_distribution;

vector<int> ArrayGenerator::generateOrderedIntArray(size_t n) {
    vector<int> vec(n);
    for(int i = 0; i < n; i++)
        vec[i] = i;
    return vec;
}

vector<int> ArrayGenerator::generateRandomIntArray(size_t n, int lowerBound, int upperBound) {
    vector<int> vec(n);
    default_random_engine e;
    uniform_int_distribution<int> u(lowerBound, upperBound);
    for (size_t i = 0; i < n; i++)
        vec[i] = u(e);
    return vec;
}


vector<double> ArrayGenerator::generateOrderedFloatArray(size_t n) {
    vector<double> vec(n);
    for(size_t i = 0; i < n; i++)
        vec[i] = static_cast<double>(i);
    return vec;
}

vector<double> ArrayGenerator::generateRandomFloatArray(size_t n, double lowerBound, double upperBound) {
    vector<double> vec(n);
    default_random_engine e;
    uniform_real_distribution<double> u(lowerBound, upperBound);
    for (size_t i = 0; i < n; i++)
        vec[i] = u(e);
    return vec;
}