//#ifndef ALGORITHM_TEMPLATE_CPP_TRIE_MAP_H
//#define ALGORITHM_TEMPLATE_CPP_TRIE_MAP_H
//
//#include "map.h"
//#include "../tree/trie_with_weight.h"
//#include <string>
//
//class TrieMap : public Map<std::string, int> {
//public:
//    TrieMap():
//        trie(new TrieWithWeight) {  }
//
//    int getSize() const override { return trie -> getSize(); }
//    bool isEmpty() const override { return trie -> isEmpty(); }
//    bool contains(const std::string &key) const override { return trie -> contains(key); }
//    int get(const std::string &key) const override { return trie -> getWeight(key); }
//    void set(const std::string &key, const int &newValue) override { trie -> setWeight(key, newValue); };
//    void add(const std::string &key, const int &value) override { trie -> add(key, value); };
//    void remove(const std::string &key) override;
//
//    ~TrieMap() override { delete trie; };
//private:
//    TrieWithWeight *trie;
//};
//
//#endif //ALGORITHM_TEMPLATE_CPP_TRIE_MAP_H
