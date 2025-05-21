#ifndef AVL_ITERATOR_H
#define AVL_ITERATOR_H

#include <vector>
#include "AVL_Node.h"

template<typename E>
class SimpleQueue {
private:
    std::vector<E> data;
    size_t head = 0;
public:
    void push(const E& e) { data.push_back(e); }
    void pop() { if (head < data.size()) ++head; }
    E& front() { return data[head]; }
    bool empty() const { return head >= data.size(); }
};

template<typename T>
class AVLIterator {
public:
    enum Type { PreOrder, InOrder, PostOrder, BFS };

private:
    std::vector<NodeAVL<T>*> seq;
    size_t pos;
    NodeAVL<T>* current;
    Type type;

    void buildSeq(NodeAVL<T>* root) {
        if (!root) return;
        switch (type) {
            case PreOrder:
                seq.push_back(root);
                buildSeq(root->left);
                buildSeq(root->right);
                break;
            case InOrder:
                buildSeq(root->left);
                seq.push_back(root);
                buildSeq(root->right);
                break;
            case PostOrder:
                buildSeq(root->left);
                buildSeq(root->right);
                seq.push_back(root);
                break;
            case BFS: {
                SimpleQueue<NodeAVL<T>*> q;
                q.push(root);
                while (!q.empty()) {
                    auto n = q.front(); q.pop();
                    seq.push_back(n);
                    if (n->left)  q.push(n->left);
                    if (n->right) q.push(n->right);
                }
                break;
            }
        }
    }

public:
    AVLIterator() : pos(0), current(nullptr), type(InOrder) {}
    AVLIterator(NodeAVL<T>* root, Type t = InOrder)
        : pos(0), current(nullptr), type(t) {
        buildSeq(root);
        if (!seq.empty()) current = seq[0];
    }

    AVLIterator<T>& operator=(AVLIterator<T> other) {
        seq     = std::move(other.seq);
        pos     = other.pos;
        current = other.current;
        type    = other.type;
        return *this;
    }
    bool operator!=(AVLIterator<T> o) const { return current != o.current; }
    AVLIterator<T>& operator++() {
        if (pos < seq.size()) ++pos;
        current = (pos < seq.size() ? seq[pos] : nullptr);
        return *this;
    }
    T operator*() const { return current->data; }
};

#endif
