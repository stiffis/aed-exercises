#ifndef NODE_H
#define NODE_H

#include <iostream>

template <typename TK> struct Node {
    TK *keys;
    Node<TK> **children;
    int count;
    bool leaf;
    int M;

    Node(int _M) : count(0), leaf(true), M(_M) {
        keys = new TK[M - 1];
        children = new Node<TK> *[M];
        for (int i = 0; i < M; ++i)
            children[i] = nullptr;
    }

    ~Node() {
        delete[] keys;
        delete[] children;
    }
};

#endif // NODE_H
