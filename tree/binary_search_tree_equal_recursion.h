#ifndef ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_EQUAL_RECURSION_H
#define ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_EQUAL_RECURSION_H

#include <iostream>
#include <queue>
#include <functional>

template <typename T>
class BinarySearchTreeEqualRecursion;

template <typename T>
std::ostream &operator<<(std::ostream &, const BinarySearchTreeEqualRecursion<T> &);

template <typename T>
class BinarySearchTreeEqualRecursion {
    friend std::ostream &operator<<<T>(std::ostream &, const BinarySearchTreeEqualRecursion<T> &);
public:
    BinarySearchTreeEqualRecursion():
            root(nullptr), size(0) { }
    BinarySearchTreeEqualRecursion(const BinarySearchTreeEqualRecursion<T> &rhs);
    BinarySearchTreeEqualRecursion<T> &operator=(const BinarySearchTreeEqualRecursion<T> &rhs);

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
    void removeOneMin();
    void removeOneMax();
    void removeOne(const T &e);
    void removeAllMin();
    void removeAllMax();
    void removeAll(const T &e);
    void swap(BinarySearchTreeEqualRecursion<T> &rhs);

    ~BinarySearchTreeEqualRecursion();

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

    void preOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void inOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void postOrder(const Node *node, std::function<void(const Node *)> visit) const;
    void postOrder(Node *node, std::function<void(Node *)> visit);
    void levelOrder(const Node *node, std::function<void(const Node *)> visit) const;  // 非递归实现！
    bool contains(const Node *node, const T &e) const;

    Node *minimum(Node *node) const;
    Node *maximum(Node *node) const;
    Node *add(Node *node, const T &e);
    Node *removeMin(Node *node);
    Node *removeMax(Node *node);
    Node *remove(Node *node, const T &e);
    Node *copyTree(const Node *rhsNode);
};

template<typename T>
void BinarySearchTreeEqualRecursion<T>::swap(BinarySearchTreeEqualRecursion<T> &rhs) {
    using std::swap;
    swap(root, rhs.root);
    swap(size, rhs.size);
}

template<typename T>
BinarySearchTreeEqualRecursion<T>::~BinarySearchTreeEqualRecursion() {
    postOrder(root, [](Node *node){ delete node; });  // 后序遍历删除整棵二叉树
}

template<typename T>
BinarySearchTreeEqualRecursion<T>::BinarySearchTreeEqualRecursion(const BinarySearchTreeEqualRecursion<T> &rhs) {
    size = 0;
    root = copyTree(rhs.root);
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::copyTree(const BinarySearchTreeEqualRecursion::Node *rhsNode) {
    if (!rhsNode)
        return nullptr;

    auto newNode = new Node(rhsNode -> val);
    size++;
    newNode -> left = copyTree(rhsNode -> left);
    newNode -> right = copyTree(rhsNode -> right);

    return newNode;
}

template<typename T>
BinarySearchTreeEqualRecursion<T> &BinarySearchTreeEqualRecursion<T>::operator=(const BinarySearchTreeEqualRecursion<T> &rhs) {
    BinarySearchTreeEqualRecursion<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
bool BinarySearchTreeEqualRecursion<T>::contains(const T &e) const {
    return contains(root, e);
}

template<typename T>
bool BinarySearchTreeEqualRecursion<T>::contains(const BinarySearchTreeEqualRecursion:: Node *node, const T &e) const {
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
void BinarySearchTreeEqualRecursion<T>::preOrder() const {
    preOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::preOrder(const BinarySearchTreeEqualRecursion::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    visit(node);
    preOrder(node -> left, visit);
    preOrder(node -> right, visit);
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::inOrder() const {
    inOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::inOrder(const BinarySearchTreeEqualRecursion::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    inOrder(node -> left, visit);
    visit(node);
    inOrder(node -> right, visit);
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::postOrder() const {
    postOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::postOrder(const BinarySearchTreeEqualRecursion::Node *node, std::function<void(const Node *)> visit) const {
    if (!node)
        return;

    postOrder(node -> left, visit);
    postOrder(node -> right, visit);
    visit(node);
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::postOrder(BinarySearchTreeEqualRecursion::Node *node, std::function<void(Node *)> visit) {
    if (!node)
        return;

    postOrder(node -> left, visit);
    postOrder(node -> right, visit);
    visit(node);
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::levelOrder() const {
    levelOrder(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::levelOrder(const BinarySearchTreeEqualRecursion::Node *node,
                                                   std::function<void(const Node *)> visit) const {
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
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::add(Node *node, const T &e) {
    if (!node) {
        size++;
        return new Node(e);
    }

    if (e <= node -> val)
        node -> left = add(node -> left, e);
    else  // e > node -> val
        node -> right = add(node -> right, e);

    return node;
}

template<typename T>
T BinarySearchTreeEqualRecursion<T>::minimum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    return minimum(root) -> val;
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::minimum(BinarySearchTreeEqualRecursion::Node *node) const {
    if (!node -> left)
        return node;

    return minimum(node -> left);
}

template<typename T>
T BinarySearchTreeEqualRecursion<T>::maximum() const {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    return maximum(root) -> val;
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::maximum(BinarySearchTreeEqualRecursion::Node *node) const {
    if (!node -> right)
        return node;

    return maximum(node -> right);
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeOneMin() {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    root = removeMin(root);
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::removeMin(BinarySearchTreeEqualRecursion::Node *node) {
    if (!node -> left) {
        auto rightNode = node -> right;
        delete node;
        size--;
        return rightNode;
    }

    node -> left = removeMin(node -> left);
    return node;
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeOneMax() {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    root = removeMax(root);
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *BinarySearchTreeEqualRecursion<T>::removeMax(BinarySearchTreeEqualRecursion::Node *node) {
    if (!node -> right) {
        auto leftNode = node -> left;
        delete node;
        size--;
        return leftNode;
    }

    node -> right = removeMax(node -> right);
    return node;
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeOne(const T &e) {
    root = remove(root, e);
}

template<typename T>
typename BinarySearchTreeEqualRecursion<T>::Node *
BinarySearchTreeEqualRecursion<T>::remove(BinarySearchTreeEqualRecursion::Node *node, const T &e) {
    if (!node)
        return nullptr;

    if (e < node -> val) {
        node -> left = remove(node -> left, e);
        return node;
    }
    if (e > node -> val) {
        node -> right = remove(node -> right, e);
        return node;
    }

    // e == node -> val
    if (!node -> left) {
        auto rightNode = node -> right;
        delete node;
        size--;
        return rightNode;
    }
    if (!node -> right) {
        auto leftNode = node -> left;
        delete node;
        size--;
        return leftNode;
    }

    auto successor = new Node(minimum(node -> right) -> val);  // 后继结点
    successor -> left = node -> left;
    successor -> right = removeMin(node -> right);  // removeMin已经size--

    delete node;
    return successor;
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeAllMin() {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    auto minVal = minimum();  // 记录要删除的最小值
    auto nowMin = minVal;  // 记录当前树中的最小值
    while (minVal == nowMin) {  // 若当前树中最小值和要删除的最小值相同，则删除
        root = removeMin(root);
        if (size == 0)
            break;
        nowMin = minimum();
    }
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeAllMax() {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    root = removeMax(root);

    auto maxVal = maximum();  // 记录要删除的最大值
    auto nowMax = maxVal;  // 记录当前树中的最大值
    while (maxVal == nowMax) {  // 若当前树中最大值和要删除的最大值相同，则删除
        root = removeMax(root);
        if (size == 0)
            break;
        nowMax = maximum();
    }
}

template<typename T>
void BinarySearchTreeEqualRecursion<T>::removeAll(const T &e) {
    if (size == 0)
        throw std::runtime_error("当前二分搜索树为空！");

    auto curSize = size;
    root = remove(root, e);
    while (curSize != size) {
        curSize = size;
        root = remove(root, e);  // 若成功删除，size--，导致curSize继续不等于size
                                 // 否则，size无变化，curSize == size，跳出循环
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTreeEqualRecursion<T> &rhs) {
    auto size = rhs.getSize();

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
        std::queue<std::pair<typename BinarySearchTreeEqualRecursion<T>::Node *, int>> que;
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

#endif //ALGORITHM_TEMPLATE_CPP_BINARY_SEARCH_TREE_EQUAL_RECURSION_H
