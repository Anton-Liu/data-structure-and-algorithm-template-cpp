#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_SIZE_OPTIMIZATION_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_SIZE_OPTIMIZATION_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 并查集Quick Union，集合大小优化
 * 特点：
 *      通过集合大小对合并进行优化
 *      合并性能相比基本Quick Union有进一步提升
 * 各操作时间复杂度：
 *      isConnected: O(h)
 *      find: O(h)
 *      unionElements: O(h)
 *      h是树的高度
 */

class UnionFindQuickUnionWithSizeOptimization : public UnionFind {
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithSizeOptimization &);
public:
    explicit UnionFindQuickUnionWithSizeOptimization(int size):
            parent(new std::vector<int>(size)), sz(new std::vector<int>(size)) {
        for (int i = 0; i < size; i++) {
            (*parent)[i] = i;
            (*sz)[i] = 1;
        }
    }

    int getSize() const override { return parent -> size(); };

    bool isConnected(int p, int q) override  // 查看元素p和q是否同属于一个集合
    { return find(p) == find(q); }
    void unionElements(int p, int q) override;  // 合并元素p和q所属的集合

private:
    std::vector<int> *parent;
    std::vector<int> *sz;  // sz[i]表示以i为根的集合中元素的个数

    int find(int p);   // 查找元素p所对应的集合编号
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithSizeOptimization &);

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_SIZE_OPTIMIZATION_H
