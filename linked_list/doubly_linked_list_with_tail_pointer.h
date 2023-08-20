#ifndef ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_WITH_TAIL_POINTER_H
#define ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_WITH_TAIL_POINTER_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class DoublyLinkedListWithTailPointer;

template <typename T>
std::ostream &operator<<(std::ostream &, const DoublyLinkedListWithTailPointer<T> &);

template <typename T>
class DoublyLinkedListWithTailPointer : public LinkedList<T>{
    friend std::ostream &operator<<<T>(std::ostream &os, const DoublyLinkedListWithTailPointer<T> &rhs);
public:
    DoublyLinkedListWithTailPointer():
            dummyHead(new Node()), size(0) { tail = dummyHead; }

    DoublyLinkedListWithTailPointer(const DoublyLinkedListWithTailPointer<T> &rhs);
    DoublyLinkedListWithTailPointer<T> &operator=(const DoublyLinkedListWithTailPointer<T> &rhs);

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
    void reverseList();

    void swap(DoublyLinkedListWithTailPointer<T> &rhs);

    ~DoublyLinkedListWithTailPointer() override;

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
    Node *tail;
    int size;

    void add(int idx, const T &e);
    T get(int idx) const;
    void remove(int idx);
};

template<typename T>
void DoublyLinkedListWithTailPointer<T>::reverseList() {
    if (size == 0)
        return;

    using std::swap;
    auto cur = dummyHead -> next;
    tail = cur;
    while (cur -> next) {
        swap(cur -> next, cur -> prev);
        cur = cur -> prev;
    }
    swap(cur -> next, cur -> prev);
    cur -> prev = dummyHead;
    dummyHead -> next -> next = nullptr;
    dummyHead -> next = cur;
}

template<typename T>
DoublyLinkedListWithTailPointer<T>::DoublyLinkedListWithTailPointer(const DoublyLinkedListWithTailPointer<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur != nullptr) {
        pre -> next = new Node(rhsCur -> val, pre, nullptr);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
    tail = pre;
}

template<typename T>
void DoublyLinkedListWithTailPointer<T>::swap(DoublyLinkedListWithTailPointer<T> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(tail, rhs.tail);
    swap(size, rhs.size);
}

template<typename T>
DoublyLinkedListWithTailPointer<T> &
DoublyLinkedListWithTailPointer<T>::operator=(const DoublyLinkedListWithTailPointer<T> &rhs) {
    DoublyLinkedListWithTailPointer<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool DoublyLinkedListWithTailPointer<T>::contains(const T &e) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template<typename T>
T DoublyLinkedListWithTailPointer<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("索引超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
T DoublyLinkedListWithTailPointer<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");
    return get(0);
}

template<typename T>
T DoublyLinkedListWithTailPointer<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    return tail -> val;
}

template<typename T>
void DoublyLinkedListWithTailPointer<T>::remove(int idx) {
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
void DoublyLinkedListWithTailPointer<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    remove(0);
}

template<typename T>
void DoublyLinkedListWithTailPointer<T>::removeLast() {  // O(1)
    if (size == 0)
        throw std::runtime_error("当前链表为空！");

    auto delNode = tail;
    delNode -> prev -> next = nullptr;
    delete delNode;
}

template<typename T>
void DoublyLinkedListWithTailPointer<T>::removeElements(const T &e) {
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
DoublyLinkedListWithTailPointer<T>::~DoublyLinkedListWithTailPointer() {
    auto delNode = dummyHead;
    while (dummyHead) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
}

template<typename T>
void DoublyLinkedListWithTailPointer<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;
    pre -> next = new Node(e, pre, pre -> next);
    size++;
}


template<typename T>
void DoublyLinkedListWithTailPointer<T>::addLast(const T &e) {
    tail -> next = new Node(e, tail, nullptr);
    tail = tail -> next;
    size++;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoublyLinkedListWithTailPointer<T> &rhs) {
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

#endif //ALGORITHM_TEMPLATE_CPP_DOUBLY_LINKED_LIST_WITH_TAIL_POINTER_H
