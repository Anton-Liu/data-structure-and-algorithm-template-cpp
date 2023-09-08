#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H

#include <iostream>
#include "set.h"
#include "../linked_list/singly_linked_list.h"

template <typename T> class LinkedListSet;

template <typename T>
std::ostream &operator<<(std::ostream &, const LinkedListSet<T> &);

template <typename T>
class LinkedListSet : public Set<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LinkedListSet<T> &rhs);
public:
    LinkedListSet():
            bst(new SinglyLinkedList<T>()) { }
    LinkedListSet(const LinkedListSet<T> &rhs):
            bst(new SinglyLinkedList<T>(rhs)) { }
    LinkedListSet<T> &operator=(const LinkedListSet<T> &rhs);

    int getSize() const override { return bst -> getSize(); };
    bool isEmpty() const override { return bst -> isEmpty(); };
    bool contains(const T &e) const override { return bst -> contains(e); };

    void add(const T &e) override {
        if (!bst -> contains(e))
            bst -> addFirst(e);
    };
    void remove(const T &e) override { bst -> removeElements(e); };
    void swap(LinkedListSet<T> &rhs);

    ~LinkedListSet() { delete bst; }

private:
    SinglyLinkedList<T> *bst;
};

template<typename T>
void LinkedListSet<T>::swap(LinkedListSet<T> &rhs) {
    std::swap(bst, rhs.bst);
}

template<typename T>
LinkedListSet<T> &LinkedListSet<T>::operator=(const LinkedListSet<T> &rhs) {
    LinkedListSet<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const LinkedListSet<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "Set的大小：" << size << "\n"
       << "Set的内容：\n";

    os << "{";
    auto tmp = *rhs.bst;
    for (int i = 0; i < size; i++) {
        if (i != size - 1)
            os << tmp.getFirst() << ", ";
        else
            os << tmp.getFirst();
        tmp.removeFirst();
    }
    os << "}\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H
