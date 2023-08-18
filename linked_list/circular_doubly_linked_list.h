#ifndef ALGORITHM_TEMPLATE_CPP_CIRCULAR_DOUBLY_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_CIRCULAR_DOUBLY_LINKED_LIST_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class CircularDoublyLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const CircularDoublyLinkedList<T> &);

template <typename T>
class CircularDoublyLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const CircularDoublyLinkedList<T> &rhs);
public:
    CircularDoublyLinkedList():
            dummyHead(new Node()), size(0) { dummyHead -> next = dummyHead; dummyHead -> prev = dummyHead; }

    CircularDoublyLinkedList(const CircularDoublyLinkedList<T> &rhs);
    CircularDoublyLinkedList<T> &operator=(const CircularDoublyLinkedList<T> &rhs);

    int getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
    bool contains(const T &e) const override;
    T getFirst() const override;
    T getLast() const override;

    void addFirst(const T &e) override { add(0, e); };
    void addLast(const T &e) override;
    void removeFirst() override;
    void removeLast() override;
    void removeElements(const T &e);

    void swap(CircularDoublyLinkedList<T> &rhs);

    ~CircularDoublyLinkedList() override;

private:
    class Node {
    public:
        T val;
        Node *prev;
        Node *next;

        Node(T val, Node *prev, Node *next):
                val(val), prev(prev), next(next) { }
        explicit Node(T val):
                Node(val, nullptr, nullptr) { }
        Node():
                Node(T(), nullptr, nullptr) { }
    };
    Node *dummyHead;
    int size;

    void add(int idx, const T &e);
    T get(int idx) const;
    void remove(int idx);
};

template<typename T>
void CircularDoublyLinkedList<T>::addLast(const T &e) {
    dummyHead -> prev -> next = new Node(e, dummyHead -> prev, dummyHead);
    dummyHead -> prev = dummyHead -> prev -> next;
    size++;
}

template<typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != rhs.dummyHead) {
        pre -> next = new Node(rhsCur -> val, pre, nullptr);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
    pre -> next = dummyHead;
    dummyHead -> prev = pre;
}

template<typename T>
void CircularDoublyLinkedList<T>::swap(CircularDoublyLinkedList<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename T>
CircularDoublyLinkedList<T> &CircularDoublyLinkedList<T>::operator=(const CircularDoublyLinkedList<T> &rhs) {
    CircularDoublyLinkedList<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool CircularDoublyLinkedList<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur != dummyHead) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template<typename T>
T CircularDoublyLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("索引超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
T CircularDoublyLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    return get(0);
}

template<typename T>
T CircularDoublyLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    return dummyHead -> prev -> val;
}

template<typename T>
void CircularDoublyLinkedList<T>::remove(int idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("索引超过链表范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    auto delNode = pre -> next;
    if (delNode -> next != dummyHead) {
        pre -> next = delNode -> next;
        delNode-> next -> prev = delNode -> prev;
    }
    else {
        dummyHead -> prev = pre;
        pre -> next = dummyHead;
    }
    delete delNode;

    size--;
}

template<typename T>
void CircularDoublyLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    remove(0);
}

template<typename T>
void CircularDoublyLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    auto delNode = dummyHead -> prev;
    dummyHead -> prev = delNode -> prev;
    delNode -> prev -> next = dummyHead;
}

template<typename T>
void CircularDoublyLinkedList<T>::removeElements(const T &e) {
    auto pre = dummyHead;
    while (pre -> next != dummyHead) {
        if (pre -> next -> val == e) {
            auto delNode = pre -> next;
            if (delNode -> next != dummyHead) {
                pre -> next = delNode -> next;
                delNode-> next -> prev = delNode -> prev;
            }
            else {
                dummyHead -> prev = pre;
                pre -> next = dummyHead;
            }
            delete delNode;
            size--;
        }
        else
            pre = pre -> next;
    }
}

template<typename T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList() {
    auto pre = dummyHead;
    while (pre -> next != dummyHead) {
        auto delNode = pre -> next;
        pre -> next = delNode -> next;
        delete delNode;
    }
    delete dummyHead;
}

template<typename T>
void CircularDoublyLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;
    pre -> next = new Node(e, pre, pre -> next);

    size++;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const CircularDoublyLinkedList<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "双链表的长度：" << size << "\n"
       << "双链表的内容：" << "list: ";

    if (size == 0)
        os << "NULL\n";
    else {
        for (int i = 0; i < size; i++) {
            os << "(" << rhs.get(i) << ")";
            if (i != size - 1)
                os << "<->";
        }
        os << "\n                     ↑";
        for (int i = 0; i < size - 1; i++)
            os << (i == size - 2 ? "     " :  "      ");
        os << "↑\n";
        os << "                       ";
        for (int i = 0; i < size - 1; i++)
            os << "--    ";
        os << "\n";
    }

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}


#endif //ALGORITHM_TEMPLATE_CPP_CIRCULAR_DOUBLY_LINKED_LIST_H
