#ifndef CDOUBLYLINKEDLIST_H
#define CDOUBLYLINKEDLIST_H

#include "CList.h"
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

template <typename T> class CDoublyLinkedList : public List<T> {
  private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
    };
    // INFO: Attributes
    Node *head;
    Node *tail;
    int size;

  public:
    // INFO: Methods
    CDoublyLinkedList();
    ~CDoublyLinkedList();
    Node *getHead() { return head; }
    void setHead(Node *head) { this->head = head; }
    void setSize(int size) { this->size = size; }
    void setTail(Node *tail) { this->tail = tail; }
    T front() { return head->data; } // O(1)
    T back() { return tail->data; }  // O(1)
    void push_front(const T data) {
        Node *newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    void push_back(const T data) {
        Node *newNode = new Node(data);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    T pop_front() {
        if (head == nullptr) {
            return T();
        }
        Node *temp = head;
        T data = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return data;
    }
    T pop_back() {
        if (tail == nullptr) {
            return T();
        }
        Node *temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
        return data;
    }
    void insert(T val, int pos) {
        if (pos > size || pos < 0) {
            return;
        }
        if (head == nullptr) {
            Node *newNode = new Node(val);
            head = newNode;
            tail = newNode;
            size++;
            return;
        }
        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == size) {
            push_back(val);
            return;
        }
        Node *newNode = new Node(val);
        Node *temp = head;
        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }
    void remove(int x){
        int a = x;
    } // TODO: Implement and ask
    T &operator[](int pos) {
        if (pos >= size || pos < 0 || head == nullptr) {
            throw std::out_of_range("Indice fuera de rango"); // WARN: returns the defaul value(depends on the
                        // constructor)
        }
        Node *temp = head;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }
    bool is_empty() { return (size == 0); }
    int get_size() { return size; }
    void sort(){
        int a = 0;
    } // TODO: Implement and ask
    void clear() {
        Node *temp = head;
        while (temp != nullptr) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void reverse(){
        int a = 0;
    }
    std::string name() { return "CDoublyLinkedList"; }
    void print() {
        Node *temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

template <typename T>
CDoublyLinkedList<T>::CDoublyLinkedList()
    : head(nullptr), tail(nullptr), size(0) {}
template <typename T> CDoublyLinkedList<T>::~CDoublyLinkedList() { clear(); }
#endif // !CDOUBLYLINKEDLIST_H
// BUG:
/*
⠀ ／l
（ﾟ､ ｡ ７
⠀ l、ﾞ ~ヽ
  じしf_, )ノ ❤️
*/
