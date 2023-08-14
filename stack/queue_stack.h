//
// Created by Anton Liu on 2023/8/13.
//

#ifndef ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H
#define ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H

/**
 * 思路：出队位置为栈顶
 */

#include "stack.h"
#include "../queue/array_queue.h"
#include "array_stack.h"

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
    explicit QueueStack(int capacity):
            que(ArrayQueue<T>(capacity)) { }

    QueueStack(const QueueStack<T> &rhs):
            que(rhs.que) { }
    QueueStack<T> &operator=(const QueueStack<T> &rhs);

    bool isEmpty() const override { return que.isEmpty(); }

    int getSize() const override { return que.getSize(); }

    int getCapacity() const override { return que.getCapacity(); }

    T top() const override { return que.getFront(); };  // O(1)

    void push(const T &e) override;  // O(n)

    void pop() override { que.dequeue(); };  // O(1)
private:
    ArrayQueue<T> que;
};

template<typename T>
void QueueStack<T>::push(const T &e) {
    // 辅助队列写法
//    ArrayQueue<T> que2;
//    while (!que.isEmpty()) {
//        que2.enqueue(que.getFront());
//        que.dequeue();
//    }
//    que.enqueue(e);
//    while (!que2.isEmpty()) {
//        que.enqueue(que2.getFront());
//        que2.dequeue();
//    }

    // 原地调整
    que.enqueue(e);
    for (int i = 0; i < que.getSize() - 1; i++) {
        que.enqueue(que.getFront());
        que.dequeue();
    }
}

template<typename T>
QueueStack<T> &QueueStack<T>::operator=(const QueueStack<T> &rhs) {
    que = rhs.que;
    return *this;
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
    ArrayStack<T> ans;
    while (!tmp.isEmpty()) {
        ans.push(tmp.getFront());
        tmp.dequeue();
    }
    while (ans.getSize() > 1) {
        os << ans.top() << ", ";
        ans.pop();
    }
    if (!ans.isEmpty())
        os << ans.top();
    os << "] top\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_QUEUE_STACK_H
