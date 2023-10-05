#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_FIND_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_FIND_H

#include "union_find.h"
#include <vector>
#include <iostream>

/**
 * 最简单的并查集Quick Find
 * 特点：
 *      查询很快，合并很慢
 * 各操作时间复杂度：
 *      isConnected: O(1)
 *      find: O(1)
 *      unionElements: O(n)
 */

class UnionFindQuickFind : public UnionFind{
    friend std::ostream &operator<<(std::ostream &, const UnionFindQuickFind &);
public:
    explicit UnionFindQuickFind(int size):
        id(new std::vector<int>(size)) {
        for (int i = 0; i < size; i++)
            (*id)[i] = i;
    }

    int getSize() const override { return id -> size(); };
    bool isConnected(int p, int q) override  // 查看元素p和q是否同属于一个集合
        { return find(p) == find(q); }
    void unionElements(int p, int q) override;  // 合并元素p和q所属的集合

    ~UnionFindQuickFind() { delete id; }
private:
    std::vector<int> *id;

    int find(int p);   // 查找元素p所对应的集合编号
};

std::ostream &operator<<(std::ostream &, const UnionFindQuickFind &);

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_QUICK_FIND_H
