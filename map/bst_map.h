#ifndef ALGORITHM_TEMPLATE_CPP_BST_MAP_H
#define ALGORITHM_TEMPLATE_CPP_BST_MAP_H

#include "map.h"
#include <iostream>
#include <queue>

template <typename K, typename V> class BSTMap;

template <typename K, typename V>
std::ostream &operator<<(std::ostream &, const BSTMap<K, V> &);

template <typename K, typename V>
class BSTMap : public Map<K, V> {
    friend std::ostream &operator<<<K, V>(std::ostream &, const BSTMap<K, V> &);
public:
    BSTMap():
            root(nullptr), size(0) { }
    BSTMap(const BSTMap<K, V> &rhs);
    BSTMap<K, V> &operator=(const BSTMap<K, V> &rhs);

    int getSize() const override { return size; };
    bool isEmpty() const override { return size == 0; };
    bool contains(const K &key) const override;
    V get(const K &key) const override;

    void set(const K &key, const V &newValue) override;
    void add(const K &key, const V &value) override;
    void remove(const K &key) override;

private:
    class Node {
    public:
        K key;
        V value;
        Node *left;
        Node *right;

        Node(K key, V value):
            key(key), value(value), left(nullptr), right(nullptr) { }
        Node(K key, V value, Node *left, Node *right):
            key(key), value(value), left(left), right(right) { }
    };
    Node *root;
    int size;

    Node *get(Node *node, const K &key) const;
    Node *add(Node *node, const K &key, const V &value);
    Node *copyTree(const Node *rhsNode);
    void swap(const BSTMap<K, V> &rhs);
    Node *minimum(Node *node);
    Node *removeMin(Node *node);
    Node *remove(Node *node, const K &key);
};

template<typename K, typename V>
typename BSTMap<K, V>::Node *BSTMap<K, V>::copyTree(const BSTMap::Node *rhsNode) {
    if (!rhsNode)
        return nullptr;

    auto newNode = new Node(rhsNode -> key, rhsNode -> value);
    size++;
    newNode -> left = copyTree(rhsNode -> left);
    newNode -> right = copyTree(rhsNode -> right);

    return newNode;
}

template<typename K, typename V>
BSTMap<K, V>::BSTMap(const BSTMap<K, V> &rhs) {
    size = 0;
    root = copyTree(rhs.root);
}

template<typename K, typename V>
void BSTMap<K, V>::swap(const BSTMap<K, V> &rhs) {
    using std::swap;
    swap(root, rhs.root);
    swap(size, rhs.size);
}

template<typename K, typename V>
BSTMap<K, V> &BSTMap<K, V>::operator=(const BSTMap<K, V> &rhs) {
    BSTMap<K, V>(rhs).swap(*this);
    return *this;
}

template<typename K, typename V>
typename BSTMap<K, V>::Node *BSTMap<K, V>::get(BSTMap::Node *node, const K &key) const {
    if (!node)
        return nullptr;

    if (key < node -> key)
        return get(node -> left, key);
    if (key > node -> key)
        return get(node -> right, key);

    return node;
}

template<typename K, typename V>
V BSTMap<K, V>::get(const K &key) const {
    auto node = get(root, key);
    if (!node)
        throw std::runtime_error("键值不存在！");
    return node -> value;
}

template<typename K, typename V>
bool BSTMap<K, V>::contains(const K &key) const {
    return get(root, key) != nullptr;
}

template<typename K, typename V>
void BSTMap<K, V>::set(const K &key, const V &newValue) {
    auto node = get(root, key);
    if (!node)
        throw std::runtime_error("键值不存在！");
    node -> value = newValue;
}

template<typename K, typename V>
void BSTMap<K, V>::add(const K &key, const V &value) {
    root = add(root, key, value);
}

template<typename K, typename V>
typename BSTMap<K, V>::Node *BSTMap<K, V>::add(BSTMap::Node *node, const K &key, const V &value) {
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

    return node;
}

template<typename K, typename V>
typename BSTMap<K, V>::Node *BSTMap<K, V>::minimum(BSTMap::Node *node) {
    if (!node -> left)
        return node;

    return minimum(node -> left);
}

template<typename K, typename V>
typename BSTMap<K, V>::Node *BSTMap<K, V>::removeMin(BSTMap::Node *node) {
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
typename BSTMap<K, V>::Node *BSTMap<K, V>::remove(BSTMap::Node *node, const K &key) {
    if (!node)
        return nullptr;
    if (key < node -> key) {
        node -> left = remove(node -> left, key);
        return node;
    }
    if (key > node -> key) {
        node -> right = remove(node -> right, key);
        return node;
    }

    // key == node -> key
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

    // node -> left != nullptr && node -> right != nullptr
    auto rightMinNode = minimum(node -> right);
    auto successor = new Node(rightMinNode -> key, rightMinNode -> value);
    successor -> left = node -> left;
    successor -> right = removeMin(node -> right);
    delete node;
    return successor;
}

template<typename K, typename V>
void BSTMap<K, V>::remove(const K &key) {
    root = remove(root, key);
}

template<typename K, typename V>
std::ostream &operator<<(std::ostream &os, const BSTMap<K, V> &rhs) {
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
    std::queue<typename BSTMap<K, V>::Node *> que;

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


#endif //ALGORITHM_TEMPLATE_CPP_BST_MAP_H
