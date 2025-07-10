#ifndef BENCHMARKREDBLACKTREE_H
#define BENCHMARKREDBLACKTREE_H

#include "../Node.h"
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

class RedBlackTree {
  private:
    Node *root;

    // Benchmark storage: pares (tiempo_microsegundos, tamaño_entrada)
    std::vector<std::pair<long long, int>> benchmarkInsertData;
    std::vector<std::pair<long long, int>> benchmarkRemoveData;
    std::vector<std::pair<long long, int>> benchmarkPrintData;
    std::vector<std::pair<long long, int>> benchmarkLeftRotateData;
    std::vector<std::pair<long long, int>> benchmarkRightRotateData;
    std::vector<std::pair<long long, int>> benchmarkSearchData;

    int nodeCount = 0;

    Node *minimum(Node *node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Private Left Rotation
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

    // Private Right Rotation
    void rightRotate(Node *y) {
        if (y == nullptr || y->left == nullptr)
            return;
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
                        benchmarkLeftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    benchmarkRightRotate(z->parent->parent);
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
                        benchmarkRightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    benchmarkLeftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void fixDelete(Node *x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    benchmarkLeftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr)
                            w->left->color = BLACK;
                        w->color = RED;
                        benchmarkRightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    benchmarkLeftRotate(x->parent);
                    x = root;
                }
            } else {
                Node *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    benchmarkRightRotate(x->parent);
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
                        benchmarkLeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    benchmarkRightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) {
            x->color = BLACK;
        }
    }

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

    void deleteNode(Node *z) {
        if (z == nullptr)
            return;

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
                if (x != nullptr)
                    x->parent = y;
            } else {
                if (x != nullptr)
                    x->parent = y->parent;
                transplant(y, y->right);
                if (y->right != nullptr)
                    y->right->parent = y;
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK && x != nullptr)
            fixDelete(x);

        delete z;
    }

    void printHelper(Node *root, int space) {
        constexpr int COUNT = 10;
        if (root == nullptr)
            return;
        space += COUNT;
        printHelper(root->right, space);
        std::cout << std::endl;
        for (int i = COUNT; i < space; ++i)
            std::cout << " ";
        std::cout << root->data << "(" << ((root->color == RED) ? "R" : "B")
                  << ")" << std::endl;
        printHelper(root->left, space);
    }

  public:
    RedBlackTree() : root(nullptr), nodeCount(0) {}

    int size() const { return nodeCount; }

    // Public insert with timing
    void insert(int val) {
        auto start = std::chrono::high_resolution_clock::now();

        Node *newNode = new Node(val);
        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        newNode->parent = y;
        if (y == nullptr)
            root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);

        nodeCount++;

        auto end = std::chrono::high_resolution_clock::now();
        long long duration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        benchmarkInsertData.emplace_back(duration, nodeCount);
    }

    // Public remove with timing
    void remove(int val) {
        auto start = std::chrono::high_resolution_clock::now();

        Node *z = root;
        while (z != nullptr) {
            if (val < z->data)
                z = z->left;
            else if (val > z->data)
                z = z->right;
            else {
                deleteNode(z);
                nodeCount--;
                auto end = std::chrono::high_resolution_clock::now();
                long long duration =
                    std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                          start)
                        .count();
                benchmarkRemoveData.emplace_back(duration, nodeCount);
                return;
            }
        }
        std::cout << "Node with value " << val << " not found in the tree."
                  << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        long long duration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();
        benchmarkRemoveData.emplace_back(duration, nodeCount);
    }

    // Search function with timing
    Node *search(int val) {
        auto start = std::chrono::high_resolution_clock::now();
        
        Node *current = root;
        Node *result = nullptr;
        
        while (current != nullptr) {
            if (val < current->data)
                current = current->left;
            else if (val > current->data)
                current = current->right;
            else {
                result = current;
                break;
            }
        }
        
        // Record search time regardless of success or failure
        auto end = std::chrono::high_resolution_clock::now();
        long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        benchmarkSearchData.emplace_back(duration, nodeCount);
        
        return result;
    }

    // Public print con timing
    void print() {
        auto start = std::chrono::high_resolution_clock::now();
        printHelper(root, 0);
        auto end = std::chrono::high_resolution_clock::now();
        long long duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        benchmarkPrintData.emplace_back(duration, nodeCount);
    }

    // Public Left Rotate con timing
    void benchmarkLeftRotate(Node *x) {
        auto start = std::chrono::high_resolution_clock::now();
        leftRotate(x);
        auto end = std::chrono::high_resolution_clock::now();
        long long duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        benchmarkLeftRotateData.emplace_back(duration, nodeCount);
    }

    // Public Right Rotate con timing
    void benchmarkRightRotate(Node *y) {
        auto start = std::chrono::high_resolution_clock::now();
        rightRotate(y);
        auto end = std::chrono::high_resolution_clock::now();
        long long duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        benchmarkRightRotateData.emplace_back(duration, nodeCount);
    }

    // Getters para datos de benchmark
    const std::vector<std::pair<long long, int>> &getInsertBenchmark() const {
        return benchmarkInsertData;
    }
    const std::vector<std::pair<long long, int>> &getRemoveBenchmark() const {
        return benchmarkRemoveData;
    }
    const std::vector<std::pair<long long, int>> &getPrintBenchmark() const {
        return benchmarkPrintData;
    }
    const std::vector<std::pair<long long, int>> &
    getLeftRotateBenchmark() const {
        return benchmarkLeftRotateData;
    }
    const std::vector<std::pair<long long, int>> &
    getRightRotateBenchmark() const {
        return benchmarkRightRotateData;
    }
    const std::vector<std::pair<long long, int>> &
    getSearchBenchmark() const {
        return benchmarkSearchData;
    }
};

#endif // BENCHMARKREDBLACKTREE_H
