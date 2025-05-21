#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <sstream>
#include <vector>
#include "AVL_Node.h"
#include "AVL_Iterator.h"

template<typename T>
class AVLTree {
public:
    typedef AVLIterator<T> iterator;
    iterator begin(typename iterator::Type t) { return iterator(root, t); }
    iterator end()                          { return iterator(nullptr); }

    AVLTree() : root(nullptr) {}
    ~AVLTree() { if (root) root->killSelf(); }

    void insert(const T& v) {
        insertRec(root, v);
        rebuildBalanced();
    }

    bool find(const T& v) const { return findNode(root, v) != nullptr; }

    std::string getInOrder() const  { std::ostringstream oss; inOrderRec(root, oss);  return oss.str(); }
    std::string getPreOrder() const { std::ostringstream oss; preOrderRec(root, oss); return oss.str(); }
    std::string getPostOrder() const{ std::ostringstream oss; postOrderRec(root, oss);return oss.str(); }
    int height() const              { return root ? root->height : -1; }

    T minValue() const { if (!root) throw std::runtime_error("Árbol vacío"); return findMin(root)->data; }
    T maxValue() const { if (!root) throw std::runtime_error("Árbol vacío"); return findMax(root)->data; }
    bool isBalanced() const { return isBalancedRec(root); }
    int size() const        { return sizeRec(root); }

    void remove(const T& v) { removeRec(root, v); rebuildBalanced(); }

    T successor(const T& v) const    { return successorRec(v); }
    T predecessor(const T& v) const  { return predecessorRec(v); }
    void clear() { if (root) { root->killSelf(); root = nullptr; } }
    void displayPretty() const { print2DUtil(root, 0); }

private:
    NodeAVL<T>* root;

    void insertRec(NodeAVL<T>*& node, const T& v) {
        if (!node) node = new NodeAVL<T>(v);
        else if (v < node->data) insertRec(node->left, v);
        else insertRec(node->right, v);
    }

    void removeRec(NodeAVL<T>*& node, const T& v) {
        if (!node) return;
        if (v < node->data) removeRec(node->left, v);
        else if (v > node->data) removeRec(node->right, v);
        else {
            if (!node->left && !node->right) { delete node; node = nullptr; }
            else if (!node->left) { NodeAVL<T>* tmp = node; node = node->right; tmp->left = tmp->right = nullptr; delete tmp; }
            else if (!node->right) { NodeAVL<T>* tmp = node; node = node->left; tmp->left = tmp->right = nullptr; delete tmp; }
            else { NodeAVL<T>* succ = findMin(node->right); node->data = succ->data; removeRec(node->right, succ->data); }
        }
    }

    NodeAVL<T>* findNode(NodeAVL<T>* node, const T& v) const {
        if (!node) return nullptr;
        if (v == node->data) return node;
        if (v < node->data) return findNode(node->left, v);
        return findNode(node->right, v);
    }

    NodeAVL<T>* findMin(NodeAVL<T>* node) const { while (node->left) node = node->left; return node; }
    NodeAVL<T>* findMax(NodeAVL<T>* node) const { while (node->right) node = node->right; return node; }

    void inOrderRec(NodeAVL<T>* node, std::ostringstream& oss) const {
        if (!node) return;
        inOrderRec(node->left, oss);
        oss << node->data << " ";
        inOrderRec(node->right, oss);
    }
    void preOrderRec(NodeAVL<T>* node, std::ostringstream& oss) const {
        if (!node) return;
        oss << node->data << " ";
        preOrderRec(node->left,  oss);
        preOrderRec(node->right, oss);
    }
    void postOrderRec(NodeAVL<T>* node, std::ostringstream& oss) const {
        if (!node) return;
        postOrderRec(node->left,  oss);
        postOrderRec(node->right, oss);
        oss << node->data << " ";
    }

    int sizeRec(NodeAVL<T>* node) const { return node ? 1 + sizeRec(node->left) + sizeRec(node->right) : 0; }
    bool isBalancedRec(NodeAVL<T>* node) const {
        if (!node) return true;
        int hl = node->left  ? node->left->height  : -1;
        int hr = node->right ? node->right->height : -1;
        if (std::abs(hl - hr) > 1) return false;
        return isBalancedRec(node->left) && isBalancedRec(node->right);
    }

    void print2DUtil(NodeAVL<T>* node, int space) const {
        if (!node) return;
        space += 5;
        print2DUtil(node->right, space);
        std::cout << std::endl;
        for (int i = 5; i < space; ++i) std::cout << ' ';
        std::cout << node->data << "\n";
        print2DUtil(node->left, space);
    }

    void toSortedRec(NodeAVL<T>* n, std::vector<T>& v) const {
        if (!n) return;
        toSortedRec(n->left,  v);
        v.push_back(n->data);
        toSortedRec(n->right, v);
    }

    NodeAVL<T>* buildFromSorted(const std::vector<T>& v, int l, int r) {
        if (l > r) return nullptr;
        int m = l + (r - l) / 2;
        NodeAVL<T>* node = new NodeAVL<T>(v[m]);
        node->left  = buildFromSorted(v, l,   m - 1);
        node->right = buildFromSorted(v, m + 1, r);
        int hl = node->left  ? node->left->height  : -1;
        int hr = node->right ? node->right->height : -1;
        node->height = 1 + std::max(hl, hr);
        return node;
    }

    void rebuildBalanced() {
        std::vector<T> v;
        toSortedRec(root, v);
        if (root) { root->killSelf(); root = nullptr; }
        root = buildFromSorted(v, 0, static_cast<int>(v.size()) - 1);
    }

    T successorRec(const T& v) const {
        NodeAVL<T>* node = findNode(root, v);
        if (!node) throw std::runtime_error("Value not found");
        if (node->right) return findMin(node->right)->data;
        NodeAVL<T>* succ = nullptr;
        NodeAVL<T>* anc  = root;
        while (anc != node) {
            if (v < anc->data) { succ = anc; anc = anc->left; }
            else { anc = anc->right; }
        }
        if (!succ) throw std::runtime_error("No successor");
        return succ->data;
    }

    T predecessorRec(const T& v) const {
        NodeAVL<T>* node = findNode(root, v);
        if (!node) throw std::runtime_error("Value not found");
        if (node->left) return findMax(node->left)->data;
        NodeAVL<T>* pred = nullptr;
        NodeAVL<T>* anc  = root;
        while (anc != node) {
            if (v > anc->data) { pred = anc; anc = anc->right; }
            else { anc = anc->left; }
        }
        if (!pred) throw std::runtime_error("No predecessor");
        return pred->data;
    }
};

#endif // AVL_H
