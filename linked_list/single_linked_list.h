#ifndef ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class SingleLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const SingleLinkedList<T> &);

template <typename T>
class SingleLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const SingleLinkedList<T> &rhs);
public:
    SingleLinkedList():
        dummyHead(new Node()), size(0) { }

    SingleLinkedList(const SingleLinkedList<T> &rhs);
    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &rhs);

    int getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
    bool contains(const T &e) const override;
    T getFirst() const override;
    T getLast() const override;

    void addFirst(const T &e) override { add(0, e); };
    void addLast(const T &e) override { add(size, e); };
    void removeFirst() override;
    void removeLast() override;

    ~SingleLinkedList() override;
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
void SingleLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(size - 1);
}

template<typename T>
void SingleLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(0);
}

template<typename T>
T SingleLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    return get(size - 1);
}

template<typename T>
T SingleLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    return get(0);
}

template<typename T>
void SingleLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    pre -> next = new Node(e, pre -> next);
    size++;
}

template<typename T>
T SingleLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
void SingleLinkedList<T>::remove(int idx) {
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
SingleLinkedList<T>::~SingleLinkedList() {
    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto cur = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != nullptr) {
        cur -> next = new Node(rhsCur -> val);
        cur = cur -> next;
        rhsCur = rhsCur -> next;
    }
    cur -> next = nullptr;
}

template<typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &rhs) {
    auto tmp = SingleLinkedList<T>(rhs);

    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }

    dummyHead = new Node();
    auto cur = dummyHead;
    auto rhsCur = tmp.dummyHead -> next;
    while (rhsCur != nullptr) {
        cur -> next = new Node(rhsCur -> val);
        cur = cur -> next;
        rhsCur = rhsCur -> next;
    }
    cur -> next = nullptr;
    size = tmp.size;

    return *this;
}

template<typename T>
bool SingleLinkedList<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SingleLinkedList<T> &rhs) {
    int size = rhs.getSize();

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

#endif //ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_H
