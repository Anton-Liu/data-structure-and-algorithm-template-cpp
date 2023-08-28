#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>

template <typename T>
class BinarySearchTree;

template <typename T>
std::ostream &operator<<(std::ostream &, const BinarySearchTree<T> &);

template <typename T>
class BinarySearchTree {
    friend std::ostream &operator<<<T>(std::ostream &os, const BinarySearchTree<T> &rhs);
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

    void add(const T &e);
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

        Node():
                val(T()), left(nullptr), right(nullptr){}
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
    if (!rhs.root) {
        root = nullptr;
        size = 0;
        return;
    }

    size = rhs.size;
    std::queue<Node *> queL, queR;
    root = new Node();
    queL.push(root);
    queR.push(rhs.root);
    while (!queR.empty()) {
        auto curR = queR.front();
        queR.pop();
        auto curL = queL.front();
        queL.pop();
        curL -> val = curR -> val;
        if (curR -> left) {
            queR.push(curR -> left);
            curL -> left = new Node();
            queL.push(curL -> left);
        }
        if (curR -> right) {
            queR.push(curR -> right);
            curL -> right = new Node();
            queL.push(curL -> right);
        }
    }
}

template<typename T>
void BinarySearchTree<T>::swap(BinarySearchTree<T> &rhs) {
    using std::swap;
    swap(root, rhs.root);
    swap(size, rhs.size);
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &rhs) {
    BinarySearchTree<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &e) const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    auto cur = root;
    while (cur) {
        if (e == cur -> val)
            return true;
        if (e < cur -> val)
            cur = cur -> left;
        else // e > cur -> val
            cur = cur -> right;
    }
    return false;
}

template<typename T>
void BinarySearchTree<T>::add(const T &e) {
    if (size == 0) {
        root = new Node(e);
        size++;
        return;
    }

    auto cur = root;
    while (true) {
        if (e < cur -> val) {
            if (!cur -> left) {
                cur -> left = new Node(e);
                size++;
                return;
            }
            cur = cur -> left;
        }
        else if (e > cur -> val) {
            if (!cur -> right) {
                cur -> right = new Node(e);
                size++;
                return;
            }
            cur = cur -> right;
        }
        else
            return;  // e == cur -> val
    }
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
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "BST的长度：" << size << "\n"
       << "BST的内容(层序遍历)：\n";

    if (rhs.root == nullptr)
        os << "NULL\n";
    else {
        std::queue<std::pair<typename BinarySearchTree<T>::Node *, int>> que;
        que.push({rhs.root, 0});
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            for (int i = 0; i < cur.second; i++)
                os << "-";
            os << cur.first -> val << "\n";
            if (cur.first -> left)
                que.push({cur.first -> left, cur.second + 1});
            if (cur.first -> right)
                que.push({cur.first -> right, cur.second + 1});
        }
    }

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}


#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_H
