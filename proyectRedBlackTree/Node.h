#ifndef NODE_H
#define NODE_H
enum Color { RED, BLACK };
struct Node {
    int data;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(int val)
        : data(val), color(RED), left(nullptr), right(nullptr),
          parent(nullptr) {}
};
#endif // NODE_H
