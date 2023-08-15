#ifndef ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_STACK_H
#define ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_STACK_H

#include "stack.h"
#include "../linked_list/single_linked_list.h"
#include <iostream>

template <typename T>
class SingleLinkedListStack;

template <typename T>
std::ostream &operator<<(std::ostream &, const SingleLinkedListStack<T> &rhs);

template <typename T>
class SingleLinkedListStack : public Stack<T> {
    friend std::ostream &operator<<<T>(std::ostream &, const SingleLinkedListStack<T> &rhs);
public:
    SingleLinkedListStack():
        list(new SingleLinkedList<T>()) { }

    bool isEmpty() const override { return list -> isEmpty(); }
    int getSize() const override { return list -> getSize(); }

    T top() const override { return list -> getFirst(); }
    void push(const T &e) override { list -> addFirst(e); }
    void pop() override { list -> removeFirst(); }

    ~SingleLinkedListStack() { delete list; }

private:
    SingleLinkedList<T> *list;
};


template <typename T>
std::ostream &operator<<(std::ostream &os, const SingleLinkedListStack<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 栈的信息
    os << "栈的长度：" << size << "，"
       << "栈的容量：∞" << '\n'
       << "栈的内容：" << "stack top[";

    SingleLinkedList<T> tmp = *rhs.list;
    while (tmp.getSize() > 1) {
        os << tmp.getFirst() << ", ";
        tmp.removeFirst();
    }
    if (!tmp.isEmpty())
        os << tmp.getFirst();
    os << "]\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}


#endif //ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_STACK_H
