#ifndef ALGORITHM_TEMPLATE_CPP_DYNAMIC_ARRAY_H
#define ALGORITHM_TEMPLATE_CPP_DYNAMIC_ARRAY_H

/**
 * 支持扩容的动态数组，内部使用vector实现
 * 扩容策略：元素满则扩容两倍
 */

#include <iostream>
#include "static_array.h"

template <typename T> class DynamicArray;
template <typename T> std::ostream &operator<<(std::ostream &os, const DynamicArray<T> &arr);

template <typename T>
class DynamicArray : public Array<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const DynamicArray<T> &arr);
public:
    DynamicArray():
            data(std::vector<T>(10)), size(0) { }  // 默认构造函数，默认容量为10
    explicit DynamicArray(int capacity):
            data(std::vector<T>(capacity)), size(0) { }  // 用户指定容量的构造函数

    DynamicArray(const DynamicArray<T> &rhs):
            data(rhs.data), size(rhs.size) { }
    DynamicArray<T> &operator=(const DynamicArray<T> &rhs);

    int getSize() const override { return size; }  // 获取数组大小
    int getCapacity() const override { return data.size(); }  // 获取数组容量
    bool isEmpty() const override { return size == 0; }  // 判断数组是否为空
    bool contains(const T &e) const override;  // 判断数组中是否有元素e
    int getIndex(const T &e) const override;  // 获取元素e的下标，不存在返回-1
    T get(const int &idx) const override;  // 返回下标idx的元素
    T getFirst() const override { return get(0); }  // 获取第一个位置的元素
    T getLast() const override { return get(size - 1); };  // 获取最后一个位置的元素

    void set(const int &idx, const T &e) override;  // 修改下标idx处元素的值为e
    void add(const int &idx, const T &e) override;  // 在数组下标idx处插入一个新元素e
    void addFirst(const T &e) override { add(0, e); }  // 在数组所有元素前添加一个新元素e
    void addLast(const T &e) override { add(size, e); }  // 在数组所有元素后添加一个新元素e
    T remove(const int &idx) override;  //  删除数组idx位置的元素，返回被删除的元素
    T removeFirst() override { return remove(0); }  // 删除数组第一个元素并返回
    T removeLast() override { return remove(size - 1); }  // 删除数组最后一个元素并返回

    ~DynamicArray() = default;

    T &operator[](int idx) override {
        if (idx >= size)
            throw std::runtime_error("访问索引超过当前数组范围！");
        return data[idx];
    }
    const T &operator[](int idx) const override {
        if (idx >= size)
            throw std::runtime_error("访问索引超过当前数组范围！");
        return data[idx];
    }

protected:
    std::vector<T> data;
    int size;  // 数组的长度(也可以理解为指向尾后的位置)
};

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &rhs) {
    data = rhs.data;
    size = rhs.size;
    return *this;
}

template<typename T>
bool DynamicArray<T>::contains(const T &e) const {
    for (const auto &d : data)
        if (d == e)
            return true;
    return false;
}

template<typename T>
int DynamicArray<T>::getIndex(const T &e) const {
    for (int i = 0; i < size; i++)
        if (data[i] == e)
            return i;
    return -1;
}

template<typename T>
T DynamicArray<T>::get(const int &idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    return data[idx];
}

template<typename T>
void DynamicArray<T>::set(const int &idx, const T &e) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    data[idx] = e;
}

template<typename T>
void DynamicArray<T>::add(const int &idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("访问索引超过当前数组可插入范围！");
    if (size == data.size())
        data.resize(2 * data.size());  // 元素满，则扩容两倍

    for (int i = size; i > idx; i--)
        data[i] = data[i - 1];
    data[idx] = e;
    size++;
}

template<typename T>
T DynamicArray<T>::remove(const int &idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");

    T ret = data[idx];
    for (int i = idx; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return ret;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DynamicArray<T> &arr) {
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


#endif //ALGORITHM_TEMPLATE_CPP_DYNAMIC_ARRAY_H
