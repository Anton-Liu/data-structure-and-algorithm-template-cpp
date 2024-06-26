#ifndef ALGORITHM_TEMPLATE_CPP_UNIONFINDQUICKUNIONWITHALLOPTIMIZATION_H
#define ALGORITHM_TEMPLATE_CPP_UNIONFINDQUICKUNIONWITHALLOPTIMIZATION_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 并查集Quick Union，进行多种优化
 * 特点：
 *      rank优化(按秩优化)
 *      路径压缩优化
 * 各操作时间复杂度：
 *      isConnected: O(h)
 *      find: O(h)
 *      unionElements: O(h)
 *      h是树的高度
 *      实际上各操作时间复杂度为：O(log*n)
 */

class UnionFindQuickUnionWithAllOptimization : UnionFind {
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithAllOptimization &);
public:
    explicit UnionFindQuickUnionWithAllOptimization(int size):
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
    std::vector<int> *rank;  // rank[i]由于路径压缩，不再表示树的高度，
                             // 但仍具有参考意义，rank值高的结点在上方，值低的结点在下方

    int find(int p);   // 查找元素p所对应的集合编号
    int findRecursion(int p);  // find路径压缩的递归写法，一次就能压缩成两层
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickUnionWithAllOptimization &);

#endif //ALGORITHM_TEMPLATE_CPP_UNIONFINDQUICKUNIONWITHALLOPTIMIZATION_H
