#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename TK> class BTree {
  private:
    Node<TK> *root;
    int M;
    int n;

    int t() const { return (M + 1) / 2; }

    void traverse(Node<TK> *x, std::vector<TK> &out) const {
        if (!x)
            return;
        int i;
        for (i = 0; i < x->count; ++i) {
            if (!x->leaf)
                traverse(x->children[i], out);
            out.push_back(x->keys[i]);
        }
        if (!x->leaf)
            traverse(x->children[i], out);
    }

    Node<TK> *search(Node<TK> *x, TK k) const {
        if (!x)
            return nullptr;
        int i = 0;
        while (i < x->count && k > x->keys[i])
            ++i;
        if (i < x->count && k == x->keys[i])
            return x;
        if (x->leaf)
            return nullptr;
        return search(x->children[i], k);
    }

    void splitChild(Node<TK> *x, int i) {
        Node<TK> *y = x->children[i];
        Node<TK> *z = new Node<TK>(M);
        z->leaf = y->leaf;
        int mid = t() - 1;
        for (int j = 0; j < y->count - mid - 1; ++j)
            z->keys[j] = y->keys[j + mid + 1];
        if (!y->leaf) {
            for (int j = 0; j <= y->count - mid - 1; ++j)
                z->children[j] = y->children[j + mid + 1];
        }
        z->count = y->count - mid - 1;
        y->count = mid;

        for (int j = x->count; j >= i + 1; --j)
            x->children[j + 1] = x->children[j];
        x->children[i + 1] = z;
        for (int j = x->count - 1; j >= i; --j)
            x->keys[j + 1] = x->keys[j];
        x->keys[i] = y->keys[mid];
        ++x->count;
    }

    void insertNonFull(Node<TK> *x, TK k) {
        int i = x->count - 1;
        if (x->leaf) {
            while (i >= 0 && x->keys[i] > k) {
                x->keys[i + 1] = x->keys[i];
                --i;
            }
            x->keys[i + 1] = k;
            ++x->count;
        } else {
            while (i >= 0 && x->keys[i] > k)
                --i;
            ++i;
            if (x->children[i]->count == M - 1) {
                splitChild(x, i);
                if (x->keys[i] < k)
                    ++i;
            }
            insertNonFull(x->children[i], k);
        }
    }

    TK getPred(Node<TK> *x, int idx) {
        Node<TK> *cur = x->children[idx];
        while (!cur->leaf)
            cur = cur->children[cur->count];
        return cur->keys[cur->count - 1];
    }
    TK getSucc(Node<TK> *x, int idx) {
        Node<TK> *cur = x->children[idx + 1];
        while (!cur->leaf)
            cur = cur->children[0];
        return cur->keys[0];
    }

    void merge(Node<TK> *x, int idx) {
        Node<TK> *c = x->children[idx];
        Node<TK> *s = x->children[idx + 1];
        int cs = t() - 1;
        c->keys[cs] = x->keys[idx];
        for (int i = 0; i < s->count; ++i)
            c->keys[i + cs + 1] = s->keys[i];
        if (!s->leaf) {
            for (int i = 0; i <= s->count; ++i)
                c->children[i + cs + 1] = s->children[i];
        }
        c->count += s->count + 1;
        for (int i = idx + 1; i < x->count; ++i)
            x->keys[i - 1] = x->keys[i];
        for (int i = idx + 2; i <= x->count; ++i)
            x->children[i - 1] = x->children[i];
        --x->count;
        delete s;
    }

    void borrowFromPrev(Node<TK> *x, int idx) {
        Node<TK> *c = x->children[idx];
        Node<TK> *p = x->children[idx - 1];
        for (int i = c->count - 1; i >= 0; --i)
            c->keys[i + 1] = c->keys[i];
        if (!c->leaf) {
            for (int i = c->count; i >= 0; --i)
                c->children[i + 1] = c->children[i];
        }
        c->keys[0] = x->keys[idx - 1];
        if (!p->leaf)
            c->children[0] = p->children[p->count];
        x->keys[idx - 1] = p->keys[p->count - 1];
        --p->count;
        ++c->count;
    }
    void borrowFromNext(Node<TK> *x, int idx) {
        Node<TK> *c = x->children[idx];
        Node<TK> *n = x->children[idx + 1];
        c->keys[c->count] = x->keys[idx];
        if (!c->leaf)
            c->children[c->count + 1] = n->children[0];
        x->keys[idx] = n->keys[0];
        for (int i = 1; i < n->count; ++i)
            n->keys[i - 1] = n->keys[i];
        if (!n->leaf) {
            for (int i = 1; i <= n->count; ++i)
                n->children[i - 1] = n->children[i];
        }
        ++c->count;
        --n->count;
    }

    void fill(Node<TK> *x, int idx) {
        if (idx && x->children[idx - 1]->count >= t())
            borrowFromPrev(x, idx);
        else if (idx != x->count && x->children[idx + 1]->count >= t())
            borrowFromNext(x, idx);
        else {
            if (idx != x->count)
                merge(x, idx);
            else
                merge(x, idx - 1);
        }
    }

    void removeFromLeaf(Node<TK> *x, int idx) {
        for (int i = idx + 1; i < x->count; ++i)
            x->keys[i - 1] = x->keys[i];
        --x->count;
    }
    void removeFromNonLeaf(Node<TK> *x, int idx) {
        TK k = x->keys[idx];
        if (x->children[idx]->count >= t()) {
            TK pred = getPred(x, idx);
            x->keys[idx] = pred;
            remove(x->children[idx], pred);
        } else if (x->children[idx + 1]->count >= t()) {
            TK succ = getSucc(x, idx);
            x->keys[idx] = succ;
            remove(x->children[idx + 1], succ);
        } else {
            merge(x, idx);
            remove(x->children[idx], k);
        }
    }

    void remove(Node<TK> *x, TK k) {
        if (!x)
            return;
        int idx = 0;
        while (idx < x->count && x->keys[idx] < k)
            ++idx;
        if (idx < x->count && x->keys[idx] == k) {
            if (x->leaf)
                removeFromLeaf(x, idx);
            else
                removeFromNonLeaf(x, idx);
        } else {
            if (x->leaf)
                return;
            bool flag = (idx == x->count);
            if (x->children[idx]->count < t())
                fill(x, idx);
            if (flag && idx > x->count)
                remove(x->children[idx - 1], k);
            else
                remove(x->children[idx], k);
        }
    }

    void clear(Node<TK> *x) {
        if (!x)
            return;
        if (!x->leaf)
            for (int i = 0; i <= x->count; ++i)
                clear(x->children[i]);
        delete x;
    }

    bool check(Node<TK> *x, int depth, int &leafLevel) const {
        if (!x)
            return true;
        if (x == root) {
            if (x->count < 1 || x->count > M - 1)
                return false;
        } else {
            int minKeys = t() - 1;
            if (x->count < minKeys || x->count > M - 1)
                return false;
        }
        if (x->leaf) {
            if (leafLevel < 0)
                leafLevel = depth;
            else if (leafLevel != depth)
                return false;
        }
        for (int i = 0; i + 1 < x->count; ++i)
            if (x->keys[i] >= x->keys[i + 1])
                return false;
        if (!x->leaf) {
            for (int i = 0; i <= x->count; ++i)
                if (!check(x->children[i], depth + 1, leafLevel))
                    return false;
        }
        return true;
    }

  public:
    BTree(int _M) : root(nullptr), M(_M), n(0) {}

    ~BTree() {
        clear(root);
        root = nullptr;
        n = 0;
    }

    bool search(TK k) const { return search(root, k) != nullptr; }

    void insert(TK k) {
        if (!root) {
            root = new Node<TK>(M);
            root->leaf = true;
            root->count = 0;
        }
        if (search(k))
            return;
        if (root->count == M - 1) {
            Node<TK> *s = new Node<TK>(M);
            s->leaf = false;
            s->count = 0;
            s->children[0] = root;
            splitChild(s, 0);
            int i = (s->keys[0] < k ? 1 : 0);
            insertNonFull(s->children[i], k);
            root = s;
        } else {
            insertNonFull(root, k);
        }
        ++n;
    }

    void remove(TK k) {
        if (!root)
            return;
        remove(root, k);
        if (root->count == 0) {
            Node<TK> *tmp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->children[0];
            delete tmp;
        }
        --n;
    }

    int height() const {
        if (!root)
            return 0;
        Node<TK> *cur = root;
        int h = 0;
        while (!cur->leaf) {
            cur = cur->children[0];
            ++h;
        }
        return h;
    }

    std::string toString(const std::string &sep = " ") const {
        std::vector<TK> elems;
        traverse(root, elems);
        std::ostringstream oss;
        for (size_t i = 0; i < elems.size(); ++i) {
            if (i)
                oss << sep;
            oss << elems[i];
        }
        return oss.str();
    }

    std::vector<TK> rangeSearch(TK a, TK b) const {
        std::vector<TK> all, res;
        traverse(root, all);
        for (auto &v : all)
            if (v >= a && v <= b)
                res.push_back(v);
        return res;
    }

    TK minKey() const {
        if (!root)
            throw std::runtime_error("Tree empty");
        Node<TK> *cur = root;
        while (!cur->leaf)
            cur = cur->children[0];
        return cur->keys[0];
    }

    TK maxKey() const {
        if (!root)
            throw std::runtime_error("Tree empty");
        Node<TK> *cur = root;
        while (!cur->leaf) {
            cur = cur->children[cur->count];
        }
        return cur->keys[cur->count - 1];
    }

    void clear() {
        clear(root);
        root = nullptr;
        n = 0;
    }

    int size() const { return n; }

    static BTree<TK> *build_from_ordered_vector(const std::vector<TK> &elems,
                                                int order) {
        BTree<TK> *t = new BTree<TK>(order);
        for (auto &v : elems)
            t->insert(v);
        return t;
    }

    bool check_properties() const {
        int leafLevel = -1;
        return check(root, 0, leafLevel);
    }
};

#endif // BTREE_H
