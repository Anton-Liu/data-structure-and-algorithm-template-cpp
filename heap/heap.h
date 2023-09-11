#ifndef ALGORITHM_TEMPLATE_CPP_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_HEAP_H

template <typename T>
class Heap {
public:
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual T findMax() const = 0;

    virtual void add(const T &e) = 0;
    virtual T extractMax() = 0;
    virtual T replace(const T &e) = 0;

    virtual ~Heap() = default;
private:
    virtual int parent(int idx) const = 0;
    virtual int leftChild(int idx) const = 0;
    virtual int rightChild(int idx) const = 0;

    virtual void siftUp(int idx) = 0;
    virtual void siftDown(int idx) = 0;
};


#endif //ALGORITHM_TEMPLATE_CPP_HEAP_H
