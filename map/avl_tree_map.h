#ifndef ALGORITHM_TEMPLATE_CPP_AVL_TREE_MAP_H
#define ALGORITHM_TEMPLATE_CPP_AVL_TREE_MAP_H

#include "map.h"
#include <iostream>
#include <queue>

template <typename K, typename V> class AVLTreeMap;

template <typename K, typename V>
std::ostream &operator<<(std::ostream &, const AVLTreeMap<K, V> &);

template <typename K, typename V>
class AVLTreeMap : public Map<K, V> {
    friend std::ostream &operator<<<K, V>(std::ostream &, const AVLTreeMap<K, V> &);
public:
    AVLTreeMap():
            root(nullptr), size(0) { }
    AVLTreeMap(const AVLTreeMap<K, V> &rhs);
    AVLTreeMap<K, V> &operator=(const AVLTreeMap<K, V> &rhs);

    int getSize() const override { return size; };
    bool isEmpty() const override { return size == 0; };
    bool contains(const K &key) const override;
    V get(const K &key) const override;

    void set(const K &key, const V &newValue) override;
    void add(const K &key, const V &value) override { root = add(root, key, value); }
    void remove(const K &key) override;

private:
    class Node {
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        int height;  // 记录当前结点的高度

        Node(K key, V value):
                key(key), value(value), left(nullptr), right(nullptr), height(1) { }
        Node(K key, V value, Node *left, Node *right, int height):
                key(key), value(value), left(left), right(right), height(height) { }
    };
    Node *root;
    int size;

    int getHeight(const Node *node) const;  // 获得结点node的高度
    int getBalanceFactor(const Node *node) const;  // 计算结点node的平衡因子
    Node *get(Node *node, const K &key) const;
    Node *add(Node *node, const K &key, const V &value);
    Node *copyTree(const Node *rhsNode);
    void swap(const AVLTreeMap<K, V> &rhs);
    Node *minimum(Node *node);
    Node *removeMin(Node *node);
    Node *remove(Node *node, const K &key);

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

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::copyTree(const AVLTreeMap::Node *rhsNode) {
    if (!rhsNode)
        return nullptr;

    auto newNode = new Node(rhsNode -> key, rhsNode -> value);
    size++;
    newNode -> left = copyTree(rhsNode -> left);
    newNode -> right = copyTree(rhsNode -> right);

    return newNode;
}

template<typename K, typename V>
AVLTreeMap<K, V>::AVLTreeMap(const AVLTreeMap<K, V> &rhs) {
    size = 0;
    root = copyTree(rhs.root);
}

template<typename K, typename V>
void AVLTreeMap<K, V>::swap(const AVLTreeMap<K, V> &rhs) {
    using std::swap;
    swap(root, rhs.root);
    swap(size, rhs.size);
}

template<typename K, typename V>
AVLTreeMap<K, V> &AVLTreeMap<K, V>::operator=(const AVLTreeMap<K, V> &rhs) {
    AVLTreeMap<K, V>(rhs).swap(*this);
    return *this;
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::get(AVLTreeMap::Node *node, const K &key) const {
    if (!node)
        return nullptr;

    if (key < node -> key)
        return get(node -> left, key);
    if (key > node -> key)
        return get(node -> right, key);

    return node;
}

template<typename K, typename V>
V AVLTreeMap<K, V>::get(const K &key) const {
    auto node = get(root, key);
    if (!node)
        throw std::runtime_error("键值不存在！");
    return node -> value;
}

template<typename K, typename V>
bool AVLTreeMap<K, V>::contains(const K &key) const {
    return get(root, key) != nullptr;
}

template<typename K, typename V>
void AVLTreeMap<K, V>::set(const K &key, const V &newValue) {
    auto node = get(root, key);
    if (!node)
        throw std::runtime_error("键值不存在！");
    node -> value = newValue;
}

template<typename K, typename V>
int AVLTreeMap<K, V>::getHeight(const AVLTreeMap::Node *node) const {
    if (!node)
        return 0;

    return node -> height;
}

template<typename K, typename V>
int AVLTreeMap<K, V>::getBalanceFactor(const AVLTreeMap::Node *node) const {
    if (!node)
        return 0;

    return getHeight(node -> left) - getHeight(node -> right);
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::rightRotate(AVLTreeMap::Node *y) {
    auto x = y -> left;
    y -> left = x -> right;
    x -> right = y;

    // 更新height
    y -> height = 1 + std::max(getHeight(y -> left), getHeight(y -> right));
    x -> height = 1 + std::max(getHeight(x -> left), getHeight(x -> right));

    return x;
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::leftRotate(AVLTreeMap::Node *y) {
    auto x = y -> right;
    y -> right = x -> left;
    x -> left = y;

    // 更新height
    y -> height = 1 + std::max(getHeight(y -> left), getHeight(y -> right));
    x -> height = 1 + std::max(getHeight(x -> left), getHeight(x -> right));

    return x;
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::add(AVLTreeMap::Node *node, const K &key, const V &value) {
    if (!node) {
        size++;
        return new Node(key, value);
    }

    if (key < node -> key)
        node -> left = add(node -> left, key, value);
    else if (key > node -> key)
        node -> right = add(node -> right, key, value);
    else
        node -> value = value;

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

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::minimum(AVLTreeMap::Node *node) {
    if (!node -> left)
        return node;

    return minimum(node -> left);
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::removeMin(AVLTreeMap::Node *node) {
    if (!node -> left) {
        auto rightNode = node -> right;
        delete node;
        size--;
        return rightNode;
    }

    node -> left = removeMin(node -> left);
    return node;
}

template<typename K, typename V>
typename AVLTreeMap<K, V>::Node *AVLTreeMap<K, V>::remove(AVLTreeMap::Node *node, const K &key) {
    if (!node)
        return nullptr;

    Node *retNode;
    if (key < node -> key) {
        node -> left = remove(node -> left, key);
        retNode = node;
    }
    else if (key > node -> key) {
        node -> right = remove(node -> right, key);
        retNode = node;
    }
    else {  // e == node -> key
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
            auto rightMinNode = minimum(node -> right);
            auto successor = new Node(rightMinNode -> key, rightMinNode -> value);  // 后继结点
            successor -> left = node -> left;
            successor -> right = remove(node -> right, successor -> key);

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

template<typename K, typename V>
void AVLTreeMap<K, V>::remove(const K &key) {
    root = remove(root, key);
}

template<typename K, typename V>
std::ostream &operator<<(std::ostream &os, const AVLTreeMap<K, V> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "Map的长度：" << size << "\n"
       << "Map的内容：\n";

    os << "{";

    auto tmp(rhs);
    std::queue<typename AVLTreeMap<K, V>::Node *> que;

    if (tmp.root)
        que.push(tmp.root);
    while (tmp.size > 1) {
        auto cur = que.front();
        que.pop();
        tmp.size--;
        os << "<" << cur -> key << ": " << cur -> value << ">, ";
        if (cur -> left)
            que.push(cur -> left);
        if (cur -> right)
            que.push(cur -> right);
    }
    if (!que.empty())
        os << "<" << que.front() -> key << ": " << que.front() -> value << ">";
    os << "}\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_AVL_TREE_MAP_H
