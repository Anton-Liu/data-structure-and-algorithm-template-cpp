#ifndef ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class DoublyLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const DoublyLinkedList<T> &);

template <typename T>
class DoublyLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const DoublyLinkedList<T> &rhs);
public:
    DoublyLinkedList():
            dummyHead(new Node()), size(0) { }

    DoublyLinkedList(const DoublyLinkedList<T> &rhs);
    DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &rhs);

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

    void swap(DoublyLinkedList<T> &rhs);

    ~DoublyLinkedList() override;

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
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != nullptr) {
        pre -> next = new Node(rhsCur -> val, pre, nullptr);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
}

template<typename T>
void DoublyLinkedList<T>::swap(DoublyLinkedList<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &rhs) {
    DoublyLinkedList<T>(rhs).swap(*this);
    return *this;

}

template<typename T>
bool DoublyLinkedList<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template<typename T>
T DoublyLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("索引超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
T DoublyLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");
    return get(0);
}

template<typename T>
T DoublyLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");
    return get(size  - 1);
}

template<typename T>
void DoublyLinkedList<T>::remove(int idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("索引超过链表范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    auto delNode = pre -> next;
    if (delNode -> next) {
        pre -> next = delNode -> next;
        delNode-> next -> prev = delNode -> prev;
    }
    else
        pre -> next = nullptr;
    delete delNode;

    size--;
}

template<typename T>
void DoublyLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");
    remove(0);
}

template<typename T>
void DoublyLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");
    remove(size - 1);
}

template<typename T>
void DoublyLinkedList<T>::removeElements(const T &e) {
    auto pre = dummyHead;
    while (pre -> next) {
        if (pre -> next -> val == e) {
            auto delNode = pre -> next;
            if (delNode -> next) {
                pre -> next = delNode -> next;
                delNode-> next -> prev = delNode -> prev;
            }
            else
                pre -> next = nullptr;
            delete delNode;
            size--;
        }
        else
            pre = pre -> next;
    }
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    auto delNode = dummyHead;
    while (dummyHead) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
}

template<typename T>
void DoublyLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;
    pre -> next = new Node(e, pre, pre -> next);
    size++;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "双链表的长度：" << size << "\n"
       << "双链表的内容：" << "list: ";

    for (int i = 0; i < size; i++) {
        os << "(" << rhs.get(i);
        if (i == size - 1)
            os << ")->";
        else
            os << ")<->";
    }
    os << "NULL\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_H
