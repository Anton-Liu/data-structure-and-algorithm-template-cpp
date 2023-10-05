#include "UnionFindQuickUnionWithAllOptimization.h"

void UnionFindQuickUnionWithAllOptimization::unionElements(int p, int q) {
    int pRoot = find(p);
    int qRoot = find(q);

    if (pRoot == qRoot)
        return;

    // 按秩优化
    if ((*rank)[pRoot] < (*rank)[qRoot])
        (*parent)[pRoot] = qRoot;
    else if ((*rank)[qRoot] < (*rank)[pRoot])
        (*parent)[qRoot] = pRoot;
    else {  // (*rank)[qRoot] == (*rank)[pRoot]
        (*parent)[pRoot] = qRoot;
        (*rank)[qRoot]++;
    }

}

int UnionFindQuickUnionWithAllOptimization::find(int p) {
    if (p < 0 || p >= parent -> size())
        throw std::runtime_error("索引非法！");

    while (p != (*parent)[p]) {
        (*parent)[p] = (*parent)[(*parent)[p]];  // 路径压缩
        p = (*parent)[p];
    }

    return p;
}

int UnionFindQuickUnionWithAllOptimization::findRecursion(int p) {
    if (p < 0 || p >= parent -> size())
        throw std::runtime_error("索引非法！");

    if (p != (*parent)[p]) {
        (*parent)[p] = findRecursion((*parent)[p]);
    }

    return (*parent)[p];
}

std::ostream &operator<<(std::ostream &os, const UnionFindQuickUnionWithAllOptimization &uf) {
    // 自适应边框
    int size = uf.getSize();
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << "并查集大小：" << size << "\n"
       << "并查集数组表示：\n" << " index[";
    for (int i = 0 ; i < size; i++) {
        os << i;
        if (i != size - 1)
            os << ", ";
    }
    os << "]\n";

    os << "parent[";
    for (int i = 0 ; i < size; i++) {
        os << (*uf.parent)[i];
        if (i != size - 1)
            os << ", ";
    }
    os << "]\n";

    // 自适应边框
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    return os;
}
