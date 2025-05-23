#include "double.h"
#include "forward.h"
#include <iostream>

void testSimpleLinkedList();
void testDoubleLinkedList();
int main() {
    testSimpleLinkedList();
    testDoubleLinkedList();
    return 0;
}
void testSimpleLinkedList() {
    std::cout << "Forward Linked List" << std::endl;
    ForwardList<int> integers;
    for (int i = 0; i < 5; i++) {
        integers.push_front(2 * i);
    }
    integers.pop_front();
    ForwardList<int>::iterator ite;
    for (ite = integers.begin(); ite != integers.end(); ++ite)
        std::cout << *ite << " "; // 6 4 2 0
}
void testDoubleLinkedList() {
    std::cout << "Doubly Linked List" << std::endl;
    DoubleList<int> integers;
    for (int i = 0; i < 5; i++) {
        integers.push_back(2 * i); // 0 2 4 6 8
    }
    integers.pop_back(); // 0 2 4 6
    DoubleList<int>::iterator ite = integers.begin();
    ++ite;
    std::cout << *ite << " "; // 2
    ++ite;
    std::cout << *ite << " "; // 4
    --ite;
    std::cout << *ite << " "; // 2
}
