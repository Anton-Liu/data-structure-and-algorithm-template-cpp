#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_RECURSION_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_RECURSION_H

#include <iostream>

template <typename T>
class BinarySearchTreeRecursion {
public:
    BinarySearchTreeRecursion():
        root(nullptr), size(0) { }
    BinarySearchTreeRecursion(const BinarySearchTreeRecursion<T> &rhs);
    BinarySearchTreeRecursion<T> &operator=(const BinarySearchTreeRecursion<T> &rhs);

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    bool contains(const T &e) const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    T minimum() const;
    T maximum() const;

    void add(const T &e) { root = addRecursion(root, e); }
    void removeMin();
    void removeMax();
    void remove(const T &e);

private:
    class Node {
    public:
        T val;
        Node *left;
        Node *right;

        explicit Node(T val):
            val(val), left(nullptr), right(nullptr) { }
    };
    Node *root;
    int size;

    void visit(const Node *node) const;
    void preOrder(const Node *node) const;
    void inOrder(const Node *node) const;
    void postOrder(const Node *node) const;
    bool contains(const Node *node, const T &e) const;
    T minimum(const Node *node) const;
    T maximum(const Node *node) const;

    Node *add(Node *node, const T &e);
    Node *removeMin(Node *node);
    Node *removeMax(Node *node);
};

template<typename T>
BinarySearchTreeRecursion<T>::BinarySearchTreeRecursion(const BinarySearchTreeRecursion<T> &rhs) {

}

template<typename T>
BinarySearchTreeRecursion<T> &BinarySearchTreeRecursion<T>::operator=(const BinarySearchTreeRecursion<T> &rhs) {

}

template<typename T>
bool BinarySearchTreeRecursion<T>::contains(const T &e) const {
    return containsRecursion(root, e);
}

template<typename T>
bool BinarySearchTreeRecursion<T>::contains(const BinarySearchTreeRecursion:: Node *node, const T &e) const {
    if (!node)
        return false;
    if (e == node -> val)
        return true;

    if (e < node -> val)
        return containsRecursion(node -> left, e);
    // e > node -> val
    return containsRecursion(node -> right, e);
}


template<typename T>
void BinarySearchTreeRecursion<T>::visit(const BinarySearchTreeRecursion::Node *node) const {
    std::cout << "当前访问结点" << node -> val << std::endl;
}

template<typename T>
void BinarySearchTreeRecursion<T>::preOrder() const {
    preOrderRecursion(root);
}

template<typename T>
void BinarySearchTreeRecursion<T>::preOrder(const BinarySearchTreeRecursion::Node *node) const {
    if (!node)
        return;

    visit(node);
    preOrderRecursion(node -> left);
    preOrderRecursion(node -> right);
}

template<typename T>
void BinarySearchTreeRecursion<T>::inOrder() const {
    inOrderRecursion(root);
}

template<typename T>
void BinarySearchTreeRecursion<T>::inOrder(const BinarySearchTreeRecursion::Node *node) const {
    if (!node)
        return;

    inOrderRecursion(node -> left);
    visit(node);
    inOrderRecursion(node -> right);
}

template<typename T>
void BinarySearchTreeRecursion<T>::postOrder() const {
    postOrderRecursion(root);
}

template<typename T>
void BinarySearchTreeRecursion<T>::postOrder(const BinarySearchTreeRecursion::Node *node) const {
    if (!node)
        return;

    postOrderRecursion(node -> left);
    postOrderRecursion(node -> right);
    visit(node);
}

template<typename T>
T BinarySearchTreeRecursion<T>::minimum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

   return minimum(root);
}

template<typename T>
T BinarySearchTreeRecursion<T>::minimum(const BinarySearchTreeRecursion::Node *node) const {
    if (!node -> left)
        return node;

    return minimum(node -> left);
}

template<typename T>
T BinarySearchTreeRecursion<T>::maximum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    return maximum(root);
}

template<typename T>
T BinarySearchTreeRecursion<T>::maximum(const BinarySearchTreeRecursion::Node *node) const {
    if (!node -> right)
        return node;

    return maximum(node -> right);
}

template<typename T>
void BinarySearchTreeRecursion<T>::removeMin() {

}

template<typename T>
typename BinarySearchTreeRecursion<T>::Node *BinarySearchTreeRecursion<T>::removeMin(BinarySearchTreeRecursion::Node *node) {
    return nullptr;
}

template<typename T>
void BinarySearchTreeRecursion<T>::removeMax() {

}

template<typename T>
typename BinarySearchTreeRecursion<T>::Node *BinarySearchTreeRecursion<T>::removeMax(BinarySearchTreeRecursion::Node *node) {
    return nullptr;
}

template<typename T>
typename BinarySearchTreeRecursion<T>::Node *BinarySearchTreeRecursion<T>::add(Node *node, const T &e) {
    if (!node) {
        size++;
        return new Node(e);
    }

    if (e < node -> val)
        node -> left = add(node -> left, e);
    else if (e > node -> val)
        node -> right = add(node -> right, e);

    return node;
}

template<typename T>
void BinarySearchTreeRecursion<T>::remove(const T &e) {

}

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_RECURSION_H
