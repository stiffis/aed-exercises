#include "AVL.h"
#include "HashTable.h"
#include "tester.h"
#include <iostream>
#include <string>
using namespace std;

void test_avl() {
    AVLTree<int> *avl = new AVLTree<int>();
    avl->insert(35);
    avl->insert(30);
    avl->insert(27);
    avl->insert(11);
    avl->insert(16);
    avl->insert(100);
    avl->insert(50);
    avl->insert(91);
    avl->insert(73);
    avl->insert(5);

    ASSERT(avl->isBalanced() == true, "The avl is not working");
    ASSERT(avl->height() == 3, "The avl is not working");
    ASSERT(avl->getInOrder() == "5 11 16 27 30 35 50 73 91 100 ",
           "The avl is not working");
    ASSERT(avl->minValue() == 5, "The function minValue is not working");
    ASSERT(avl->maxValue() == 100, "The function maxValue is not working");
    ASSERT(avl->successor(5) == 11, "The function successor is not working");
    ASSERT(avl->successor(27) == 30, "The function successor is not working");
    ASSERT(avl->successor(50) == 73, "The function successor is not working");
    ASSERT(avl->predecessor(100) == 91,
           "The function predecessor is not working");
    ASSERT(avl->predecessor(35) == 30,
           "The function predecessor is not working");
    ASSERT(avl->predecessor(16) == 11,
           "The function predecessor is not working");

    /*-----------------------iterators---------------------------------*/
    string result = "";
    AVLTree<int>::iterator ite = avl->begin(AVLIterator<int>::Type::PreOrder);
    while (ite != avl->end()) {
        result += std::to_string(*ite) + " ";
        ++ite;
    }
    ASSERT(result == avl->getPreOrder(),
           "The PreOrder iterator is not working");
    ASSERT(result == avl->getPreOrder(),
           "The PreOrder iterator is not working");
    ASSERT(result == avl->getPreOrder(),
           "The PreOrder iterator is not working");

    result = "";
    ite = avl->begin(AVLIterator<int>::Type::PostOrder);
    while (ite != avl->end()) {
        result += std::to_string(*ite) + " ";
        ++ite;
    }
    ASSERT(result == avl->getPostOrder(),
           "The PostOrder iterator is not working");
    ASSERT(result == avl->getPostOrder(),
           "The PostOrder iterator is not working");
    ASSERT(result == avl->getPostOrder(),
           "The PostOrder iterator is not working");
    /*---------------------------------------------------------------*/

    avl->remove(30);
    avl->remove(35);
    avl->remove(100);
    ASSERT(avl->height() == 2, "The avl is not working");
    ASSERT(avl->getPreOrder() == "27 11 5 16 73 50 91 ",
           "The avl is not working");

    delete avl;
}

void test_hash() {
    HashTable<string, float> notas;
    notas.insert("Nancy", 18);
    notas.insert("Jorge", 10);
    notas.insert("Maria", 15);
    notas.insert("Pedro", 20);
    notas.insert("Teofilo", 16);
    notas.insert("Cecilia", 14);
    notas.insert("Marcos", 11);
    notas.insert(pair<string, float>("Ricardo", 12));
    notas.insert(pair<string, float>("Dina", 8));
    notas.insert(pair<string, float>("Ana", 19));
    notas.insert(pair<string, float>("Cesar", 13));
    notas.insert(pair<string, float>("Patricia", 17));

    ASSERT(notas.getSize() == 12, "The hash table is not working");
    ASSERT(notas.find("Marcos") == true, "The hash table is not working");
    ASSERT(notas.find("Heider") == false, "The hash table is not working");
    ASSERT(notas["Marcos"] == 11, "The hash table is not working");
    notas["Marcos"] = 7;
    ASSERT(notas.at("Marcos") == 7, "The hash table is not working");

    /*-----------------------iterator---------------------------------*/
    string result = "";
    HashTable<string, float>::iterator iteh = notas.begin();
    while (iteh != notas.end()) {
        result += std::to_string((*iteh).first) + " ";
        ++iteh;
    }
    ASSERT(result == "Nancy Jorge Maria Pedro Teofilo Cecilia Marcos Ricardo "
                     "Dina Ana Cesar Patricia ",
           "The hash table is not working");
    ASSERT(result == "Nancy Jorge Maria Pedro Teofilo Cecilia Marcos Ricardo "
                     "Dina Ana Cesar Patricia ",
           "The hash table is not working");
    ASSERT(result == "Nancy Jorge Maria Pedro Teofilo Cecilia Marcos Ricardo "
                     "Dina Ana Cesar Patricia ",
           "The hash table is not working");
    /*---------------------------------------------------------------*/

    ASSERT(notas.remove("Heider") == false, "The hash table is not working");
    ASSERT(notas.remove("Marcos") == true, "The hash table is not working");
    ASSERT(notas.find("Marcos") == false, "The hash table is not working");
}

int main(int argc, char const *argv[]) {
    test_hash();
    test_avl();
    return 0;
}
