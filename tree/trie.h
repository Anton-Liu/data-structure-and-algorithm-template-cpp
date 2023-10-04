#ifndef ALGORITHM_TEMPLATE_CPP_TRIE_H
#define ALGORITHM_TEMPLATE_CPP_TRIE_H

#include <map>
#include <string>

class Trie {
    // friend std::ostream &operator<<(std::ostream &, const Trie &);
public:
    Trie():
        root(new Node()), size(0) { }

    int getSize() { return size; }
    bool contains(const std::string &word) const;  // 查询Trie中是否含有单词word
    void add(const std::string &word);  // 向Trie中添加单词word
private:
    class Node {
    public:
        bool isWord;  // 访问到当前Node时，是否能确定一个单词
        std::map<char, Node*> *next;
        explicit Node(bool isWord):
            isWord(isWord), next(new std::map<char, Node*>()) { }
        Node():
            isWord(false), next(new std::map<char, Node*>()) { }
        ~Node() { delete next; }
    };

    Node *root;  // 根结点
    int size;  // 记录当前Trie中单词数量
};

// std::ostream &operator<<(std::ostream &, const Trie &);

#endif //ALGORITHM_TEMPLATE_CPP_TRIE_H
