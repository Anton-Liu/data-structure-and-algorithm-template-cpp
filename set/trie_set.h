#ifndef ALGORITHM_TEMPLATE_CPP_TRIE_SET_H
#define ALGORITHM_TEMPLATE_CPP_TRIE_SET_H

#include "set.h"
#include <string>
#include "../tree/trie.h"

class TrieSet : public Set<std::string> {
public:
    TrieSet(): trie(new Trie) { }

    int getSize() const override { return trie -> getSize(); }
    bool isEmpty() const override { return trie -> isEmpty(); }
    bool contains(const std::string &e) const override { return trie -> contains(e); }
    void add(const std::string &e) override { trie -> add(e); };
    void remove(const std::string &e) override { trie -> remove(e); };

    ~TrieSet() override { delete trie; }
private:
    Trie *trie;
};


#endif //ALGORITHM_TEMPLATE_CPP_TRIE_SET_H
