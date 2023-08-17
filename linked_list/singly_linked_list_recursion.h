#ifndef ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_RECURSION_H
#define ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_RECURSION_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class SinglyLinkedListRecursion;

template <typename T>
std::ostream &operator<<(std::ostream &, const SinglyLinkedListRecursion<T> &);

template <typename T>
class SinglyLinkedListRecursion : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const SinglyLinkedListRecursion<T> &rhs);
public:
    SinglyLinkedListRecursion():
            dummyHead(new Node()), size(0) { }

    SinglyLinkedListRecursion(const SinglyLinkedListRecursion<T> &rhs);
    SinglyLinkedListRecursion<T> &operator=(const SinglyLinkedListRecursion<T> &rhs);

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

    void swap(SinglyLinkedListRecursion<T> &rhs);

    ~SinglyLinkedListRecursion() override;

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
    void addRecursion(Node *pre, int idx, const T &e);
    T get(int idx) const;
    T getRecursion(Node *node, int idx) const;
    void remove(int idx);
    void removeRecursion(Node *pre, int idx);
    Node* removeElementsRecursion(Node *node, const T &e);
};


template<typename T>
void SinglyLinkedListRecursion<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    addRecursion(dummyHead, idx, e);
    size++;
}

template<typename T>
void SinglyLinkedListRecursion<T>::addRecursion(Node *pre, int idx, const T &e) {
    if (idx == 0) {
        pre -> next = new Node(e, pre -> next);
        return;
    }

    addRecursion(pre -> next, idx - 1, e);
}

template<typename T>
void SinglyLinkedListRecursion<T>::removeElements(const T &e) {
    dummyHead -> next = removeElementsRecursion(dummyHead -> next, e);
}


template<typename T>
typename SinglyLinkedListRecursion<T>::Node *
SinglyLinkedListRecursion<T>::removeElementsRecursion(SinglyLinkedListRecursion::Node *node, const T &e) {
    if (!node)
        return nullptr;

    node -> next = removeElementsRecursion(node -> next, e);

    if (node -> val == e) {  // 回溯时再删除
        auto delNode = node;
        node = node -> next;
        delete delNode;
        size--;
        return node;
    }
    return node;
}

template<typename T>
void SinglyLinkedListRecursion<T>::swap(SinglyLinkedListRecursion<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename T>
void SinglyLinkedListRecursion<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(size - 1);
}

template<typename T>
void SinglyLinkedListRecursion<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(0);
}

template<typename T>
T SinglyLinkedListRecursion<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    return get(size - 1);
}

template<typename T>
T SinglyLinkedListRecursion<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    return get(0);
}

template<typename T>
T SinglyLinkedListRecursion<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    return getRecursion(dummyHead -> next, idx);
}

template<typename T>
T SinglyLinkedListRecursion<T>::getRecursion(SinglyLinkedListRecursion::Node *node, int idx) const {
    if (idx == 0)
        return node -> val;

    return getRecursion(node -> next, idx - 1);
}


template<typename T>
void SinglyLinkedListRecursion<T>::remove(int idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    removeRecursion(dummyHead, idx);
    size--;
}

template<typename T>
void SinglyLinkedListRecursion<T>::removeRecursion(SinglyLinkedListRecursion::Node *pre, int idx) {
    if (idx == 0) {
        auto delNode = pre -> next;
        pre -> next = delNode -> next;
        delete delNode;
        return;
    }

    removeRecursion(pre -> next, idx - 1);
}


template<typename T>
SinglyLinkedListRecursion<T>::~SinglyLinkedListRecursion() {
    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
}

template<typename T>
SinglyLinkedListRecursion<T>::SinglyLinkedListRecursion(const SinglyLinkedListRecursion<T> &rhs):
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
SinglyLinkedListRecursion<T> &SinglyLinkedListRecursion<T>::operator=(const SinglyLinkedListRecursion<T> &rhs) {
    SinglyLinkedListRecursion<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool SinglyLinkedListRecursion<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SinglyLinkedListRecursion<T> &rhs) {
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

#endif //ALGORITHM_TEMPLATE_CPP_SINGLY_LINKED_LIST_RECURSION_H
