#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree():
            root(nullptr), size(0) { }
    BinarySearchTree(const BinarySearchTree<T> &rhs);
    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &rhs);

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    bool contains(const T &e) const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void levelOrder() const;  // 非递归实现！
    T minimum() const;
    T maximum() const;

    void add(const T &e) { root = add(root, e); }
    void removeMin();
    void removeMax();
    void remove(const T &e);
    void swap(BinarySearchTree<T> &rhs);

    ~BinarySearchTree();

private:
    class Node {
    public:
        T val;
        Node *left;
        Node *right;

        explicit Node(T val):
                val(val), left(nullptr), right(nullptr) { }
        Node(T val, Node *left, Node *right):
                val(val), left(left), right(right) { }
    };
    Node *root;
    int size;
};

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    if (!root)
        return;

    std::queue<Node *> que;
    que.push(root);
    while (!que.empty()) {
        auto cur = que.front();
        que.pop();

        if (cur -> left)
            que.push(cur -> left);
        if (cur -> right)
            que.push(cur -> right);

        delete cur;
    }
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &rhs) {

}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &rhs) {
    
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &e) const {
    return false;
}

template<typename T>
void BinarySearchTree<T>::preOrder() const {

}

template<typename T>
void BinarySearchTree<T>::inOrder() const {

}

template<typename T>
void BinarySearchTree<T>::postOrder() const {

}

template<typename T>
void BinarySearchTree<T>::levelOrder() const {

}

template<typename T>
T BinarySearchTree<T>::minimum() const {
    return nullptr;
}

template<typename T>
T BinarySearchTree<T>::maximum() const {
    return nullptr;
}

template<typename T>
void BinarySearchTree<T>::removeMin() {

}

template<typename T>
void BinarySearchTree<T>::removeMax() {

}

template<typename T>
void BinarySearchTree<T>::remove(const T &e) {

}

template<typename T>
void BinarySearchTree<T>::swap(BinarySearchTree<T> &rhs) {

}

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H
