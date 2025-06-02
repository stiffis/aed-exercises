#include "btree.h"
#include "tester.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    BTree<int> *btree = new BTree<int>(3);
    int numbers[10] = {45, 75, 100, 36, 120, 70, 11, 111, 47, 114};
    for (int i = 0; i < 10; i++) {
        btree->insert(numbers[i]);
    }

    ASSERT(btree->toString(" ") == "11 36 45 47 70 75 100 111 114 120",
           "The function insert is not working");
    ASSERT(btree->height() == 2, "The function height is not working");
    for (int i = 0; i < 10; i = i + 2) {
        ASSERT(btree->search(numbers[i]) == true,
               "The function search is not working");
    }
    ASSERT(btree->minKey() == 11, "The function minKey is not working");
    std::cout << btree->maxKey() << "\n";
    ASSERT(btree->maxKey() == 120, "The function maxKey is not working");

    btree->remove(100);
    btree->remove(111);
    btree->remove(45);

    ASSERT(btree->toString(" ") == "11 36 47 70 75 114 120",
           "The function remove is not working");
    ASSERT(btree->height() == 1, "The function height is not working");

    btree->remove(114);
    btree->insert(40);

    ASSERT(btree->toString(" - ") == "11 - 36 - 40 - 47 - 70 - 75 - 120",
           "The function toString is not working");
    ASSERT(btree->height() == 2, "The function height is not working");

    btree->insert(125);
    btree->insert(115);

    ASSERT(btree->maxKey() == 125, "The function maxKey is not working");
    ASSERT(btree->search(47) == true, "The function search is not working");

    btree->remove(11);

    ASSERT(btree->search(11) == false, "The function search is not working");
    ASSERT(btree->minKey() == 36, "The function minKey is not working");
    ASSERT(btree->size() == 8, "The function size is not working");

    btree->clear();
    ASSERT(btree->size() == 0, "The function size is not working");
    ASSERT(btree->height() == 0, "The function height is not working");

    // TODO: agregar pruebas
    std::vector<int> elements = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    BTree<int> *btree2 = BTree<int>::build_from_ordered_vector(elements, 4);
    ASSERT(btree2->toString(",") ==
               "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20",
           "The function build_from_ordered_vector is not working");
    if (btree2->check_properties()) {
        cout << "El árbol 2 cumple con las propiedades de un árbol B." << endl;
    } else {
        cout << "El árbol 2 no cumple con las propiedades de un árbol B."
             << endl;
    }

    delete btree;
    delete btree2;

    return 0;
}
