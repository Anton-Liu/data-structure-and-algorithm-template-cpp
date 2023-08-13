#ifndef ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H
#define ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H

#include "stack.h"
#include "../queue/array_queue.h"

/**
 * 思路：入队位置为栈顶
 */

template <typename T>
class QueueStack;

template <typename T>
std::ostream &operator<<(std::ostream &, const QueueStack<T> &);

template <typename T>
class QueueStack : public Stack<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const QueueStack<T> &rhs);
public:
    QueueStack():
        que(ArrayQueue<T>()) { }
    QueueStack(int capacity):
        que(ArrayQueue<T>(capacity)) { }

    QueueStack(const QueueStack<T> &rhs):
        que(rhs.que), curTop(rhs.curTop) { }
    QueueStack<T> &operator=(const QueueStack<T> &rhs);

    bool isEmpty() const override { return que.isEmpty(); }

    int getSize() const override { return que.getSize(); }

    int getCapacity() const override { return que.getCapacity(); }

    T top() const override { return curTop; };  // O(1)

    void push(const T &e) override { que.enqueue(e); curTop = e; }  // O(1)

    void pop() override;  // O(n)
private:
    ArrayQueue<T> que;
    T curTop;  // 记录当前栈顶元素
};

template<typename T>
QueueStack<T> &QueueStack<T>::operator=(const QueueStack<T> &rhs) {
    que = rhs.que;
    curTop = rhs.curTop;
    return *this;
}

template<typename T>
void QueueStack<T>::pop() {
    ArrayQueue<T> que2;
    while (que.getSize() > 1) {
        curTop = que.getFront();
        que.dequeue();
        que2.enqueue(curTop);
    }
    que.dequeue();
    que = que2;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const QueueStack<T> &rhs) {
    int size = rhs.getSize();
    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 栈的信息
    os << "栈的长度：" << size << "，"
       << "栈的容量：" << rhs.getCapacity() << '\n'
       << "栈的内容：" << "stack[";

    ArrayQueue<T> tmp = rhs.que;
    while (tmp.getSize() > 1) {
        os << tmp.getFront() << ", ";
        tmp.dequeue();
    }
    if (!tmp.isEmpty())
        os << tmp.getFront();

    os << "] top\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H
