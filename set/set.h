#ifndef ALGORITHM_TEMPLATE_CPP_SET_H
#define ALGORITHM_TEMPLATE_CPP_SET_H

template <typename T>
class Set {
public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool contains(const T &e) const = 0;

    virtual void add(const T &e) = 0;
    virtual void remove(const T &e) = 0;

    virtual ~Set() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_SET_H
