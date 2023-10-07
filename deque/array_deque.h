#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_DEQUE_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_DEQUE_H

#include "deque.h"
#include <memory>
#include <vector>
#include <iostream>

template <typename T> class ArrayDeque;

template <typename T>
std::ostream &operator<<(std::ostream &, const ArrayDeque<T> &);

template <typename T>
class ArrayDeque : public Deque<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const ArrayDeque<T> &que);
public:
    ArrayDeque():
        data(std::make_shared<std::vector<T>>(10)),
        front(0), tail(0), size(0) { }
    explicit ArrayDeque(int capacity):
        data(std::make_shared<std::vector<T>>(capacity)),
        front(0), tail(0), size(0) { }

    bool isEmpty() const override { return size == 0; }
    int getSize() const override { return size; }
    int getCapacity() const override { return data -> size(); }

    T getFront() const override {
        if (size == 0)
            throw std::runtime_error("当前双端队列为空！");

        return (*data)[front];
    }

    T getLast() const override {
        if (size == 0)
            throw std::runtime_error("当前双端队列为空！");

        return (*data)[tail == 0 ? data -> size() - 1 : tail - 1];
    }

    void addFront(const T &e) override;
    void addLast(const T &e) override;
    void removeFront() override;
    void removeLast() override;

private:
    std::shared_ptr<std::vector<T>> data;
    int front;
    int tail;
    int size;  // 记录元素数量

    void resize(int newCapacity);  // 调整容量
};

template<typename T>
void ArrayDeque<T>::resize(int newCapacity) {
    std::vector<T> newData(newCapacity);
    for (int i = 0; i < size; i++)
        newData[i] = (*data)[(i + front) % data -> size()];
    front = 0;
    tail = size;
    data = std::make_shared<std::vector<T>>(newData);
}

template<typename T>
void ArrayDeque<T>::addFront(const T &e) {
    if (size == data -> size())
        resize(data -> size() * 2);

    front = front == 0 ? data -> size() - 1 : front - 1;
    (*data)[front] = e;
    size++;
}

template<typename T>
void ArrayDeque<T>::addLast(const T &e) {
    if (size == data -> size())
        resize(data -> size() * 2);

    (*data)[tail] = e;
    tail = (tail + 1) % data -> size();
    size++;
}

template<typename T>
void ArrayDeque<T>::removeFront() {
    if (size == 0)
        throw std::runtime_error("当前双端队列为空，不能删除元素！");

    front = (front + 1) % data -> size();
    size--;

    if (size == data -> size() / 4 && data -> size() / 2 != 0)
        resize(data -> size() / 2);
}

template<typename T>
void ArrayDeque<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("当前双端队列为空，不能删除元素！");

    tail = tail == 0 ? data -> size() - 1 : tail - 1;
    size--;

    if (size == data -> size() / 4 && data -> size() / 2 != 0)
        resize(data -> size() / 2);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayDeque<T> &que) {
    int size = que.size;
    int capacity = (que.data) -> size();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 队列信息
    os << "双端队列的长度：" << size << "，"
       << "双端队列的容量：" << capacity << '\n'
       << "双端队列的内容：" << "deque front[";
    for (int i = 0; i < size; i++) {
        os << (*que.data)[(i + que.front) % capacity];
        if (i != size - 1)
            os << ", ";
    }
    os << "]tail\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_DEQUE_H
