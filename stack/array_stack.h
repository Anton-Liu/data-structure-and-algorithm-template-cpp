#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_STACK_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_STACK_H

#include "../array/lazy_dynamic_array.h"
#include "stack.h"
#include <memory>
#include <iostream>

template <typename T>
class ArrayStack;

template <typename T>
std::ostream &operator<<(std::ostream &, const ArrayStack<T> &);

template <typename T>
class ArrayStack : public Stack<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const ArrayStack<T> &arrayStack);
public:
    ArrayStack():
            data(LazyDynamicArray<T>()) { }
    explicit ArrayStack(int capacity):
            data(LazyDynamicArray<T>(capacity)) { }

    ArrayStack(const ArrayStack<T> &rhs):
            data(rhs.data) { }
    ArrayStack<T> &operator=(const ArrayStack<T> &rhs);

    bool isEmpty() const override { return data.isEmpty(); }
    int getSize() const override { return data.getSize(); }
    int getCapacity() const override { return data.getCapacity(); }
    T top() const override { return data.getLast(); }

    void push(const T &e) override { data.addLast(e); };
    void pop() override { data.removeLast(); }
private:
    LazyDynamicArray<T> data;
};

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack<T> &rhs) {
    data = rhs.data;
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayStack<T> &arrayStack) {
    int size = arrayStack.data.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 栈的信息
    os << "栈的长度：" << size << "，"
       << "栈的容量：" << arrayStack.getCapacity() << '\n'
       << "栈的内容：" << "stack[";
    for (int i = 0; i < size; i++) {
        os << (arrayStack.data)[i];
        if (i != size - 1)
            os << ", ";
    }
    os << "] top\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_STACK_H
