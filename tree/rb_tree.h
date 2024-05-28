#ifndef ALGORITHM_TEMPLATE_CPP_RB_TREE_H
#define ALGORITHM_TEMPLATE_CPP_RB_TREE_H

enum class rbColor { red, black };

template <typename KeyType, typename ValueType>
class RBTree {
    class RBTreeNode {
    public:
        KeyType key;
        ValueType *value;
        RBTreeNode *right;
        RBTreeNode *left;
        RBTreeNode *parent;
        rbColor color;
    };
public:

private:
    RBTreeNode *root;  // 根结点
    RBTreeNode *nil;  // 叶子结点

    // 对结点y进行向左旋转操作，返回旋转后新的根结点x
    //    y                             x
    //  /  \                          /   \
    // T1   x      向左旋转 (y)       y     z
    //     / \     -------->       / \   / \
    //   T2  z                    T1 T2 T3 T4
    //      / \
    //     T3 T4
    void leftRotate(RBTree *tree, RBTreeNode *y);

    // 对结点y进行向右旋转操作，返回旋转后新的根结点x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋转 (y)        z     y
    //     / \         --------->       / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    void rightRotate(RBTree *tree, RBTreeNode *y);
};


#endif //ALGORITHM_TEMPLATE_CPP_RB_TREE_H
