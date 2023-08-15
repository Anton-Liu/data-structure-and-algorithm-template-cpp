#ifndef ALGORITHM_TEMPLATE_CPP_STACK_H
#define ALGORITHM_TEMPLATE_CPP_STACK_H

template <typename T>
class Stack {
public:
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual T top() const = 0;
    virtual void push(const T &e) = 0;
    virtual void pop() = 0;
    virtual ~Stack() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_STACK_H
