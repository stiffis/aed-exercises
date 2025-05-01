#include "bst.h"
#include <iostream>

int main () {
    BST<int> tree;
    //Separar memoria
    int size, cols;
    cols = size = 3;
    int* array = new int[cols];
    array[0] = 1;
    array[1] = 3;
    array[2] = 5;
    tree.buildBST(array, cols);
    tree.printTree();
    Node<int>* root = tree.getRoot();
    std::cout << "Root: " << root->data << std::endl;
    //fin test1
    //test2
    std::cout << "In-order traversal: ";
    tree.inOrder();
    std::cout << std::endl;
    //test3: iterator test
    //for (auto it = tree.begin(); it != tree.end(); ++it) {
    //    std::cout << *it << " ";
    //}
    auto it = tree.begin();
    while (it != tree.end()) {
        std::cout << *it << " ";
        ++it;
    }
    delete[] array;
    return 0;
}
