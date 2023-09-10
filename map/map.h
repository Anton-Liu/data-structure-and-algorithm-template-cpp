#ifndef ALGORITHM_TEMPLATE_CPP_MAP_H
#define ALGORITHM_TEMPLATE_CPP_MAP_H

template <typename K, typename V>
class Map {
public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool contains(const K &key) const = 0;
    virtual V get(const K &key) const = 0;

    virtual void set(const K &key, const V &newValue) = 0;
    virtual void add(const K &key, const V &value) = 0;
    virtual void remove(const K &key) = 0;

    virtual ~Map() = default;
};


#endif //ALGORITHM_TEMPLATE_CPP_MAP_H
