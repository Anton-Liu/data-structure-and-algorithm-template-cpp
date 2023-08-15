#ifndef ALGORITHM_TEMPLATE_CPP_LOOP_ARRAY_QUEUE_H
#define ALGORITHM_TEMPLATE_CPP_LOOP_ARRAY_QUEUE_H

#include "queue.h"
#include <memory>
#include <iostream>

template <typename T> class LoopArrayQueue;

template <typename T>
std::ostream &operator<<(std::ostream &, const LoopArrayQueue<T> &);

template <typename T>
class LoopArrayQueue : public Queue<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LoopArrayQueue<T> &que);
public:
    LoopArrayQueue():
            data(std::make_shared<std::vector<T>>(10 + 1)), front(0), tail(0) { }
    explicit LoopArrayQueue(int capacity):
            data(std::make_shared<std::vector<T>>(capacity + 1)), front(0), tail(0) { }

    bool isEmpty() const override { return front == tail; };
    int getSize() const override { return (tail - front + data -> size()) % data -> size(); };
    int getCapacity() const { return data -> size() - 1; };
    T getFront() const override {
        if (isEmpty())
            throw std::runtime_error("当前队列为空！");
        return (*data)[front];
    };

    void enqueue(const T &e) override;
    void dequeue() override;
private:
    int front;
    int tail;
    std::shared_ptr<std::vector<T>> data;
    void resize(int newCapacity);
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const LoopArrayQueue<T> &que) {
    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < que.getSize(); i++)
        os << "----";
    os << '\n';

    // 队列信息
    os << "队列的长度：" << que.getSize() << "，"
       << "队列的容量：" << que.getCapacity() << '\n'
       << "队列的内容：" << "queue front[";
    for (int i = que.front; i != que.tail; i = (i + 1) % que.data -> size()) {
        os << (*que.data)[i];
        if ((i + 1) % que.data -> size() != que.tail)
            os << ", ";
    }
    os << "]tail\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < que.getSize(); i++)
        os << "----";
    return os;
}

template<typename T>
void LoopArrayQueue<T>::resize(int newCapacity) {
    std::vector<T> newData(newCapacity);
    for (int i = 0; i < getSize(); i++)
        newData[i] = (*data)[(front + i) % data -> size()];
    tail = getSize();
    front = 0;
    data = std::make_shared<std::vector<T>>(newData);
}

template<typename T>
void LoopArrayQueue<T>::dequeue() {
    if (front == tail)
        throw std::runtime_error("当前队列为空！");

    front = (front + 1) % data -> size();

    if (getSize() == getCapacity() / 4 && getCapacity() / 2 != 0)
        resize(getCapacity() / 2 + 1);
}

template<typename T>
void LoopArrayQueue<T>::enqueue(const T &e) {
    if ((tail + 1) % data -> size() == front)
        resize(getCapacity() * 2 + 1);

    (*data)[tail] = e;
    tail = (tail + 1) % data -> size();
}

#endif //ALGORITHM_TEMPLATE_CPP_LOOP_ARRAY_QUEUE_H
