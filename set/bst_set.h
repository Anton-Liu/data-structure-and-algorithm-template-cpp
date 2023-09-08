#ifndef ALGORITHM_TEMPLATE_CPP_BST_SET_H
#define ALGORITHM_TEMPLATE_CPP_BST_SET_H

#include <iostream>
#include "set.h"
#include "../tree/binary_search_tree_recursion.h"

template <typename T> class BSTSet;

template <typename T>
std::ostream &operator<<(std::ostream &, const BSTSet<T> &);

template <typename T>
class BSTSet : public Set<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const BSTSet<T> &rhs);
public:
    BSTSet():
            bst(new BinarySearchTreeRecursion<T>()) { }
    BSTSet(const BSTSet<T> &rhs):
            bst(new BinarySearchTreeRecursion<T>(rhs)) { }
    BSTSet<T> &operator=(const BSTSet<T> &rhs);

    int getSize() const override { return bst -> getSize(); };
    bool isEmpty() const override { return bst -> isEmpty(); };
    bool contains(const T &e) const override { return bst -> contains(e); };

    void add(const T &e) override { bst -> add(e); };
    void remove(const T &e) override { bst -> remove(e); };
    void swap(BSTSet<T> &rhs);

    ~BSTSet() { delete bst; }

private:
    BinarySearchTreeRecursion<T> *bst;
};

template<typename T>
void BSTSet<T>::swap(BSTSet<T> &rhs) {
    std::swap(bst, rhs.bst);
}

template<typename T>
BSTSet<T> &BSTSet<T>::operator=(const BSTSet<T> &rhs) {
    BSTSet<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BSTSet<T> &rhs) {
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
        if (i != size - 1) {
            os << tmp.minimum() << ", ";
            tmp.removeMin();
        }
        else {
            os << tmp.minimum();
        }
    }
    os << "}\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_BST_SET_H
