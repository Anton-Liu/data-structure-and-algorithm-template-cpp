#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_PATH_COMPRESSION_OPTIMIZATION_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_PATH_COMPRESSION_OPTIMIZATION_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 并查集Quick Union，路径压缩优化
 * 特点：
 *      对find进行路径压缩优化
 *      相比基本Quick Union各操作性能都有所提升
 * 各操作时间复杂度：
 *      isConnected: O(h)
 *      find: O(h)
 *      unionElements: O(h)
 *      h是树的高度
 */

class UnionFindQuickUnionWithPathCompressionOptimization : public UnionFind {
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithPathCompressionOptimization &);
public:
    explicit UnionFindQuickUnionWithPathCompressionOptimization(int size):
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
    int findRecursion(int p);  // find路径压缩的递归写法，一次就能压缩成两层
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithPathCompressionOptimization &);

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_UNION_WITH_PATH_COMPRESSION_OPTIMIZATION_H
