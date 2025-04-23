#ifndef CFORWARDLIST_H
#define CFORWARDLIST_H

#include "CList.h"
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

template <typename T> class CForwardList : public List<T> {
  private:
    struct Node {
        T data;
        Node *next;
        Node(const T &data) : data(data), next(nullptr) {}
    };
    // INFO: Attributes
    Node *head;
    int size;

  public:
    // INFO: Methods
    CForwardList();
    ~CForwardList();
    Node *getHead() { return head; }
    void setHead(Node *head) { this->head = head; }
    void setSize(int size) { this->size = size; }
    T front() { return head->data; } // PERF: O(1)
    T back() {                       // PERF: O(n)
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }
    void push_front(T data) { // PERF: O(1)
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        size++;
    }
    void push_back(T data) { // PERF: O(n)
        Node *newNode = new Node(data);
        Node *temp = head;
        if (head == nullptr) {
            head = newNode;
            size++;
            return;
        }
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        size++;
    }

    T pop_front() { // PERF: O(1)
        if (head == nullptr) {
            return T();
        }
        Node *temp = head;
        head = head->next;
        T data = temp->data;
        delete temp;
        size--;
        return data;
    }

    T pop_back() { // PERF: O(n)
        if (head == nullptr) {
            return T();
        }
        Node *temp = head;
        Node *prev = nullptr;
        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }
        T data = temp->data;
        delete temp;
        if (prev != nullptr) {
            prev->next = nullptr;
        } else {
            head = nullptr;
        }
        size--;
        return data;
    }

    void insert(T data, int pos) { // PERF: O(n)
        if (pos == 0) {
            push_front(data);
            return;
        }
        Node *newNode = new Node(data);
        Node *temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }
    void remove(int pos) { // WARN: NOT SURE O(n)
        if (pos < 0 || pos >= size) {
            throw std::out_of_range("Index out of range");
        }

        if (pos == 0) {
            pop_front();
            return;
        }

        Node *temp = head;
        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }

        Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;
    }
    T &operator[](int index) { // PERF: O(n)
        Node *temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    bool is_empty() { return size == 0; } // PERF: O(1)
    int get_sizeAux(Node* node){
        if (node == nullptr) {
            return 0;
        }
        return 1 + get_sizeAux(node->next);
    }
    int get_size() { 
        //return size; 
        return get_sizeAux(head);
    }
    void sort() {                         // WARN: NOT SURE
        Node *temp = head;
        Node *temp2 = nullptr;
        T data;
        if (head == nullptr) {
            return;
        }
        while (temp != nullptr) {
            temp2 = temp->next;
            while (temp2 != nullptr) {
                if (temp->data > temp2->data) {
                    data = temp->data;
                    temp->data = temp2->data;
                    temp2->data = data;
                }
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    void clear() { // PERF: O(n)
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    void reverse() { // PERF: O(n)
        Node *current = head;
        Node *prev = nullptr;
        Node *next = nullptr;
        if (head == nullptr) {
            return;
        }

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    bool is_sortedAux(Node *node, Node *next) {
        if (node == nullptr || next == nullptr) {
            return true;
        } else if (node->data < next->data) {
            return is_sortedAux(next, next->next);
        }
        return false;
    }
    bool is_sorted() { // PERF: O(n)
        /*Node *temp = head;
        if (head == nullptr) {
            return true;
        }
        while (temp->next != nullptr) {
            if (temp->data > temp->next->data) {
                return false;
            }
            temp = temp->next;
        }
        return true;
        */
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        return is_sortedAux(head, head->next);
    }
    void print() { // PERF: O(n)
        Node *temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    std::string name() { return "CForwardList"; } // PERF: O(1)
};

template <typename T>
CForwardList<T>::CForwardList() : head(nullptr), size(0) {}

template <typename T> CForwardList<T>::~CForwardList() { clear(); }
#endif // CFORWARDLIST_H
// PERF:
/*
⠀ ／l
（ﾟ､ ｡ ７
⠀ l、ﾞ ~ヽ
  じしf_, )ノ ❤️
*/
