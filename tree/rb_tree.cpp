#include "rb_tree.h"

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::leftRotate(RBTree *tree, RBTree::RBTreeNode *y) {
    auto x = y -> right;
    y -> right = x -> left;
    if (x -> left)
        x -> left -> parent = y;

    x -> parent = y -> parent;
    if (y -> parent == tree -> nil) {
        tree -> root = x;
    }
    else if (y == y -> parent -> left)
        y -> parent -> left = x;
    else  // y == y -> parent -> right
        y -> parent -> right = x;

    x -> left = y;
    y -> parent = x;
}


template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rightRotate(RBTree *tree, RBTree::RBTreeNode *y) {
    // 对结点y进行向右旋转操作，返回旋转后新的根结点x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋转 (y)        z     y
    //     / \         --------->       / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    auto x = y -> left;
    y -> left = x -> right;
    if (x -> right)
        x -> right -> parent = y;

    x -> parent = y -> parent;
    if (y -> parent == tree -> nil)
        tree -> root = x;
    else if (y == y -> parent -> left)
        y -> parent -> left = x;
    else
        y -> parent -> right = x;

    x -> right = y;
    y -> parent = x;
}
