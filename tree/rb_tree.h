#ifndef ALGORITHM_TEMPLATE_CPP_RB_TREE_H
#define ALGORITHM_TEMPLATE_CPP_RB_TREE_H

#include <iostream>
#include <queue>

enum class rbColor { RED, BLACK };

template <typename K, typename V>
class RBTree {
    class RBTreeNode {
    public:
        explicit RBTreeNode(const std::pair<K, V> &kv):  // 默认插入红结点
                kv_(kv), right_(nullptr), left_(nullptr), parent_(nullptr), color_(rbColor::RED) { }

        std::pair<K, V> kv_;
        RBTreeNode *right_;
        RBTreeNode *left_;
        RBTreeNode *parent_;
        rbColor color_;
    };

public:
    RBTree(): m_nil(new RBTreeNode({})), m_size(0) {
        m_nil -> color_ = rbColor::BLACK;
        m_root = m_nil;
    }

    int size() const { return m_size; }

    void insert(const K &key, const V &val);

    ~RBTree() {
        std::queue<RBTreeNode*> que;
        if (m_root != m_nil)
            que.push(m_root);
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            if (cur -> left_ != m_nil)
                que.push(cur -> left_);
            if (cur -> right_ != m_nil)
                que.push(cur -> right_);
            delete cur;
        }
        delete m_nil;
    }

private:
    RBTreeNode *m_root;  // 根结点
    RBTreeNode *m_nil;  // 虚拟叶结点(黑色结点，所有实际叶结点的left、right指针和根结点的parent指针都指向该结点)，注意nil只能被指向
    int m_size;  // 红黑树的当前大小(不含虚拟叶结点)

    // 对结点y进行向左旋转操作，返回旋转后新的根结点x
    //    y                             x
    //  /  \                          /   \
    // T1   x      向左旋转 (y)       y     z
    //     / \     -------->       / \   / \
    //   T2  z                    T1 T2 T3 T4
    //      / \
    //     T3 T4
    void leftRotate(RBTreeNode *y);

    // 对结点y进行向右旋转操作，返回旋转后新的根结点x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋转 (y)        z     y
    //     / \         --------->       / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    void rightRotate(RBTreeNode *y);

    // 插入结点后进行调整
    void insertFixup(RBTreeNode *node);
};

template<typename K, typename V>
void RBTree<K, V>::leftRotate(RBTree::RBTreeNode *y) {
    auto x = y -> right_;
    y -> right_ = x -> left_;
    if (x -> left_ != m_nil)
        x -> left_ -> parent_ = y;

    x -> parent_ = y -> parent_;
    if (y -> parent_ == m_nil)
        m_root = x;
    else if (y == y -> parent_ -> left_)
        y -> parent_ -> left_ = x;
    else  // y == y -> parent_ -> right_
        y -> parent_ -> right_ = x;

    x -> left_ = y;
    y -> parent_ = x;
}


template<typename K, typename V>
void RBTree<K, V>::rightRotate(RBTree::RBTreeNode *y) {
    auto x = y -> left_;
    y -> left_ = x -> right_;
    if (x -> right_ != m_nil)
        x -> right_ -> parent_ = y;

    x -> parent_ = y -> parent_;
    if (y -> parent_ == m_nil)
        m_root = x;
    else if (y == y -> parent_ -> left_)
        y -> parent_ -> left_ = x;
    else
        y -> parent_ -> right_ = x;

    x -> right_ = y;
    y -> parent_ = x;
}

template<typename K, typename V>
void RBTree<K, V>::insert(const K &key, const V &val) {
    // 构造插入结点
    RBTreeNode *insertNode = new RBTreeNode({key, val});
    insertNode -> left_ = insertNode -> right_ = insertNode -> parent_ = m_nil;

    RBTreeNode *cur = m_root;
    RBTreeNode *pre = m_nil;  // 指向当前结点的上一个结点
    while (cur != m_nil) {
        pre = cur;
        if (insertNode -> kv_.first < cur -> kv_.first)
            cur = cur -> left_;
        else if (insertNode -> kv_.first > cur -> kv_.first)
            cur = cur -> right_;
        else  // 相同结点处理(取决于业务场景)
            return;
    }

    // 若当前红黑树无实际结点，让insertNode成为黑色根结点
    if (m_root == m_nil) {
        insertNode -> color_ = rbColor::BLACK;
        m_root = insertNode;
    }
    else {
        // 当前红黑树有实际结点
        if (insertNode -> kv_.first < pre -> kv_.first)
            pre -> left_ = insertNode;
        else
            pre -> right_ = insertNode;

        insertNode -> parent_ = pre;
        insertNode -> color_ = rbColor::RED;
    }

    insertFixup(insertNode);  // 对插入的红结点进行调整
    m_size++;
}

template<typename K, typename V>
void RBTree<K, V>::insertFixup(RBTree::RBTreeNode *node) {
    // 此时，node是红结点，node的父结点是红结点，node的祖父结点是黑结点
    //      node的叔父结点颜色不确定，需要分类讨论
    while (node -> color_ == rbColor::RED) {
        // 若不存在祖父结点，无需调整
        if (node -> parent_ -> parent_ == m_nil)
            return;

        // 若为根结点，变黑即可
        if (node == m_root) {
            node -> color_ = rbColor::BLACK;
            break;
        }

        // node插入在祖父结点的左子树中
        if (node -> parent_ == node -> parent_ -> parent_ -> left_) {
            RBTreeNode *uncle = node -> parent_ -> parent_ -> right_;
            if (uncle -> color_ == rbColor::RED) {  // 叔父结点是红色的
                //  平衡，无需再旋转，按如下调整可满足红黑树性质
                //        B                        R
                //      /  \                     /  \
                //     R    R    -------->      B    B
                //     |                        |
                //    [R]                      [R]
                node -> parent_ -> parent_ -> color_ = rbColor::RED;
                node -> parent_ -> color_  = rbColor::BLACK;
                uncle -> color_ = rbColor::BLACK;

                node = node -> parent_ -> parent_;  // 让祖父结点成为待调整结点node
            }
            else {  // 叔父结点是黑色的(只可能是nil)
                if (node == node -> parent_ -> left_) {
                    //  祖父结点不平衡，需先LL旋转，再按如下调整可满足红黑树性质
                    //        B                       R                           B
                    //       /                      /  \                        /  \
                    //      R      -------->      [R]   B    -------->        [R]   R
                    //     /
                    //   [R]
                    rightRotate(node -> parent_ -> parent_);
                    node -> parent_ -> color_ = rbColor::BLACK;
                    node -> parent_ -> right_ -> color_ = rbColor::RED;
                }
                else {
                    //  祖父结点不平衡，需先LR旋转，再按如下调整可满足红黑树性质
                    //        B                       B                        [R]                      [B]
                    //      /                        /                        /  \                     /  \
                    //     R       -------->       [R]       -------->       R    B     -------->     R    R
                    //      \                      /
                    //      [R]                   R
                    leftRotate(node -> parent_);
                    rightRotate(node -> parent_);
                    node -> color_ = rbColor::BLACK;
                    node -> right_ -> color_ = rbColor::RED;
                }
                break;
            }
        }
        else {  // node插入在祖父结点的右子树中(对称情况)
            RBTreeNode *uncle = node -> parent_ -> parent_ -> left_;
            if (uncle -> color_ == rbColor::RED) {  // 叔父结点是红色的
                //  平衡，需先LL旋转，再按如下调整可满足红黑树性质
                //        B                        R
                //      /  \                     /  \
                //     R    R    -------->      B    B
                //          |                        |
                //         [R]                      [R]
                node -> parent_ -> parent_ -> color_ = rbColor::RED;
                node -> parent_ -> color_  = rbColor::BLACK;
                uncle -> color_ = rbColor::BLACK;

                node = node -> parent_ -> parent_;  // 让祖父结点成为待调整结点node
            }
            else {  // 叔父结点是黑色的(只可能是nil)
                if (node == node -> parent_ -> right_) {
                    //  祖父结点不平衡，需先RR旋转，再按如下调整可满足红黑树性质
                    //     B                           R                           B
                    //      \                        /  \                        /  \
                    //       R       -------->      B   [R]     -------->       R   [R]
                    //        \
                    //        [R]
                    leftRotate(node -> parent_ -> parent_);
                    node -> parent_ -> color_ = rbColor::BLACK;
                    node -> parent_ -> left_ -> color_ = rbColor::RED;
                }
                else {
                    //  祖父结点不平衡，需先RL旋转，再按如下调整可满足红黑树性质
                    //      B                      B                           [R]                      [B]
                    //       \                      \                         /  \                     /  \
                    //        R     -------->       [R]       -------->      B    R     -------->     R    R
                    //       /                        \
                    //     [R]                         R
                    rightRotate(node -> parent_);
                    leftRotate(node -> parent_);
                    node -> color_ = rbColor::BLACK;
                    node -> left_ -> color_ = rbColor::RED;
                }
                break;
            }
        }
    }
}

#endif //ALGORITHM_TEMPLATE_CPP_RB_TREE_H
