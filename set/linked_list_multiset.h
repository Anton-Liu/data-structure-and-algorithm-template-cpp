#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MULTISET_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MULTISET_H

#include <iostream>
#include "set.h"
#include "../linked_list/singly_linked_list.h"

template <typename T> class LinkedListMultiset;

template <typename T>
std::ostream &operator<<(std::ostream &, const LinkedListMultiset<T> &);

template <typename T>
class LinkedListMultiset : public Set<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const LinkedListMultiset<T> &rhs);
public:
    LinkedListMultiset():
            list(new SinglyLinkedList<T>()) { }
    LinkedListMultiset(const LinkedListMultiset<T> &rhs):
            list(new SinglyLinkedList<T>(*rhs.list)) { }
    LinkedListMultiset<T> &operator=(const LinkedListMultiset<T> &rhs);

    int getSize() const override { return list -> getSize(); };
    bool isEmpty() const override { return list -> isEmpty(); };
    bool contains(const T &e) const override { return list -> contains(e); };

    void add(const T &e) override { list -> addFirst(e); };
    void remove(const T &e) override { list -> removeElements(e); };
    void swap(LinkedListMultiset<T> &rhs);

    ~LinkedListMultiset() { delete list; }

private:
    SinglyLinkedList<T> *list;
};


template<typename T>
void LinkedListMultiset<T>::swap(LinkedListMultiset<T> &rhs) {
    std::swap(list, rhs.list);
}

template<typename T>
LinkedListMultiset<T> &LinkedListMultiset<T>::operator=(const LinkedListMultiset<T> &rhs) {
    LinkedListMultiset<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const LinkedListMultiset<T> &rhs) {
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
    auto tmp = *rhs.list;
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

#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MULTISET_H
