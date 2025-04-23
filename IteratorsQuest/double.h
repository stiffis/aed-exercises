#ifndef DOUBLE_H
#define DOUBLE_H
// NodeDL is a node of the double linked list
#include <stdexcept>
template <typename T> struct NodeDL {
    T data;
    NodeDL *next;
    NodeDL *prev;
    NodeDL() : next(nullptr), prev(nullptr) {}
    NodeDL(T value) : data(value), next(nullptr), prev(nullptr) {}
};
// DoubleListIterator is an iterator of the double linked list
template <typename T> class DoubleListIterator {
    private:
        NodeDL<T> *current;
  public:
    DoubleListIterator() {
        current = nullptr;
    } // Constructor with no arguments
    DoubleListIterator(NodeDL<T> *current) {
        this->current = current;
    } // Constructor with a node
    DoubleListIterator<T> &operator++();    //++it
    DoubleListIterator<T> &operator++(int); // it++
    DoubleListIterator<T> &operator--();    //--it
    bool operator!=(const DoubleListIterator<T> &other);
    T operator*();
};
template<typename T> DoubleListIterator<T> &DoubleListIterator<T>::operator++() {
    if (current != nullptr) {
        current = current->next;
    }
    return *this;
}
template<typename T> DoubleListIterator<T> &DoubleListIterator<T>::operator++(int) {
    DoubleListIterator<T> temp = *this;
    ++(*this);
    return temp;
}
template<typename T> DoubleListIterator<T> &DoubleListIterator<T>::operator--() {
    if (current != nullptr) {
        current = current->prev;
    }
    return *this;
}
template<typename T> bool DoubleListIterator<T>::operator!=(const DoubleListIterator<T> &other) {
    return current != other.current;
}
template<typename T> T DoubleListIterator<T>::operator*() {
    return current->data;
}


// DoubleList is a double linked list
template <typename T> class DoubleList {
  public:
    typedef DoubleListIterator<T> iterator;

  private:
    NodeDL<T> *head;
    NodeDL<T> *tail;

  public:
    DoubleList() {
        head = nullptr;
        tail = nullptr;
    }
    /* new functions */
    iterator begin() {
        // Return an iterator pointing to the head of the list
        return iterator(head);
    }
    iterator end() {
        // Return an iterator pointing to the tail of the list
        return iterator(tail);
    }
    void push_back(T data) {
        // Create a new node
        NodeDL<T> *newNode = new NodeDL<T>(data);
        // If the list is empty, set head and tail to the new node
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // Otherwise, add the new node to the end of the list
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    T pop_back() {
        // If the list is empty, throw an exception
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        // Store the data of the tail node
        T data = tail->data;
        // Delete the tail node
        NodeDL<T> *temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr; // List is now empty
        }
        delete temp;
        return data;
    }
    ~DoubleList() {
        // Destructor to free the memory
        while (head != nullptr) {
            NodeDL<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
#endif
