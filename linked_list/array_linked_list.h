#ifndef ALGORITHM_TEMPLATE_CPP_ARRAY_LINKED_LIST_H
#define ALGORITHM_TEMPLATE_CPP_ARRAY_LINKED_LIST_H

#include "linked_list.h"
#include "../array/lazy_dynamic_array.h"
#include <iostream>
#include <utility>
#include <set>

template <typename T>
class ArrayLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const ArrayLinkedList<T> &);

template <typename T>
class ArrayLinkedList : public LinkedList<T> {
    friend std::ostream &operator<<<T>(std::ostream &os, const ArrayLinkedList<T> &rhs);
public:
    ArrayLinkedList():
            data(new std::vector<std::pair<T, int>>()), size(0), headIdx(-1), delSet(new std::set<int>()) { }

    ArrayLinkedList(const ArrayLinkedList<T> &rhs);
    ArrayLinkedList<T> &operator=(const ArrayLinkedList<T> &rhs);

    int getSize() const override { return size; };
    bool isEmpty() const override { return size == 0; };
    bool contains(const T &e) const override;
    T getFirst() const override;
    T getLast() const override;

    void addFirst(const T &e) override { add(0, e); };
    void addLast(const T &e) override { add(size, e); };
    void removeFirst() override;
    void removeLast() override;
    void removeElements(const T &e);

    void swap(ArrayLinkedList<T> &rhs);

    ~ArrayLinkedList() override;
    void add(int idx, const T &e);

private:
    const int END = -1;
    const int DELETED = -2;

    std::vector<std::pair<T, int>> *data;
    int size;
    int headIdx;  // 记录头结点位置，空表为-1
    std::set<int> *delSet;  // 记录被删除的索引

    T get(int idx) const;
    void remove(int idx);
};

template<typename T>
void ArrayLinkedList<T>::removeElements(const T &e) {
    while (headIdx >= 0 && (*data)[headIdx].first == e && (*data)[headIdx].second != DELETED) {
        int delIdx = headIdx;
        headIdx = (*data)[headIdx].second;
        (*data)[delIdx].second = DELETED;
        delSet -> insert(delIdx);
        size--;
    }

    int preIdx = headIdx;
    while (preIdx >= 0 && (*data)[preIdx].second != END) {
        if ((*data)[(*data)[preIdx].second].first == e) {
            int delIdx = (*data)[preIdx].second;
            (*data)[preIdx].second = (*data)[delIdx].second;
            (*data)[delIdx].second = DELETED;
            delSet -> insert(delIdx);
            size--;
        }
        else
            preIdx = (*data)[preIdx].second;
    }
}

template<typename T>
ArrayLinkedList<T>::ArrayLinkedList(const ArrayLinkedList<T> &rhs) {
    headIdx = rhs.headIdx;
    size = rhs.size;
    data = new std::vector<std::pair<T, int>>();
    delSet = new std::set<int>();

    for (const auto &p : *rhs.data)
        data -> emplace_back(p);
    for (auto iter = rhs.delSet -> begin(); iter != rhs.delSet -> end(); ++iter)
        delSet -> insert(*iter);
}

template<typename T>
ArrayLinkedList<T> &ArrayLinkedList<T>::operator=(const ArrayLinkedList<T> &rhs) {
    ArrayLinkedList<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
void ArrayLinkedList<T>::swap(ArrayLinkedList <T> &rhs) {
    using std::swap;
    swap(data, rhs.data);
    swap(size, rhs.size);
    swap(headIdx, rhs.headIdx);
    swap(delSet, rhs.delSet);
}

template<typename T>
ArrayLinkedList<T>::~ArrayLinkedList() {
    delete data;
    delete delSet;
}

template<typename T>
bool ArrayLinkedList<T>::contains(const T &e) const {
    auto curIdx = headIdx;
    while (curIdx != END) {
        if ((*data)[curIdx].first == e)
            return true;
        curIdx = (*data)[curIdx].second;
    }

    return false;
}

template<typename T>
void ArrayLinkedList<T>::add(int idx, const T &e) {
    if (idx < 0 || idx > data -> size())
        throw std::runtime_error("超过链表可插入范围！");

    if (idx == 0) {
        if (!delSet -> empty()) {
            int insertIndex = *(delSet -> begin());
            delSet -> erase(insertIndex);

            (*data)[insertIndex].first = e;
            (*data)[insertIndex].second = headIdx;
            headIdx = insertIndex;
        }
        else {
            data -> push_back(std::pair<T, int>(e, headIdx));
            headIdx = data -> size() - 1;
        }
        size++;
        return;
    }

    int preIdx = headIdx;
    for (int i = 0; i < idx - 1; i++)
        preIdx = (*data)[preIdx].second;

    if (!delSet -> empty()) {
        int insertIndex = *(delSet -> begin());
        delSet -> erase(insertIndex);

        (*data)[insertIndex].first = e;
        (*data)[insertIndex].second = (*data)[preIdx].second;
        (*data)[preIdx].second = insertIndex;
    }
    else {
        data -> push_back(std::pair<T, int>(e, (*data)[preIdx].second));
        (*data)[preIdx].second = data -> size() - 1;
    }
    size++;
}

template<typename T>
T ArrayLinkedList<T>::get(int idx) const {
    if (idx < 0 || idx >= data -> size())
        throw std::runtime_error("超过链表范围！");

    auto cur = headIdx;
    for (int i = 0; i < idx; i++)
        cur = (*data)[cur].second;
    return (*data)[cur].first;
}

template<typename T>
void ArrayLinkedList<T>::remove(int idx) {
    if (idx < 0 || idx >= data -> size())
        throw std::runtime_error("超过链表范围！");

    if (idx == 0) {
        int delIdx = headIdx;
        headIdx = (*data)[delIdx].second;
        (*data)[delIdx].second = DELETED;
        delSet -> insert(delIdx);
        size--;
        return;
    }

    int preIdx = headIdx;
    for (int i = 0; i < idx - 1; i++)
        preIdx = (*data)[headIdx].second;

    int delIdx = (*data)[preIdx].second;
    (*data)[preIdx].second = (*data)[delIdx].second;

    (*data)[delIdx].second = DELETED;
    delSet -> insert(delIdx);
    size--;
}

template<typename T>
T ArrayLinkedList<T>::getFirst() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(0);
}

template<typename T>
T ArrayLinkedList<T>::getLast() const {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    return get(size - 1);
}

template<typename T>
void ArrayLinkedList<T>::removeFirst() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(0);
}

template<typename T>
void ArrayLinkedList<T>::removeLast() {
    if (size == 0)
        throw std::runtime_error("链表为空！");

    remove(size - 1);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ArrayLinkedList<T> &rhs) {
    int size = rhs.getSize();

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    os << '\n';

    // 链表的信息
    os << "链表的长度：" << size << "\n"
       << "链表的内容：\n" << "list: ";

    for (int i = 0; i < size; i++)
        os << "(" << rhs.get(i) << ")->";
    os << "NULL\n";

    os << "内部表的内容：\n"
       << "INDEX\tVALUE\tNEXT_INDEX\n";
    for (int i = 0; i < rhs.data -> size(); i++) {
        if (i == rhs.headIdx) {
            os << "[" << i << "]" << "\t"
               << "[" << (*rhs.data)[i].first << "]" << "\t";
            if ((*rhs.data)[i].second == -1)
                os << "[END]\n";
            else
                os <<  "[" << (*rhs.data)[i].second << "]" << "\n";
        }
        else if ((*rhs.data)[i].second == rhs.DELETED)
            os << i << "\t"
               << "X\t"
               << "DELETED" << "\n";
        else {
            os << i << "\t"
               << (*rhs.data)[i].first << "\t";
            if ((*rhs.data)[i].second == -1)
                os << "END\n";
            else
                os << (*rhs.data)[i].second << "\n";
        }
    }
    os << "\n";

    // 自适应边框
    os << "--------------------------";
    for (int i = 0; i < size; i++)
        os << "----";
    return os;
}

#endif //ALGORITHM_TEMPLATE_CPP_ARRAY_LINKED_LIST_H
