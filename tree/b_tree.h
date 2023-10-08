#ifndef ALGORITHM_TEMPLATE_CPP_B_TREE_H
#define ALGORITHM_TEMPLATE_CPP_B_TREE_H

#include <vector>
#include <functional>
#include <iostream>

/**
 * 未实现
 * m阶B树是一棵空树，或者满足以下性质的树：
 *      1 每个结点最多有m棵子树(最多有m-1个关键字)
 *      2 非终端结点的根结点最少有2棵子树(最少有1个关键字)
 *      3 每个中间结点最少有⌈m/2⌉棵子树(最少有⌈m/2⌉-1个关键字)
 *      4 所有叶子结点都在同一层，并且不带任何信息(空结点)
 *      5 所有非页结点的结构：
 *          P0 | K1 | P1 | K2 | P2 | ... | Kn | Pn
 *          n为结点中关键字的个数
 *          Ki(i = 1, 2, ..., n)表示结点的关键字，且满足K1 < K2 < ... < Kn
 *          Pj(j = 0, 1, ..., n)表示指向子树根结点的指针，且指针Pj所指子树中所有结点的关键字均小于K(j+1)
 */

template <typename T>
class BTree {
    BTree(int m):
            root(nullptr), m(m) { }

    void traverse() const;  // 遍历整个B树
    bool contains(const T &key);  // 查询B树中是否包含某个关键字，O(logn)
    void add(const T &key);  // 向B树中插入关键字，O(logn)

private:
    class Node {
    public:
        std::vector<T> *keys;  // 存放关键字的数组
        std::vector<Node *> *children;  // 存放孩子结点的指针数组

        Node():
            keys(new std::vector<T>()), children(new std::vector<Node *>()) { }

        ~Node() { delete keys; delete children; }
    };

    Node *root;  // 根结点指针
    int m;  // B树的阶数

    void traverseRecursion(const Node *node, std::function<void(const Node *)> visit) const;  // 遍历整个B树(递归函数)
    bool containsRecursion(const Node *node, const T &key) const;  // 查询以node为根的子树中是否包含某个关键字(递归函数)

    ~BTree() { delete root; }
};

template<typename T>
void BTree<T>::traverse() const {
    if (!root)
        return;

    traverseRecursion(root, [](const Node *node){ std::cout << "当前访问结点：" << node -> val << std::endl; });
}

template<typename T>
void BTree<T>::traverseRecursion(const Node *node, std::function<void(const Node *)> visit) const {
    // 类似于二叉树的中序遍历
    if (!node)
        return;

    auto n = node -> keys -> size();  // 结点的关键字个数
    for (int i = 0; i < n; i++) {
        traverse((*node -> children)[i]);
        visit(node);
    }
}

template<typename T>
bool BTree<T>::contains(const T &key) {
    if (!root)
        throw std::runtime_error("当前B树为空！");

    return containsRecursion(root, key);
}

template<typename T>
bool BTree<T>::containsRecursion(const BTree::Node *node, const T &key) const {
    if (!node)
        return false;

    auto n = node -> keys -> size();

    // 找到node中第一个大于等于key的关键字索引i
    int i = 0;
    while (i < n && key > (*node -> keys)[i])
        i++;

    // i指向等于key的关键字，返回true
    if (i < n && key == (*node -> keys)[i])
        return true;

    // i指向第一个大于key的关键字，或最后一个关键字之后的位置
    // 继续往关键字左侧的子树找
    return containsRecursion((*node -> children)[i], key);
}

template<typename T>
void BTree<T>::add(const T &key) {
    if (!root) {
        root = new Node();
        root -> keys -> push_back(key);
        return;
    }

    // 若根结点已满，则要分裂结点
    if (root -> keys -> size() == m - 1) {

    }
}

#endif //ALGORITHM_TEMPLATE_CPP_B_TREE_H
