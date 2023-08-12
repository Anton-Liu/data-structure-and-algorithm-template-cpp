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
            arr(new LasyDynamicArray<T>()) { }
    ArrayStack(int capacity):
            arr(new LasyDynamicArray<T>(capacity)) { }

    bool isEmpty() const override { return arr -> isEmpty(); }
    int getSize() const override { return arr -> getSize(); }
    int getCapacity() const override { return arr -> getCapacity(); }
    T top() const override { return arr -> getLast(); }

    void push(const T &e) override { arr -> addLast(e); };
    void pop() override { arr -> removeLast(); }
private:
    std::unique_ptr<LasyDynamicArray<T>> arr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayStack<T> &arrayStack) {
    int size = arrayStack.arr -> getSize();
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
        os << (*arrayStack.arr)[i];
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
