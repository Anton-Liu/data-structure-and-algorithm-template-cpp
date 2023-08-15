#ifndef ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_WITH_TAIL_POINTER_H
#define ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_WITH_TAIL_POINTER_H

#include "linked_list.h"
#include <iostream>

template <typename T>
class SingleLinkedListWithTailPointer;

template <typename T>
std::ostream &operator<<(std::ostream &, const SingleLinkedListWithTailPointer<T> &);

template <typename T>
class SingleLinkedListWithTailPointer : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const SingleLinkedListWithTailPointer<T> &rhs);
public:
    SingleLinkedListWithTailPointer():
            dummyHead(new Node()), size(0) { tail = dummyHead; }

    SingleLinkedListWithTailPointer(const SingleLinkedListWithTailPointer<T> &rhs);
    SingleLinkedListWithTailPointer<T> &operator=(const SingleLinkedListWithTailPointer<T> &rhs);

    int getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }
    bool contains(const T &e) const override;
    T getFirst() const override;
    T getLast() const override;

    void addFirst(const T &e) override { add(0, e); };
    void addLast(const T &e) override;
    void removeFirst() override;
    void removeLast() override;

    ~SingleLinkedListWithTailPointer() override;
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
    Node *tail;
    int size;

    void add(int idx, const T &e);
    T get(int idx) const;
    void remove(int idx);
};

template<typename T>
SingleLinkedListWithTailPointer<T>::~SingleLinkedListWithTailPointer() {
    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }
    tail = nullptr;
}

template<typename T>
SingleLinkedListWithTailPointer<T>::SingleLinkedListWithTailPointer(const SingleLinkedListWithTailPointer<T> &rhs):
        dummyHead(new Node()), size(rhs.size) {
    tail = dummyHead;
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
SingleLinkedListWithTailPointer<T> &
SingleLinkedListWithTailPointer<T>::operator=(const SingleLinkedListWithTailPointer<T> &rhs) {
    auto tmp = SingleLinkedListWithTailPointer<T>(rhs);

    auto delNode = dummyHead;
    while (dummyHead != nullptr) {
        dummyHead = dummyHead -> next;
        delete delNode;
        delNode = dummyHead;
    }

    dummyHead = new Node();
    auto pre = dummyHead;
    tail = dummyHead;
    auto rhsCur = tmp.dummyHead -> next;
    while (rhsCur != nullptr) {
        pre -> next = new Node(rhsCur -> val);
        pre = pre -> next;
        tail = pre;
        rhsCur = rhsCur -> next;
    }
    pre -> next = nullptr;
    size = tmp.size;

    return *this;
}

template<typename T>
T SingleLinkedListWithTailPointer<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    return get(0);
}

template<typename T>
T SingleLinkedListWithTailPointer<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return tail -> val;
}

template<typename T>
void SingleLinkedListWithTailPointer<T>::addLast(const T &e) {
    tail -> next = new Node(e);
    tail = tail -> next;
    size++;
}

template<typename T>
void SingleLinkedListWithTailPointer<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(0);
}

template<typename T>
void SingleLinkedListWithTailPointer<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");
    remove(size - 1);
}

template<typename T>
bool SingleLinkedListWithTailPointer<T>::contains(const T &e) const  {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> val == e)
            return true;
        cur = cur -> next;
    }
    return false;
}

template<typename T>
void SingleLinkedListWithTailPointer<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > size)
        throw std::runtime_error("超过链表可插入范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    pre -> next = new Node(e, pre -> next);
    if (size == 0)  // 插入第一个元素时需要更新尾指针
        tail = tail -> next;
    size++;
}

template<typename T>
T SingleLinkedListWithTailPointer<T>::get(int idx) const {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto cur = dummyHead -> next;
    for (int i = 0; i < idx; i++)
        cur = cur -> next;
    return cur -> val;
}

template<typename T>
void SingleLinkedListWithTailPointer<T>::remove(int idx) {
    if (idx < 0 || idx >= size)
        throw std::runtime_error("超过链表范围！");

    auto pre = dummyHead;
    for (int i = 0; i < idx; i++)
        pre = pre -> next;

    if (idx == size - 1)
        tail = pre;

    auto delNode = pre -> next;
    pre -> next = delNode -> next;
    delete delNode;

    size--;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SingleLinkedListWithTailPointer<T> &rhs) {
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

#endif //ALGORITHM_TEMPLATE_CPP_SINGLE_LINKED_LIST_WITH_TAIL_POINTER_H
