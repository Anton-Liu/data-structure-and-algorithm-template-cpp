#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 基本并查集Quick Union
 * 特点：
 *      没有任何优化
 *      合并性能相比Quick Find有提升
 *      合并生成的树可能退化为链表
 * 各操作时间复杂度：
 *      isConnected: O(h)
 *      find: O(h)
 *      unionElements: O(h)
 *      h是树的高度
 */

class UnionFindQuickUnion : public UnionFind{
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickUnion &);
public:
    explicit UnionFindQuickUnion(int size):
            parent(new std::vector<int>(size)) {
        for (int i = 0; i < size; i++)
            (*parent)[i] = i;
    }

    int getSize() const override { return parent -> size(); };
    bool isConnected(int p, int q) override  // 查看元素p和q是否同属于一个集合
    { return find(p) == find(q); }
    void unionElements(int p, int q) override;  // 合并元素p和q所属的集合

private:
    std::vector<int> *parent;

    int find(int p);   // 查找元素p所对应的集合编号
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickUnion &);

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_H
