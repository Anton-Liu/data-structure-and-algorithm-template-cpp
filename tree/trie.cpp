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

bool Trie::isPrefix(const std::string &prefix) const {
    auto cur = root;
    for (const auto &c : prefix) {
        if (cur -> next -> find(c) == cur -> next -> end())
            return false;
        cur = cur -> next -> at(c);
    }

    return true;
}

bool Trie::contains(const std::string &word, char wildcard) const {
    return match(root, word, wildcard, 0);
}

bool Trie::match(const Trie::Node* node, const std::string &word, char wildcard, int idx) const {
    if (idx == word.size())
        return node -> isWord;

    if (word[idx] != wildcard) {
        if (node -> next -> find(word[idx]) == node -> next -> end())
            return false;
        return match(node -> next -> at(word[idx]), word, wildcard, idx + 1);
    }
    else {
        for (auto it = node -> next -> begin(); it != node -> next -> end(); ++it)
            if (match(it -> second, word, wildcard, idx + 1))
                return true;
        return false;
    }
}

void Trie::remove(const std::string &word) {
    removeRecursion(root, word, 0);
}

void Trie::removeRecursion(Trie::Node *node, const std::string &word, int idx) {
    if (idx == word.size()) {
        if (!node -> isWord)
            throw std::runtime_error("单词不存在！");
        node -> isWord = false;
        size--;
        return;
    }

    if (node -> next -> find(word[idx]) == node -> next -> end())
        throw std::runtime_error("单词不存在！");

    removeRecursion(node -> next -> at(word[idx]), word, idx + 1);

    auto nextNode = node -> next -> at(word[idx]);
    if (!nextNode -> isWord && nextNode -> next -> empty())
        node -> next -> erase(word[idx]);
}
