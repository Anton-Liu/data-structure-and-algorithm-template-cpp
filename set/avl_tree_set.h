#ifndef ALGORITHM_TEMPLATE_CPP_AVL_TREE_SET_H
#define ALGORITHM_TEMPLATE_CPP_AVL_TREE_SET_H

#include <iostream>
#include "set.h"
#include "../tree/avl_tree.h"

template <typename T> class AVLTreeSet;

template <typename T>
std::ostream &operator<<(std::ostream &, const AVLTreeSet<T> &);

template <typename T>
class AVLTreeSet : public Set<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const AVLTreeSet<T> &rhs);
public:
    AVLTreeSet():
            avlTree(new AVLTree<T>()) { }
    AVLTreeSet(const AVLTreeSet<T> &rhs):
            avlTree(new AVLTree<T>(rhs)) { }
    AVLTreeSet<T> &operator=(const AVLTreeSet<T> &rhs);

    int getSize() const override { return avlTree -> getSize(); };
    bool isEmpty() const override { return avlTree -> isEmpty(); };
    bool contains(const T &e) const override { return avlTree -> contains(e); };

    void add(const T &e) override { avlTree -> add(e); };
    void remove(const T &e) override { avlTree -> remove(e); };
    void swap(AVLTreeSet<T> &rhs);

    ~AVLTreeSet() { delete avlTree; }

private:
    AVLTree<T> *avlTree;
};

template<typename T>
void AVLTreeSet<T>::swap(AVLTreeSet<T> &rhs) {
    std::swap(avlTree, rhs.avlTree);
}

template<typename T>
AVLTreeSet<T> &AVLTreeSet<T>::operator=(const AVLTreeSet<T> &rhs) {
    AVLTreeSet<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const AVLTreeSet<T> &rhs) {
    auto size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "Set的大小：" << size << "\n"
       << "Set的内容：\n";

    os << "{";
    auto tmp = *rhs.avlTree;
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

#endif //ALGORITHM_TEMPLATE_CPP_AVL_TREE_SET_H
