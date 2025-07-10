#include "../RedBlackTree.h"
#include <iostream>
#include <vector>
#include <random>

int main() {
    RedBlackTree tree;
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Insertando valores..." << std::endl;
    for (int val : values) {
        tree.insert(val);
        std::cout << "Insertado: " << val << std::endl;
    }
    
    std::cout << "Árbol después de insertar:" << std::endl;
    tree.print();
    
    std::cout << "\nBuscando valores..." << std::endl;
    for (int val : values) {
        Node* found = tree.search(val);
        if (found) {
            std::cout << "Encontrado: " << val << std::endl;
        } else {
            std::cout << "NO encontrado: " << val << std::endl;
        }
    }
    
    std::cout << "\nEliminando algunos valores..." << std::endl;
    std::vector<int> toRemove = {3, 7, 1, 10};
    for (int val : toRemove) {
        std::cout << "Eliminando: " << val << std::endl;
        tree.remove(val);
    }
    
    std::cout << "Árbol después de eliminar:" << std::endl;
    tree.print();
    
    return 0;
}
