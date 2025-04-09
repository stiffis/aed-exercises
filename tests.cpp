#include "CForwardList.h"

#include <iostream>

int main () {
    CForwardList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);


    list.print();

    std::cout << "head: " << list.front() << std::endl;
    std::cout << "tail: " << list.back() << std::endl;
    return 0;
}
