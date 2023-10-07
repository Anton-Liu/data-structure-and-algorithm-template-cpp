#include "union_find_quick_find.h"

int UnionFindQuickFind::find(int p) {
    if (p < 0 || p >= id -> size())
        throw std::runtime_error("索引非法！");

    return (*id)[p];
}

void UnionFindQuickFind::unionElements(int p, int q) {
    auto pID = find(p);
    auto qID = find(q);

    if (pID == qID)
        return;

    for (auto &e : *id)
        if (e == pID)
            e = qID;
}

std::ostream &operator<<(std::ostream &os, const UnionFindQuickFind &uf) {
    // 自适应边框
    auto size = uf.getSize();
    os << "-----------------";
    for (int i = 0; i < size; i++)
        os << "---";
    os << '\n';

    // 数组信息
    os << "并查集大小：" << size << "\n"
       << "并查集数组表示：\n" << "index[";
    for (int i = 0 ; i < size; i++) {
        os << i;
        if (i != size - 1)
            os << ", ";
    }
    os << "]\n";

    os << "   id[";
    for (int i = 0 ; i < size; i++) {
        os << (*uf.id)[i];
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
