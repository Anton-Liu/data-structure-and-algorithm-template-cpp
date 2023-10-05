#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_RANK_OPTIMIZATION_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_RANK_OPTIMIZATION_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 并查集Quick Union，树的高度优化
 * 特点：
 *      通过树的高度对合并进行优化
 *      相比基于size优化的Quick Union更加合理
 * 各操作时间复杂度：
 *      isConnected: O(h)
 *      find: O(h)
 *      unionElements: O(h)
 *      h是树的高度
 */

class UnionFindQuickUnionWithRankOptimization : UnionFind {
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithRankOptimization &);
public:
    explicit UnionFindQuickUnionWithRankOptimization(int size):
            parent(new std::vector<int>(size)), rank(new std::vector<int>(size)) {
        for (int i = 0; i < size; i++) {
            (*parent)[i] = i;
            (*rank)[i] = 1;
        }
    }

    int getSize() const override { return parent -> size(); };
    bool isConnected(int p, int q) override  // 查看元素p和q是否同属于一个集合
    { return find(p) == find(q); }
    void unionElements(int p, int q) override;  // 合并元素p和q所属的集合

private:
    std::vector<int> *parent;
    std::vector<int> *rank;  // rank[i]表示以i为根的集合所表示的树的层数

    int find(int p);   // 查找元素p所对应的集合编号
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithRankOptimization &);

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_RANK_OPTIMIZATION_H
