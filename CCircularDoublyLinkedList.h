#ifndef CCIRCULAR_DOUBLY_LINKED_LIST_H
#define CCIRCULAR_DOUBLY_LINKED_LIST_H

#include "CList.h"
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class CCircularDoublyLinkedList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d = T()) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node sentinel;
    int size;

public:
    CCircularDoublyLinkedList();
    ~CCircularDoublyLinkedList();

    int get_size() const { return size; }
    bool is_empty() const { return size == 0; }

    T front();
    T back();
    void push_front(T data);
    void push_back(T data);
    T pop_front();
    T pop_back();
    void insert(T data, int pos);
    void remove(int pos);
    T& operator[](int index);
    void sort();
    void reverse();
    void clear();
    bool is_empty();
    int get_size();
    bool is_sorted();
    void print();
    std::string name() { return "CCircularDoublyLinkedList"; }
};

// Constructor
template <typename T>
CCircularDoublyLinkedList<T>::CCircularDoublyLinkedList() : size(0) {
    sentinel.next = &sentinel;
    sentinel.prev = &sentinel;
}

// Destructor
template <typename T>
CCircularDoublyLinkedList<T>::~CCircularDoublyLinkedList() {
    clear();
}

// Front
template <typename T>
T CCircularDoublyLinkedList<T>::front() {
    if (is_empty()) throw std::runtime_error("List is empty");
    return sentinel.next->data;
}

// Back
template <typename T>
T CCircularDoublyLinkedList<T>::back() {
    if (is_empty()) throw std::runtime_error("List is empty");
    return sentinel.prev->data;
}

// Push Front
template <typename T>
void CCircularDoublyLinkedList<T>::push_front(T data) {
    Node* node = new Node(data);
    Node* first = sentinel.next;

    node->next = first;
    node->prev = &sentinel;

    sentinel.next = node;
    first->prev = node;

    size++;
}

// Push Back
template <typename T>
void CCircularDoublyLinkedList<T>::push_back(T data) {
    Node* node = new Node(data);
    Node* last = sentinel.prev;

    node->next = &sentinel;
    node->prev = last;

    last->next = node;
    sentinel.prev = node;

    size++;
}

// Pop Front
template <typename T>
T CCircularDoublyLinkedList<T>::pop_front() {
    if (is_empty()) throw std::runtime_error("List is empty");

    Node* node = sentinel.next;
    T data = node->data;

    sentinel.next = node->next;
    node->next->prev = &sentinel;

    delete node;
    size--;
    return data;
}

// Pop Back
template <typename T>
T CCircularDoublyLinkedList<T>::pop_back() {
    if (is_empty()) throw std::runtime_error("List is empty");

    Node* node = sentinel.prev;
    T data = node->data;

    sentinel.prev = node->prev;
    node->prev->next = &sentinel;

    delete node;
    size--;
    return data;
}

// Insert
template <typename T>
void CCircularDoublyLinkedList<T>::insert(T data, int pos) {
    if (pos < 0 || pos > size) throw std::out_of_range("Invalid position");

    Node* temp = &sentinel;
    for (int i = 0; i < pos; ++i)
        temp = temp->next;

    Node* nextNode = temp->next;
    Node* newNode = new Node(data);

    newNode->next = nextNode;
    newNode->prev = temp;

    temp->next = newNode;
    nextNode->prev = newNode;

    size++;
}

// Remove
template <typename T>
void CCircularDoublyLinkedList<T>::remove(int pos) {
    if (pos < 0 || pos >= size) throw std::out_of_range("Invalid position");

    Node* node = sentinel.next;
    for (int i = 0; i < pos; ++i)
        node = node->next;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    size--;
}

// Operator []
template <typename T>
T& CCircularDoublyLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
    Node* node = sentinel.next;
    for (int i = 0; i < index; ++i)
        node = node->next;
    return node->data;
}
// Get Size
template <typename T>
int CCircularDoublyLinkedList<T>::get_size() {
    return size;
}
// Is Empty
template <typename T>
bool CCircularDoublyLinkedList<T>::is_empty() {
    return size == 0;
}
// Sort
template <typename T>
void CCircularDoublyLinkedList<T>::sort() {
    if (size < 2) return;

    for (Node* i = sentinel.next; i != &sentinel; i = i->next) {
        for (Node* j = i->next; j != &sentinel; j = j->next) {
            if (i->data > j->data)
                std::swap(i->data, j->data);
        }
    }
}

// Reverse
template <typename T>
void CCircularDoublyLinkedList<T>::reverse() {
    Node* current = &sentinel;
    do {
        std::swap(current->next, current->prev);
        current = current->prev; // antes era next
    } while (current != &sentinel);
}

// Clear
template <typename T>
void CCircularDoublyLinkedList<T>::clear() {
    Node* current = sentinel.next;
    while (current != &sentinel) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    sentinel.next = &sentinel;
    sentinel.prev = &sentinel;
    size = 0;
}

// Is Sorted
template <typename T>
bool CCircularDoublyLinkedList<T>::is_sorted() {
    if (size < 2) return true;
    Node* current = sentinel.next;
    while (current->next != &sentinel) {
        if (current->data > current->next->data)
            return false;
        current = current->next;
    }
    return true;
}

// Print
template <typename T>
void CCircularDoublyLinkedList<T>::print() {
    Node* current = sentinel.next;
    while (current != &sentinel) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

#endif // CCIRCULAR_DOUBLY_LINKED_LIST_H
