#ifndef ALGORITHM_TEMPLATE_CPP_TRIE_H
#define ALGORITHM_TEMPLATE_CPP_TRIE_H

#include <map>
#include <string>

class Trie {
    // friend std::ostream &operator<<(std::ostream &, const Trie &);
public:
    Trie():
        root(new Node()), size(0) { }

    int getSize() const { return size; }  // 获取当前trie中含有的单词数量
    bool isEmpty() const { return size == 0; }  // 判断trie中是否存在单词
    bool isPrefix(const std::string &prefix) const;  // 查询Trie中是否含有单词以prefix为前缀
    bool contains(const std::string &word) const;  // 查询Trie中是否含有单词word
    bool contains(const std::string &word, char wildcard) const;  // 查询Trie中是否含有单词(允许使用word通配符)

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

    // 递归函数，完成支持通配符的查询
    // 如果存在字符串与word匹配，则返回true；否则，返回false
    // word中可能包含一些通配符，每个通配符都可以表示任何一个字母。
    bool match(const Node *node, const std::string &word, char wildcard, int idx) const;
};

// std::ostream &operator<<(std::ostream &, const Trie &);

#endif //ALGORITHM_TEMPLATE_CPP_TRIE_H
