#ifndef ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H
#define ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H

/**
 * 支持扩容&缩容的动态数组，内部使用vector实现
 * 扩容策略：元素满则扩容两倍
 * 缩容策略：lazy
 */

#include <iostream>
#include "dynamic_array.h"

template <typename T> class LazyDynamicArray;
template <typename T> std::ostream &operator<<(std::ostream &os, const LazyDynamicArray<T> &arr);

template <typename T>
class LazyDynamicArray : public DynamicArray<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LazyDynamicArray<T> &arr);
public:
    LazyDynamicArray():
            DynamicArray<T>() { }  // 默认构造函数，默认容量为10
    LazyDynamicArray(int capacity):
            DynamicArray<T>(capacity) { }  // 用户指定容量的构造函数

    LazyDynamicArray(const LazyDynamicArray<T> &rhs):
            DynamicArray<T>(rhs) { }
    LazyDynamicArray<T> &operator=(const LazyDynamicArray<T> &rhs);

    T remove(const int &idx) override;  //  删除数组idx位置的元素，返回被删除的元素(支持lazy缩容)

    ~LazyDynamicArray() = default;
};

template<typename T>
LazyDynamicArray<T> &LazyDynamicArray<T>::operator=(const LazyDynamicArray<T> &rhs) {
    DynamicArray<T>::operator=(rhs);
    return *this;
}

template<typename T>
T LazyDynamicArray<T>::remove(const int &idx) {
    if (idx < 0 || idx >= DynamicArray<T>::size)
        throw std::runtime_error("访问索引超过当前数组范围！");

    T ret = DynamicArray<T>::data[idx];
    for (int i = idx; i < DynamicArray<T>::size - 1; i++)
        DynamicArray<T>::data[i] = DynamicArray<T>::data[i + 1];
    DynamicArray<T>::size--;

    if (DynamicArray<T>::size == DynamicArray<T>::data.size() / 4 && DynamicArray<T>::data.size() / 2 != 0)  // 缩容(lazy)，注意数组不能缩容0
        DynamicArray<T>::data.resize(DynamicArray<T>::data.size() / 2);
    return ret;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LazyDynamicArray<T> &arr) {
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < arr.size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << "数组长度：" << arr.size << "，"
       << "数组容量：" << arr.data.size() << '\n'
       << "数组内容：" << "array[";
    if (arr.size == 0) {
        os << "]\n";
        return os;
    }
    os << (arr.data)[0];
    for (int i = 1; i < arr.size; i++)
        os << ", " << (arr.data)[i];
    os << "]\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < arr.size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H
