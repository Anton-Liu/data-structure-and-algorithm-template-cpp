#ifndef ALGORITHM_TEMPLATE_CPP_STACK_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_STACK_QUEUE_H

#include "queue.h"
#include "../stack/array_stack.h"

template <typename T>
class StackQueue;

template <typename T>
std::ostream &operator<<(std::ostream &, const StackQueue<T> &);

template <typename T>
class StackQueue : public Queue<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const StackQueue<T> &arrayQueue);
public:
    StackQueue():
            stack{} { }
    StackQueue(int capacity):
            stack{capacity} { }

    StackQueue(const StackQueue<T> &rhs):
            stack(rhs.stack) { };
    StackQueue<T> &operator=(const StackQueue<T> &rhs);

    bool isEmpty() const { return stack.isEmpty(); }
    int getSize() const { return stack.getSize(); }
    int getCapacity() const { return stack.getCapacity(); }
    T getFront() const { return stack.top(); };

    void enqueue(const T &e);
    void dequeue();

private:
    ArrayStack<T> stack;
};

template<typename T>
StackQueue<T> &StackQueue<T>::operator=(const StackQueue<T> &rhs) {
    stack = rhs.stack;
    return *this;
}

template<typename T>
void StackQueue<T>::enqueue(const T &e) {
    ArrayStack<T> stack2;
    while (!stack.isEmpty()) {
        stack2.push(stack.top());
        stack.pop();
    }
    stack.push(e);
    while (!stack2.isEmpty()) {
        stack.push(stack2.top());
        stack2.pop();
    }
}

template<typename T>
void StackQueue<T>::dequeue() {
    stack.pop();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const StackQueue<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 队列信息
    os << "队列的长度：" << size << "，"
       << "队列的容量：" << rhs.getCapacity() << '\n'
       << "队列的内容：" << "queue front[";

    ArrayStack<T> tmp(rhs.stack);
    while (tmp.getSize() > 1) {
        os << tmp.top() << ", ";
        tmp.pop();
    }
    if (!tmp.isEmpty())
        os << tmp.top();
    os << "]tail\n";
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}


#endif //ALGORITHM_TEMPLATE_CPP_STACK_QUEUE_H
