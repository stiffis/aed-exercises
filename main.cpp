#include <cassert>
#include <iostream>
#include "tester.h"
#include "CForwardList.h"
#include "CDoublyLinkedList.h"
#include "CCircularDoublyLinkedList.h"

using namespace std;

void test(List<int>* list){   
    cout<<"*** Testing "<<list->name()<<"  *******"<<endl; 
    assert(list->is_empty() == true);
    assert(list->get_size() == 0);    
    list->push_front(5);
    list->push_front(10);
    assert(list->pop_front() == 10);
    list->push_back(20);
    list->push_back(15);
    assert(list->pop_back() == 15);
    list->push_back(30);
    list->push_back(8);
    list->insert(12, 2);
    assert((*list)[2] == 12);    
    list->push_back(10);
    list->push_front(3);
    //ASSERT(list->is_sorted() == false);
    //list->sort();
    //ASSERT(list->is_sorted() == true);
    list->clear();
    assert(list->is_empty() == true);
    delete list;
}

int main()
{    
    List<int> *forward = new CForwardList<int>();
    test(forward);

    List<int> *doble = new CDoublyLinkedList<int>();
    test(doble);

    List<int> *circular = new CDoublyLinkedList<int>();
    test(circular);

    return 0;
}
