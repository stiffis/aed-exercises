#ifndef AVL_NODE_H
#define AVL_NODE_H

template<typename T>
struct NodeAVL {
    T data;
    int height;
    NodeAVL* left;
    NodeAVL* right;
    NodeAVL() : left(nullptr), right(nullptr), height(0) {}
    NodeAVL(T value) : data(value), left(nullptr), right(nullptr), height(0) {}
    void killSelf() {
        if (left)  left->killSelf();
        if (right) right->killSelf();
        delete this;
    }
};

#endif
