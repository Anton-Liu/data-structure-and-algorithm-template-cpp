#ifndef ALGORITHM_TEMPLATE_CPP_SEGMENT_TREE_H
#define ALGORITHM_TEMPLATE_CPP_SEGMENT_TREE_H

#include <vector>
#include <iostream>
#include <functional>

template <typename T> class SegmentTree;

template <typename T>
std::ostream &operator<<(std::ostream &, const SegmentTree<T> &);

template <typename T>
class SegmentTree {
    friend std::ostream &operator<<<T>(std::ostream &os, const SegmentTree<T> &rhs);
public:
    SegmentTree(const std::vector<T> &arr, std::function<T(const T&, const T&)> merger):
            data(new std::vector<T>(arr)),
            tree(new std::vector<T>(arr.size() * 4)),
            flag(new std::vector<bool>(arr.size() * 4)),
            merger(merger) { buildSegmentTree(0, 0, data -> size() - 1);}  // 4n确保能存放整个线段树
    SegmentTree(const SegmentTree<T> &rhs):
            data(new std::vector<T>(rhs.data)),
            tree(new std::vector<T>(rhs.tree)),
            flag(new std::vector<bool>(rhs.flag)),
            merger(rhs.merger) { }

    SegmentTree<T> &operator=(const SegmentTree<T> &rhs);
    int getSize() const { return data -> size(); }
    int get(int idx) const;

    // 返回区间[queryL, queryR]的合并值
    T query(int queryL, int queryR) const;  // O(logn)

    void set(int idx, const T &e);  // 将idx位置的值更新为e，O(logn)

    void swap(SegmentTree<T> &rhs);

    ~SegmentTree() { delete data; delete tree; delete flag; }
private:
    std::vector<T> *data;
    std::vector<T> *tree;
    std::vector<bool> *flag;  // 标记tree数组中对应结点是否存在
    std::function<T(const T&, const T&)> merger;  // 合并方式

    // treeIndex是线段树中表示区间[l..r]的结点的位置
    int leftChild(int treeIndex) const { return treeIndex * 2 + 1; }
    int rightChild(int treeIndex) const { return treeIndex * 2 + 2; }
    T query(int treeIndex, int l, int r, int queryL, int queryR) const;
    void buildSegmentTree(int treeIndex, int l, int r);
    void set(int treeIndex, int l, int r, int idx, const T &e);
};

template<typename T>
int SegmentTree<T>::get(int idx) const {
    if (idx < 0 || idx >= data -> size())
        throw std::runtime_error("数组下标超过范围！");
    if (!(*flag)[idx])
        throw std::runtime_error("访问结点不存在！");

    return (*data)[idx];
}

template<typename T>
void SegmentTree<T>::set(int idx, const T &e) {
    if (idx < 0 || idx >= data -> size())
        throw std::runtime_error("数组下标超过范围！");

    (*data)[idx] = e;
    set(0, 0, data -> size() - 1, idx, e);
}

template<typename T>
void SegmentTree<T>::set(int treeIndex, int l, int r, int idx, const T &e) {
    if (l == r) {
        (*tree)[treeIndex] = e;
        return;
    }

    int mid = l + (r - l) / 2;
    int leftChildIndex = leftChild(treeIndex);
    int rightChildIndex = rightChild(treeIndex);
    if (idx >= mid + 1)
        set(rightChildIndex, mid + 1, r, idx, e);
    else  // idx <= mid
        set(leftChildIndex, l, mid, idx, e);
    (*tree)[treeIndex] = merger((*tree)[leftChildIndex], (*tree)[rightChildIndex]);
}

template<typename T>
void SegmentTree<T>::swap(SegmentTree<T> &rhs) {
    using std::swap;
    swap(data, rhs.data);
    swap(tree, rhs.tree);
    swap(flag, rhs.flag);
    swap(merger, rhs.merger);
}

template<typename T>
SegmentTree<T> &SegmentTree<T>::operator=(const SegmentTree<T> &rhs) {
    SegmentTree<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
void SegmentTree<T>::buildSegmentTree(int treeIndex, int l, int r) {
    if (l == r) {
        (*tree)[treeIndex] = (*data)[l];
        (*flag)[treeIndex] = true;
        return;
    }

    int leftChildIndex = leftChild(treeIndex);
    int rightChildIndex = rightChild(treeIndex);

    int mid = l + (r - l) / 2;
    buildSegmentTree(leftChildIndex, l, mid);
    buildSegmentTree(rightChildIndex, mid + 1, r);
    (*tree)[treeIndex] = merger((*tree)[leftChildIndex], (*tree)[rightChildIndex]);
    (*flag)[treeIndex] = true;
}

template<typename T>
T SegmentTree<T>::query(int queryL, int queryR) const {
    return query(0, 0, data -> size() - 1, queryL, queryR);
}

template<typename T>
T SegmentTree<T>::query(int treeIndex, int l, int r, int queryL, int queryR) const {
    if (l == queryL && r == queryR)
        return (*tree)[treeIndex];

    int leftChildIndex = leftChild(treeIndex);
    int rightChildIndex = rightChild(treeIndex);
    int mid = l + (r - l) / 2;
    if (queryL > mid)
        return query(rightChildIndex, mid + 1, r, queryL, queryR);
    if (queryR <= mid)
        return query(leftChildIndex, l, mid, queryL, queryR);

    // [queryL, queryR]在区间[l, mid]和[mid + 1, r]中都有部分包含
    T leftResult = query(leftChildIndex, l, mid, queryL, mid);
    T rightResult = query(rightChildIndex, mid + 1, r, mid + 1, queryR);
    return merger(leftResult, rightResult);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const SegmentTree<T> &rhs) {
    int size = rhs.tree -> size();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "数组长度：" << rhs.getSize() << "\n"
       << "线段树内容(数组表示)：SegmentTree[";

    for (int i = 0; i < size; i++) {
        if ((*rhs.flag)[i])
            os << (*rhs.tree)[i];
        else
            os << "null";
        if (i != size - 1)
            os << ", ";
    }
    os << "]\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_SEGMENT_TREE_H
