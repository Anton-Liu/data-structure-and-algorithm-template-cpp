#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_H

template <typename T>
class Array {
public:
    virtual int getSize() const = 0;  // 获取数组大小
    virtual int getCapacity() const = 0;  // 获取数组容量
    virtual bool isEmpty() const = 0;  // 判断数组是否为空
    virtual bool contains(const T &e) const = 0;  // 判断数组中是否有元素e
    virtual int getIndex(const T &e) const = 0;  // 获取元素e的下标，不存在返回-1
    virtual T get(const int &idx) const = 0;  // 返回下标idx的元素
    virtual T getFirst() const = 0;  // 获取第一个位置的元素
    virtual T getLast() const = 0;  // 获取最后一个位置的元素

    virtual void set(const int &idx, const T &e) = 0;  // 修改下标idx处元素的值为e
    virtual void add(const int &idx, const T &e) = 0;  // 在数组下标idx处插入一个新元素e
    virtual void addFirst(const T &e) = 0;  // 在数组所有元素前添加一个新元素e
    virtual void addLast(const T &e) = 0;  // 在数组所有元素后添加一个新元素e
    virtual T remove(const int &idx) = 0;  //  删除数组idx位置的元素，返回被删除的元素
    virtual T removeFirst() = 0;  // 删除数组第一个元素并返回
    virtual T removeLast() = 0;  // 删除数组最后一个元素并返回

    virtual T &operator[](int idx) = 0;
    virtual const T &operator[](int idx) const = 0;

    virtual ~Array() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_H
