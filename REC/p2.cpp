// p2.cpp
#include <iostream>
#include <string>
using namespace std;

class BST {
  private:
    struct Node {
        string key;
        int stock;
        Node *left;
        Node *right;
        Node(string _key, int _stock) : key(_key), stock(_stock), left(nullptr), right(nullptr) {}
    };
    Node *root;

    void insert(Node *&node, string key, int stock) {
        if (node == nullptr) {
            node = new Node(key, stock);
        } else if (key < node->key) {
            insert(node->left, key, stock);
        } else if (key > node->key) {
            insert(node->right, key, stock);
        } else {
            node->stock += stock;
        }
    }

    void inorderMerge(Node* node, BST &other) {
        if (!node) return;
        inorderMerge(node->left, other);
        other.insert(node->key, node->stock);
        inorderMerge(node->right, other);
    }

    void inorderPrint(Node* node) {
        if (!node) return;
        inorderPrint(node->left);
        cout << "Producto: " << node->key << " Stock: " << node->stock << "\n";
        inorderPrint(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(string key, int stock) {
        insert(root, key, stock);
    }

    void merge(BST &other) {
        inorderMerge(root, other);
    }

    void print() {
        inorderPrint(root);
    }
};

int main() {
    BST bst1, bst2;

    /*bst1.insert(40, 8);
    bst1.insert(20, 4);
    bst1.insert(10, 5);
    bst1.insert(30, 3);
    bst1.insert(50, 12);
    bst1.insert(60, 4);
    
    bst2.insert(40, 2);
    bst2.insert(21, 5);
    bst2.insert(30, 4);
    bst2.insert(60, 1);*/
    
    bst1.insert("D01", 8);
    bst1.insert("B10", 4);
    bst1.insert("A01", 5);
    bst1.insert("C06", 3);
    bst1.insert("D05", 12);
    bst1.insert("E01", 4);
    
    bst2.insert("D01", 2);
    bst2.insert("B15", 5);
    bst2.insert("C06", 4);
    bst2.insert("E01", 1);
    
    bst1.merge(bst2);

    cout << "Inventario fusionado:\n";
    bst2.print();

    return 0;
}