#ifndef ALGORITHM_TEMPLATE_CPP_UNION_FIND_H
#define ALGORITHM_TEMPLATE_CPP_UNION_FIND_H

class UnionFind {
public:
    virtual int getSize() const = 0;
    virtual bool isConnected(int p, int q) = 0;
    virtual void unionElements(int p, int q) = 0;

    ~UnionFind() = default;
};

#endif //ALGORITHM_TEMPLATE_CPP_UNION_FIND_H
