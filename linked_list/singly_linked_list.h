#ifndef ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class SinglyLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const SinglyLinkedList<T> &);

template <typename T>
class SinglyLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const SinglyLinkedList<T> &rhs);
public:
    SinglyLinkedList():
        dummyHead(new Node()), size(0) { }
    SinglyLinkedList(const SinglyLinkedList<T> &rhs);
    SinglyLinkedList<T> &operator=(const SinglyLinkedList<T> &rhs);

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
    void swap(SinglyLinkedList<T> &rhs);

    ~SinglyLinkedList() override;
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
void SinglyLinkedList<T>::reverseList() {
    Node *pre = nullptr;
    auto cur = dummyHead -> next;

    while (cur) {
        auto r = cur -> next;  // 防断链
        cur -> next = pre;
        pre = cur;
        cur = r;
    }
    dummyHead -> next = pre;
}

template<typename T>
void SinglyLinkedList<T>::removeElements(const T &e) {
    auto pre = dummyHead;
    while (pre -> next) {
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
void SinglyLinkedList<T>::swap(SinglyLinkedList<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename T>
void SinglyLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(size - 1);
}

template<typename T>
void SinglyLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(0);
}

template<typename T>
T SinglyLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(size - 1);
}

template<typename T>
T SinglyLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(0);
}

template<typename T>
void SinglyLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    pre -> next = new Node(e, pre -> next);
    size++;
}

template<typename T>
T SinglyLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
void SinglyLinkedList<T>::remove(int idx) {
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
SinglyLinkedList<T>::~SinglyLinkedList() {
    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != nullptr) {
        pre -> next = new Node(rhsCur -> val);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
}

template<typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &rhs) {
    SinglyLinkedList<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool SinglyLinkedList<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SinglyLinkedList<T> &rhs) {
    auto size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "链表的长度：" << size << "\n"
       << "链表的内容：" << "list: ";

    for (int i = 0; i < size; i++)
        os << "(" << rhs.get(i) << ")->";
    os << "NULL\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_H
