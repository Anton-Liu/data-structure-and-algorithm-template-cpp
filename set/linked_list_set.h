#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H

#include "set.h"
#include "../linked_list/singly_linked_list.h"

template <typename T>
class LinkedListSet : public Set<T> {
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



#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_SET_H
