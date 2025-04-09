#include "CForwardList.h"
#include "CDoublyLinkedList.h"
#include "CList.h"
#include <iostream>

void test(List<int>* list){
    std::cout << "*** Testing " << list->name() << "  *******" << std::endl;
    if (list->is_empty()==true) {
        std::cout << "Correctly empty" << std::endl;
    }else {
        std::cout << "Incorrectly empty" << std::endl;
    }
    if (list->get_size()==0) {
        std::cout << "Correctly size" << std::endl;
    }else {
        std::cout << "Incorrectly size" << std::endl;
    }
    list->push_front(5);
    list->push_front(10);
    if (list->pop_front()==10) {
        std::cout << "Correctly pop_front" << std::endl;
    }else {
        std::cout << "Incorrectly pop_front" << std::endl;
    }
    list->push_back(20);
    list->push_back(15);
    if (list->pop_back()==15) {
        std::cout << "Correctly pop_back" << std::endl;
    }else {
        std::cout << "Incorrectly pop_back" << std::endl;
    }
    list->push_back(30);
    list->push_back(8);
    list->insert(12, 2);
    if ((*list)[2]==12) {
        std::cout << "Correctly insert" << std::endl;
    }else {
        std::cout << "Incorrectly insert" << std::endl;
    }
    list->push_back(10);
    list->push_front(3);
    //ASSERT(list->is_sorted() == false);
    //list->sort();
    //ASSERT(list->is_sorted() == true);
    list->clear();
    if (list->is_empty()==true) {
        std::cout << "Correctly empty" << std::endl;
    }else { 
        std::cout << "Incorrectly empty" << std::endl;
    }
    delete list;
    std::cout << "Deleted list" << std::endl;
    std::cout << "***************" << std::endl;
}


int main () {
    List<int> *forward = new CForwardList<int>();
    test(forward);

    List<int> *doble = new CDoublyLinkedList<int>();
    test(doble);

    return 0;
}
