#ifndef ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MAP_H
#define ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MAP_H

#include "map.h"
#include "linked_list_map.h"
#include <iostream>

template <typename K, typename V> class LinkedListMap;

template <typename K, typename V>
std::ostream &operator<<(std::ostream &, const LinkedListMap<K, V> &);

template <typename K, typename V>
class LinkedListMap : public Map<K, V> {
    friend std::ostream &operator<<<K, V>(std::ostream &, const LinkedListMap<K, V> &);
public:
    LinkedListMap():
            dummyHead(new Node()), size(0) { };
    LinkedListMap(const LinkedListMap<K, V> &rhs);
    LinkedListMap<K, V> &operator=(const LinkedListMap<K, V> &rhs);

    int getSize() const override { return size; };
    bool isEmpty() const override { return size == 0; }
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
        Node *next;

        Node(K key, V value, Node *next):
                key(key), value(value), next(next) { }
        Node(K key, V value):
                Node(key, value, nullptr) { }
        Node():
                Node(K(), V(), nullptr) { }
    };
    Node *dummyHead;
    int size;
    void swap(LinkedListMap<K, V> &rhs);
    Node *getNode(const K &key) const;
};

template<typename K, typename V>
LinkedListMap<K, V>::LinkedListMap(const LinkedListMap<K, V> &rhs):
    dummyHead(new Node()),  size(rhs.size) {
    auto pre = dummyHead;
    auto rhsCur = rhs.dummyHead -> next;
    while (rhsCur) {
        pre -> next = new Node(rhsCur -> key, rhsCur -> value);
        pre = pre -> next;
        rhsCur = rhsCur -> next;
    }
}

template<typename K, typename V>
void LinkedListMap<K, V>::swap(LinkedListMap<K, V> &rhs) {
    using std::swap;
    swap(dummyHead, rhs.dummyHead);
    swap(size, rhs.size);
}

template<typename K, typename V>
LinkedListMap<K, V> &LinkedListMap<K, V>::operator=(const LinkedListMap<K, V> &rhs) {
    LinkedListMap<K, V>(rhs).swap(*this);
    return *this;
}

template<typename K, typename V>
typename LinkedListMap<K, V>::Node *LinkedListMap<K, V>::getNode(const K &key) const {
    auto cur = dummyHead -> next;
    while (cur) {
        if (cur -> key == key)
            return cur;
        cur = cur -> next;
    }
    return nullptr;
}

template<typename K, typename V>
bool LinkedListMap<K, V>::contains(const K &key) const {
    return getNode(key) != nullptr;
}

template<typename K, typename V>
V LinkedListMap<K, V>::get(const K &key) const {
    auto node = getNode(key);
    if (!node)
        throw std::runtime_error("键值不存在！");
    return node -> value;
}

template<typename K, typename V>
void LinkedListMap<K, V>::set(const K &key, const V &newValue) {
    auto node = getNode(key);
    if (node) {
        node -> value = newValue;
        return;
    }
    throw std::runtime_error("键值不存在！");
}

template<typename K, typename V>
void LinkedListMap<K, V>::add(const K &key, const V &value) {
    auto node = getNode(key);
    if (node)
        node -> value = value;
    else {
        dummyHead -> next = new Node(key, value, dummyHead -> next);
        size++;
    }
}

template<typename K, typename V>
void LinkedListMap<K, V>::remove(const K &key) {
    auto pre = dummyHead;
    while (pre -> next) {
        if (pre -> next -> key == key) {
            auto delNode = pre -> next;
            pre -> next = delNode -> next;
            delete delNode;
            size--;
            return;
        }
        pre = pre -> next;
    }
}

template<typename K, typename V>
std::ostream &operator<<(std::ostream &os, const LinkedListMap<K, V> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "Map的大小：" << size << "\n"
       << "Map的内容：\n";

    os << "{";
    auto cur = rhs.dummyHead -> next;
    while (cur) {
        if (cur -> next)
            os << "<" << cur -> key << ": " << cur -> value << ">, ";
        else
            os << "<" << cur -> key << ": " << cur -> value << ">";
        cur = cur -> next;
    }
    os << "}\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_LINKED_LIST_MAP_H
