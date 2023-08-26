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
    T minimum() const;
    T maximum() const;

    void add(const T &e) { root = addRecursion(root, e); }
    void removeMin();
    void removeMax();
    void remove(const T &e);

    ~BinarySearchTree();

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

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H
