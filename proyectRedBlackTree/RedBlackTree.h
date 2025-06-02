// bajo este codigo quiero que me ayudes a "modificarlo" este codigo para
// realizar benchmark empiricos de las funciones más importantes , se creará un
// arbol de prueba y cada vez que se haga un insert , delete, print o rotacion
// derecha o izquierda se medirá el tiempo que tardó en realizar dicha tarea a
// vs b; donde a representa el tiempo de ejecucion de la funcoin y b el tamaño
// de la entrada ya sea para un insert, delete, print o ratacion.
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Node.h"
#include <iostream>
class RedBlackTree {
  private:
    Node *root;
    // INFO:  Find the minimum node in a subtree
    Node *minimum(Node *node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    // INFO: Left Rotation
    void leftRotate(Node *x) {
        if (x == nullptr || x->right == nullptr)
            return;
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    // INFO: RIGHT Rotation
    void rightRotate(Node *y) {
        if (y == nullptr || y->left == nullptr) {
            return;
        }
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }
    // INFO: Fix violations after inserting a Node
    void fixInsert(Node *z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node *y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;

                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node *y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    // INFO: Fix violations after deleting a Node
    void fixDelete(Node *x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) {
                            w->left->color = BLACK;
                        }
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) {
                        w->right->color = BLACK;
                    }
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr)
                            w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) {
            x->color = BLACK;
        }
    }
    // INFO: Transplant function used in deletion
    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }
    // INFO: Delete a Node
    void deleteNode(Node *z) {
        if (z == nullptr) {
            return;
        }
        Node *y = z;
        Node *x = nullptr;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr) {
                    x->parent = y;
                }
            } else {
                if (x != nullptr) {
                    x->parent = y->parent;
                }
                transplant(y, y->right);
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
                y->right = z->right;
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) {
                y->left->parent = y;
            }
            y->color = z->color;
        }
        if (yOriginalColor == BLACK && x != nullptr) {
            fixDelete(x);
        }
        delete z;
    }
    // INFO: Print the tree structure
    void printHelper(Node *root, int space) {
        constexpr int COUNT = 10; // Space between levels
        if (root == nullptr) {
            return;
        }
        space += COUNT;
        printHelper(root->right, space);
        std::cout << std::endl;
        for (int i = COUNT; i < space; ++i) {
            std::cout << " ";
        }
        std::cout << root->data << "(" << ((root->color == RED) ? "R" : "B")
                  << ")" << std::endl;
        printHelper(root->left, space);
    }

  public:
    RedBlackTree() : root(nullptr) {}
    // INFO: Insert a Node
    void insert(int val) {
        Node *newNode = new Node(val);
        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        newNode->parent = y;
        if (y == nullptr) {
            root = newNode;
        } else if (newNode->data < y->data) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }
        fixInsert(newNode);
    }
    // INFO: Delete a Node by value
    void remove(int val) {
        Node *z = root;
        while (z != nullptr) {
            if (val < z->data) {
                z = z->left;
            } else if (val > z->data) {
                z = z->right;
            } else {
                deleteNode(z);
                return;
            }
        }
        std::cout << "Node with value " << val << " not found in the tree."
                  << std::endl;
    }
    // INFO: Search for a Node by value
    Node *search(int val) {
        Node *current = root;
        while (current != nullptr) {
            if (val < current->data) {
                current = current->left;
            } else if (val > current->data) {
                current = current->right;
            } else {
                return current; // Node found
            }
        }
        return nullptr; // Node not found
    }
    // INFO: Print the tree structure
    void print() { printHelper(root, 0); }
};
#endif // !REDBLACKTREE_H
