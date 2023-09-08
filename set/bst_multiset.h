#ifndef ALGORITHM_TEMPLATE_CPP_BST_MULTISET_H
#define ALGORITHM_TEMPLATE_CPP_BST_MULTISET_H

#include "set.h"
#include "../tree/binary_search_tree_equal_recursion.h"

template <typename T> class BSTMultiset;

template <typename T>
std::ostream &operator<<(std::ostream &, const BSTMultiset<T> &);

template <typename T>
class BSTMultiset : public Set<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const BSTMultiset<T> &rhs);
public:
    BSTMultiset():
            bst(new BinarySearchTreeEqualRecursion<T>()) { }
    BSTMultiset(const BSTMultiset<T> &rhs):
            bst(new BinarySearchTreeEqualRecursion<T>(rhs)) { }
    BSTMultiset<T> &operator=(const BSTMultiset<T> &rhs);

    int getSize() const override { return bst -> getSize(); };
    bool isEmpty() const override { return bst -> isEmpty(); };
    bool contains(const T &e) const override { return bst -> contains(e); };

    void add(const T &e) override { bst -> add(e); };
    void remove(const T &e) override { bst -> removeAll(e); };
    void swap(BSTMultiset<T> &rhs);

    ~BSTMultiset() { delete bst; }

private:
    BinarySearchTreeEqualRecursion<T> *bst;
};

template<typename T>
void BSTMultiset<T>::swap(BSTMultiset<T> &rhs) {
    std::swap(bst, rhs.bst);
}

template<typename T>
BSTMultiset<T> &BSTMultiset<T>::operator=(const BSTMultiset<T> &rhs) {
    BSTMultiset<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BSTMultiset<T> &rhs) {
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
            tmp.removeOneMin();
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

#endif //ALGORITHM_TEMPLATE_CPP_BST_MULTISET_H
