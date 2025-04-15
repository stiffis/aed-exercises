#include "CDoublyLinkedList.h"

int main () {
    CDoublyLinkedList<int> list;
    
    list.print();

    list.reverse();

    list.print();
    return 0;
}
