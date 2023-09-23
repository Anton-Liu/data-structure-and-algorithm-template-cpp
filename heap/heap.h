#ifndef ALGORITHM_TEMPLATE_CPP_HEAP_H
#define ALGORITHM_TEMPLATE_CPP_HEAP_H

template <typename T>
class Heap {
public:
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual T getTop() const = 0;

    virtual void add(const T &e) = 0;
    virtual T extractTop() = 0;
    virtual T replace(const T &e) = 0;

    virtual ~Heap() = default;

private:
    virtual void siftUp(int idx) = 0;
    virtual void siftDown(int idx) = 0;
};


#endif //ALGORITHM_TEMPLATE_CPP_HEAP_H
