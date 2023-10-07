#ifndef ALGORITHM_TEMPLATE_CPP_CIRCULAR_SINGLY_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_CIRCULAR_SINGLY_LINKED_LIST_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class CircularSinglyLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const CircularSinglyLinkedList<T> &);

template <typename T>
class CircularSinglyLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const CircularSinglyLinkedList<T> &rhs);
public:
    CircularSinglyLinkedList():
            dummyHead(new Node()), size(0) { dummyHead -> next = dummyHead; }
    CircularSinglyLinkedList(const CircularSinglyLinkedList<T> &rhs);
    CircularSinglyLinkedList<T> &operator=(const CircularSinglyLinkedList<T> &rhs);

    int getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
    bool contains(const T &e) const override;
    T getFirst() const override;
    T getLast() const override;

    void addFirst(const T &e) override { add(0, e); };
    void addLast(const T &e) override { add(size, e); };
    void removeFirst() override;
    void removeLast() override;
    void removeElements(const T &e);
    void reverseList();
    void swap(CircularSinglyLinkedList<T> &rhs);

    ~CircularSinglyLinkedList() override;

private:
    class Node {
    public:
        T val;
        Node *next;

        Node(T val, Node *next):
                val(val), next(next) { }
        explicit Node(T val):
                Node(val, nullptr) { }
        Node():
                Node(T(), nullptr) { }
    };
    Node *dummyHead;
    int size;

    void add(int idx, const T &e);
    T get(int idx) const;
    void remove(int idx);
};

template<typename T>
void CircularSinglyLinkedList<T>::reverseList() {
    auto pre = dummyHead;
    auto cur = dummyHead -> next;

    while (cur != dummyHead) {
        auto r = cur -> next;  // 防断链
        cur -> next = pre;
        pre = cur;
        cur = r;
    }
    dummyHead -> next = pre;
}


template<typename T>
void CircularSinglyLinkedList<T>::removeElements(const T &e) {
    auto pre = dummyHead;
    while (pre -> next != dummyHead) {
        if (pre -> next -> val == e) {
            auto delNode = pre -> next;
            pre -> next = delNode -> next;
            delete delNode;
            size--;
        }
        else
            pre = pre -> next;
    }
}

template<typename T>
void CircularSinglyLinkedList<T>::swap(CircularSinglyLinkedList<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename T>
void CircularSinglyLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(size - 1);
}

template<typename T>
void CircularSinglyLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(0);
}

template<typename T>
T CircularSinglyLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(size - 1);
}

template<typename T>
T CircularSinglyLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(0);
}

template<typename T>
void CircularSinglyLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    pre -> next = new Node(e, pre -> next);
    size++;
}

template<typename T>
T CircularSinglyLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
void CircularSinglyLinkedList<T>::remove(int idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    auto delNode = pre -> next;
    pre -> next = delNode -> next;
    delete delNode;
    size--;
}

template<typename T>
CircularSinglyLinkedList<T>::~CircularSinglyLinkedList() {
    auto pre = dummyHead;
    while (pre -> next != dummyHead) {
        auto delNode = pre -> next;
        pre -> next = delNode -> next;
        delete delNode;
    }
    delete dummyHead;
}

template<typename T>
CircularSinglyLinkedList<T>::CircularSinglyLinkedList(const CircularSinglyLinkedList<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != rhs.dummyHead) {
        pre -> next = new Node(rhsCur -> val);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
    pre -> next = dummyHead;
}

template<typename T>
CircularSinglyLinkedList<T> &CircularSinglyLinkedList<T>::operator=(const CircularSinglyLinkedList<T> &rhs) {
    CircularSinglyLinkedList<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool CircularSinglyLinkedList<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur != dummyHead) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const CircularSinglyLinkedList<T> &rhs) {
    auto size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "链表的长度：" << size << "\n"
       << "链表的内容：" << "list: ";

    if (size == 0)
        os << "NULL\n";
    else {
        for (int i = 0; i < size; i++) {
            os << "(" << rhs.get(i) << ")";
            if (i != size - 1)
                os << "->";
        }
        os << "\n                   ↑";
        for (int i = 0; i < size - 1; i++)
            os << (i == size - 2 ? "    " :  "     ");
        os << "↓\n";
        os << "                     ";
        for (int i = 0; i < size - 1; i++)
            os << "<-   ";
        os << "\n";
    }

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_CIRCULAR_SINGLY_LINKED_LIST_H
