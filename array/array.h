#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_H

/**
 * 不支持扩容的普通数组，内部使用vector实现
 */

#include <iostream>

template <typename T> class Array;
template <typename T> std::ostream &operator<<(std::ostream &os, const Array<T> &arr);

template <typename T>
class Array {
    friend std::ostream &operator<<<T>(std::ostream &os, const Array<T> &arr);
public:
    Array():
        data(std::vector<T>(10)), size(0) { }  // 默认构造函数，默认容量为10
    Array(int capacity):
        data(std::vector<T>(capacity)), size(0) { }  // 用户指定容量的构造函数

    int getSize() { return size; }  // 获取数组大小
    int getCapacity() { return data.size(); }  // 获取数组容量
    bool isEmpty() { return size == 0; }  // 判断数组是否为空
    bool contains(const T &e);  // 判断数组中是否有元素e
    int getIndex(const T &e);  // 获取元素e的下标，不存在返回-1
    T get(const size_t &idx);  // 返回下标idx的元素
    void set(const size_t &idx, const T &e);  // 修改下标idx处元素的值为e
    void add(const size_t &idx, const T &e);  // 在数组下标idx处插入一个新元素e
    void addFirst(const T &e) { add(0, e); }  // 在数组所有元素前添加一个新元素e
    void addLast(const T &e) { add(size, e); }  // 在数组所有元素后添加一个新元素e
    T remove(const size_t &idx);  //  删除数组idx位置的元素，返回被删除的元素
    T removeFirst() { return remove(0); }  // 删除数组第一个元素并返回
    T removeLast() { return remove(size - 1); }  // 删除数组最后一个元素并返回

    T &operator[](size_t idx) {
        if (idx >= size)
            throw std::runtime_error("访问索引超过当前数组范围！");
        return data[idx];
    }
    const T &operator[](size_t idx) const {
        if (idx >= size)
            throw std::runtime_error("访问索引超过当前数组范围！");
        return data[idx];
    }
private:
    std::vector<T> data;
    int size;  // 数组的长度(也可以理解为指向尾后的位置)
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Array<T> &arr) {
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
bool Array<T>::contains(const T &e) {
    for (const auto &d : data)
        if (d == e)
            return true;
    return false;
}

template<typename T>
int Array<T>::getIndex(const T &e) {
    for (int i = 0; i < size; i++)
        if (data[i] == e)
            return i;
    return -1;
}

template<typename T>
T Array<T>::get(const size_t &idx) {
    if (idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    return data[idx];
}

template<typename T>
void Array<T>::set(const size_t &idx, const T &e) {
    if (idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    data[idx] = e;
}

template<typename T>
void Array<T>::add(const size_t &idx, const T &e) {
    if (idx >= data.size())
        throw std::runtime_error("访问索引超过当前数组容量！");
    if (idx > size)
        throw std::runtime_error("访问索引超过当前数组可插入范围！");
    for (int i = size; i > idx; i--)
        data[i] = data[i - 1];
    data[idx] = e;
    size++;
}

template<typename T>
T Array<T>::remove(const size_t &idx) {
    if (idx >= size)
        throw std::runtime_error("访问索引超过当前数组范围！");
    T ret = data[idx];
    for (int i = idx; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return ret;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_H
