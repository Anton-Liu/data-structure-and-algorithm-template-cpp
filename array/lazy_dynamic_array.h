#ifndef ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H
#define ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H

/**
 * 支持扩容&缩容的动态数组，内部使用vector实现
 * 扩容策略：元素满则扩容两倍
 * 缩容策略：lazy
 */

#include <iostream>
#include "array.h"

template <typename T> class LasyDynamicArray;
template <typename T> std::ostream &operator<<(std::ostream &os, const LasyDynamicArray<T> &arr);

template <typename T>
class LasyDynamicArray : public Array<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LasyDynamicArray<T> &arr);
public:
    LasyDynamicArray():
            Array<T>() { }  // 默认构造函数，默认容量为10
    LasyDynamicArray(int capacity):
            Array<T>(capacity) { }  // 用户指定容量的构造函数
            
    void add(const int &idx, const T &e) override;  // 在数组下标idx处插入一个新元素e
    T remove(const int &idx) override;  //  删除数组idx位置的元素，返回被删除的元素
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const LasyDynamicArray<T> &arr) {
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

template<typename T>
void LasyDynamicArray<T>::add(const int &idx, const T &e) {
    if (idx > Array<T>::size)
        throw std::runtime_error("访问索引超过当前数组可插入范围！");
    if (idx >= Array<T>::data.size())
        Array<T>::data.resize(2 * Array<T>::data.size());  // 元素满，则扩容两倍
    for (int i = Array<T>::size; i > idx; i--)
        Array<T>::data[i] = Array<T>::data[i - 1];
    Array<T>::data[idx] = e;
    Array<T>::size++;
}

template<typename T>
T LasyDynamicArray<T>::remove(const int &idx) {
    if (idx >= Array<T>::size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    T ret = Array<T>::data[idx];
    for (int i = idx; i < Array<T>::size - 1; i++)
        Array<T>::data[i] = Array<T>::data[i + 1];
    Array<T>::size--;

    if (Array<T>::size == Array<T>::data.size() / 4 && Array<T>::data.size() / 2 != 0)  // 缩容(lazy)，注意数组不能缩容0
        Array<T>::data.resize(Array<T>::data.size() / 2);
    return ret;
}

#endif //ALGORITHM_TEMPLATE_CPP_LAZY_DYNAMIC_ARRAY_H
