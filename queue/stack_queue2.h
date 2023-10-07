#ifndef ALGORITHM_TEMPLATE_CPP_STACK_QUEUE2_H
#define ALGORITHM_TEMPLATE_CPP_STACK_QUEUE2_H

#include "queue.h"
#include "../stack/array_stack.h"

template <typename T>
class StackQueue2;

template <typename T>
std::ostream &operator<<(std::ostream &, const StackQueue2<T> &);

template <typename T>
class StackQueue2 {
    friend std::ostream &operator<<<T>(std::ostream &os, const StackQueue2<T> &arrayQueue);
public:
    StackQueue2():
            stackIn{}, stackOut{} { }
    explicit StackQueue2(int capacity):
            stackIn{capacity}, stackOut{capacity} { }
    StackQueue2(const StackQueue2<T> &rhs):
            stackIn(rhs.stackIn), stackOut(rhs.stackOut) { };
    StackQueue2<T> &operator=(const StackQueue2<T> &rhs);

    bool isEmpty() const { return stackIn.isEmpty() && stackOut.isEmpty(); }
    int getSize() const { return stackIn.getSize() + stackOut.getSize(); }
    int getCapacity() const { return stackIn.getCapacity() + stackOut.getCapacity(); }

    T getFront();  // getFront操作需要改变数据成员，因此是非const
    void enqueue(const T &e);
    void dequeue();

private:
    ArrayStack<T> stackIn;
    ArrayStack<T> stackOut;
    T front;  // 记录StackOut为空时的队首元素
};

template<typename T>
StackQueue2<T> &StackQueue2<T>::operator=(const StackQueue2<T> &rhs) {
    stackIn = rhs.stackIn;
    stackOut = rhs.stackOut;

    return *this;
}

template<typename T>
T StackQueue2<T>::getFront() {
    if (!stackOut.isEmpty())
        return stackOut.top();

    return front;
}

template<typename T>
void StackQueue2<T>::enqueue(const T &e) {
    if (stackIn.isEmpty())
        front = e;
    stackIn.push(e);
}

template<typename T>
void StackQueue2<T>::dequeue() {
    if (!stackOut.isEmpty()) {
        stackOut.pop();
        return;
    }
    while (stackIn.getSize() > 1) {
        stackOut.push(stackIn.top());
        stackIn.pop();
    }
    stackIn.pop();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const StackQueue2<T> &que) {
    auto size = que.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 队列信息
    os << "队列的长度：" << size << "，"
       << "队列的容量：" << que.getCapacity() << '\n'
       << "队列的内容：" << "queue front[";
    ArrayStack<T> tmpIn, tmpOut;
    tmpIn = que.stackIn;
    tmpOut = que.stackOut;
    while (!tmpOut.isEmpty()) {
        os << tmpOut.top() << ", ";
        tmpOut.pop();
    }
    while (!tmpIn.isEmpty()) {
        tmpOut.push(tmpIn.top());
        tmpIn.pop();
    }
    while (!tmpOut.isEmpty()) {
        os << tmpOut.top()  << ", ";
        tmpOut.pop();
    }
    os << "]tail\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_STACK_QUEUE2_H
