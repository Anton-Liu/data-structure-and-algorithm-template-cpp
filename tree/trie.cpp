#include "trie.h"

void Trie::add(const std::string &word) {
    auto cur = root;
    for (const auto &c : word) {
        if (cur -> next -> find(c) == cur -> next -> end())
            cur -> next -> insert({c, new Node()});
        cur = cur -> next -> at(c);
    }

    if (!cur -> isWord) {  // 单词可能已经存在！
        cur -> isWord = true;
        size++;
    }
}

bool Trie::contains(const std::string &word) const {
    auto cur = root;
    for (const auto &c : word) {
        if (cur -> next -> find(c) == cur -> next -> end())
            return false;
        cur = cur -> next -> at(c);
    }

    return cur -> isWord;
}

