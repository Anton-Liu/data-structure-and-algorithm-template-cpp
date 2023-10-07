#include "union_find_quick_union.h"

void UnionFindQuickUnion::unionElements(int p, int q) {
    auto pRoot = find(p);
    auto qRoot = find(q);

    if (pRoot == qRoot)
        return;

    (*parent)[pRoot] = qRoot;
}

int UnionFindQuickUnion::find(int p) {
    if (p < 0 || p >= parent -> size())
        throw std::runtime_error("索引非法！");

    while (p != (*parent)[p])
        p = (*parent)[p];

    return p;
}

std::ostream &operator<<(std::ostream &os, const UnionFindQuickUnion &uf) {
    // 自适应边框
    auto size = uf.getSize();
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
