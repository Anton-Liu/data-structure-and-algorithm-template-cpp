#ifndef ALGORITHM_TEMPLATE_CPP_AVL_TREE_H
#define ALGORITHM_TEMPLATE_CPP_AVL_TREE_H

#include <iostream>
#include <queue>
#include <cmath>
#include <functional>

template <typename T>
class AVLTree;

template <typename T>
std::ostream &operator<<(std::ostream &, const AVLTree<T> &);

template <typename T>
class AVLTree {
    friend std::ostream &operator<<<T>(std::ostream &, const AVLTree<T> &);
public:
    AVLTree():
            root(nullptr), size(0) { }
    AVLTree(const AVLTree<T> &rhs);
    AVLTree<T> &operator=(const AVLTree<T> &rhs);

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    bool contains(const T &e) const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void levelOrder() const;  // 非递归实现！
    T minimum() const;
    T maximum() const;
    bool isBST() const;  // 判断该二叉树是否是一棵二分搜索树
    bool isBalanced() const;  // 判断该二叉树是否是一棵平衡二叉树

    void add(const T &e) { root = add(root, e); }
    void removeMin();
    void removeMax();
    void remove(const T &e);
    void swap(AVLTree<T> &rhs);

    ~AVLTree();

private:
    class Node {
    public:
        T val;
        Node *left;
        Node *right;
        int height;  // 记录当前结点的高度

        explicit Node(T val):
                val(val), left(nullptr), right(nullptr), height(1) { }
        Node(T val, Node *left, Node *right, int height):
                val(val), left(left), right(right), height(height) { }
    };
    Node *root;
    int size;

    int getHeight(const Node *node) const;  // 获得结点node的高度
    int getBalanceFactor(const Node *node) const;  // 计算结点node的平衡因子
    void preOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void inOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void postOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void postOrder(Node *node, std::function<void(Node *)> visit);
    void levelOrder(const Node *node, std::function<void(const Node *)> visit) const;  // 非递归实现！
    bool contains(const Node *node, const T &e) const;
    bool isBalanced(const Node *node) const;  // 递归函数

    Node *minimum(Node *node) const;
    Node *maximum(Node *node) const;
    Node *add(Node *node, const T &e);
    Node *removeMin(Node *node);
    Node *removeMax(Node *node);
    Node *remove(Node *node, const T &e);
    Node *copyTree(const Node *rhsNode);

    // 对结点y进行向右旋转操作，返回旋转后新的根结点x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋转 (y)        z     y
    //     / \         --------->       / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    Node *rightRotate(Node *y);

    // 对结点y进行向左旋转操作，返回旋转后新的根结点x
    //    y                             x
    //  /  \                          /   \
    // T1   x      向左旋转 (y)       y     z
    //     / \     -------->       / \   / \
    //   T2  z                    T1 T2 T3 T4
    //      / \
    //     T3 T4
    Node *leftRotate(Node *y);
};

template<typename T>
void AVLTree<T>::swap(AVLTree<T> &rhs) {
    using std::swap;
    swap(root, rhs.root);
    swap(size, rhs.size);
}

template<typename T>
AVLTree<T>::~AVLTree() {
    postOrder(root, [](Node *node){ delete node; });  // 后序遍历删除整棵二叉树
}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &rhs) {
    size = 0;
    root = copyTree(rhs.root);
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::copyTree(const AVLTree::Node *rhsNode) {
    if (!rhsNode)
        return nullptr;

    auto newNode = new Node(rhsNode -> val);
    size++;
    newNode -> left = copyTree(rhsNode -> left);
    newNode -> right = copyTree(rhsNode -> right);

    return newNode;
}

template<typename T>
AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &rhs) {
    AVLTree<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
int AVLTree<T>::getHeight(const AVLTree::Node *node) const {
    if (!node)
        return 0;

    return node -> height;
}

template<typename T>
int AVLTree<T>::getBalanceFactor(const AVLTree::Node *node) const {
    if (!node)
        return 0;

    return getHeight(node -> left) - getHeight(node -> right);
}

template<typename T>
bool AVLTree<T>::isBST() const {
    std::vector<T> vec;
    inOrder(root, [&vec](const Node *node){ vec.push_back(node -> val); });
    for (int i = 1; i < vec.size(); i++)
        if (vec[i] < vec[i - 1])
            return false;
    return true;
}

template<typename T>
bool AVLTree<T>::isBalanced() const {
    return isBalanced(root);
}

template<typename T>
bool AVLTree<T>::isBalanced(const AVLTree::Node *node) const {
    if (!node)
        return true;

    auto bf = getBalanceFactor(node);
    if (std::abs(bf) > 1)
        return false;

    return isBalanced(node -> left) && isBalanced(node -> right);
}

template<typename T>
bool AVLTree<T>::contains(const T &e) const {
    return contains(root, e);
}

template<typename T>
bool AVLTree<T>::contains(const AVLTree:: Node *node, const T &e) const {
    if (!node)
        return false;
    if (e == node -> val)
        return true;

    if (e < node -> val)
        return contains(node -> left, e);
    // e > node -> val
    return contains(node -> right, e);
}

template<typename T>
void AVLTree<T>::preOrder() const {
    preOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void AVLTree<T>::preOrder(const AVLTree::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    visit(node);
    preOrder(node -> left, visit);
    preOrder(node -> right, visit);
}

template<typename T>
void AVLTree<T>::inOrder() const {
    inOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void AVLTree<T>::inOrder(const AVLTree::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    inOrder(node -> left, visit);
    visit(node);
    inOrder(node -> right, visit);
}

template<typename T>
void AVLTree<T>::postOrder() const {
    postOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void AVLTree<T>::postOrder(const AVLTree::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    postOrder(node -> left, visit);
    postOrder(node -> right, visit);
    visit(node);
}

template<typename T>
void AVLTree<T>::postOrder(AVLTree::Node *node, std::function<void(Node *)> visit) {
    if (!node)
        return;

    postOrder(node -> left, visit);
    postOrder(node -> right, visit);
    visit(node);
}

template<typename T>
void AVLTree<T>::levelOrder() const {
    levelOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void AVLTree<T>::levelOrder(const AVLTree::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    std::queue<Node *> que;
    que.push(node);
    while (!que.empty()) {
        auto cur = que.front();
        if (cur -> left)
            que.push(cur -> left);
        if (cur -> right)
            que.push(cur -> right);
        visit(cur);
        que.pop();
    }
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::rightRotate(Node *y) {
    auto x = y -> left;
    y -> left = x -> right;
    x -> right = y;

    // 更新height
    y -> height = 1 + std::max(getHeight(y -> left), getHeight(y -> right));
    x -> height = 1 + std::max(getHeight(x -> left), getHeight(x -> right));

    return x;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::leftRotate(Node *y) {
    auto x = y -> right;
    y -> right = x -> left;
    x -> left = y;

    // 更新height
    y -> height = 1 + std::max(getHeight(y -> left), getHeight(y -> right));
    x -> height = 1 + std::max(getHeight(x -> left), getHeight(x -> right));

    return x;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::add(Node *node, const T &e) {
    if (!node) {
        size++;
        return new Node(e);
    }

    if (e < node -> val)
        node -> left = add(node -> left, e);
    else if (e > node -> val)
        node -> right = add(node -> right, e);

    // 更新node的height值(重新计算即可)
    node -> height = 1 + std::max(getHeight(node -> left), getHeight(node -> right));

    // 计算平衡因子并进行平衡维护
    int bf = getBalanceFactor(node);
    // LL
    if (bf > 1 && getBalanceFactor(node -> left) > 0)
        return rightRotate(node);
    // RR
    if (bf < -1 && getBalanceFactor(node -> right) < 0)
        return leftRotate(node);
    // LR
    if (bf > 1 && getBalanceFactor(node -> left) < 0) {
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }
    // RL
    if (bf < -1 && getBalanceFactor(node -> right) > 0) {
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }

    return node;
}

template<typename T>
T AVLTree<T>::minimum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    return minimum(root) -> val;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::minimum(AVLTree::Node *node) const {
    if (!node -> left)
        return node;

    return minimum(node -> left);
}

template<typename T>
T AVLTree<T>::maximum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    return maximum(root) -> val;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::maximum(AVLTree::Node *node) const {
    if (!node -> right)
        return node;

    return maximum(node -> right);
}

template<typename T>
void AVLTree<T>::remove(const T &e) {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    root = remove(root, e);
}

template<typename T>
typename AVLTree<T>::Node *
AVLTree<T>::remove(AVLTree::Node *node, const T &e) {
    if (!node)
        return nullptr;

    Node *retNode;
    if (e < node -> val) {
        node -> left = remove(node -> left, e);
        retNode = node;
    }
    else if (e > node -> val) {
        node -> right = remove(node -> right, e);
        retNode = node;
    }
    else {  // e == node -> val
        if (!node -> left) {
            auto rightNode = node -> right;
            delete node;
            size--;
            retNode = rightNode;
        }
        else if (!node -> right) {
            auto leftNode = node -> left;
            delete node;
            size--;
            retNode = leftNode;
        }
        else {
            auto successor = new Node(minimum(node -> right) -> val);  // 后继结点
            successor -> left = node -> left;
            successor -> right = remove(node -> right, successor -> val);

            delete node;
            retNode = successor;
        }
    }

    if (!retNode)
        return nullptr;

    // 更新retNode的height值(重新计算即可)
    retNode -> height = 1 + std::max(getHeight(retNode -> left), getHeight(retNode -> right));

    // 计算平衡因子并进行平衡维护
    int bf = getBalanceFactor(retNode);
    // LL
    if (bf > 1 && getBalanceFactor(retNode -> left) > 0)
        return rightRotate(retNode);
    // RR
    if (bf < -1 && getBalanceFactor(retNode -> right) < 0)
        return leftRotate(retNode);
    // LR
    if (bf > 1 && getBalanceFactor(retNode -> left) < 0) {
        retNode -> left = leftRotate(retNode -> left);
        return rightRotate(retNode);
    }
    // RL
    if (bf < -1 && getBalanceFactor(retNode -> right) > 0) {
        retNode->right = rightRotate(retNode->right);
        return leftRotate(retNode);
    }

    return retNode;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const AVLTree<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "AVL树的长度：" << size << "\n"
       << "AVL树的内容(层序遍历)：\n";

    if (rhs.root == nullptr)
        os << "NULL\n";
    else {
        std::queue<std::pair<typename AVLTree<T>::Node *, int>> que;
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

#endif //ALGORITHM_TEMPLATE_CPP_AVL_TREE_H
