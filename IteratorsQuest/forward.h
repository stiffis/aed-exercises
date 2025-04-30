#ifndef FORWARD_H
#define FORWARD_H
// NodeFL is a node of the forward list
#include <stdexcept>
template <typename T> struct NodeFL {
    T data;
    NodeFL *next;
    NodeFL() : next(nullptr) {}
    NodeFL(T value) : data(value), next(nullptr) {}
};
// ForwardListIterator is an iterator of the forward list
template <class T> class ForwardListIterator {
  private:
    NodeFL<T> *current;

  public:
    ForwardListIterator() : current(nullptr) {}; // Constructor with no arguments
    ForwardListIterator(NodeFL<T> *current) : current(current) {}; // Constructor with a node
    ForwardListIterator<T> &operator++();    //++it
    ForwardListIterator<T> &operator++(int); // it++
    bool operator!=(const ForwardListIterator<T> &other); // Overload !=
    T operator*(); // Overload *
};
template <typename T> ForwardListIterator<T> &ForwardListIterator<T>::operator++() {
    if (current != nullptr) {
        current = current->next;
    }
    return *this;
}
template <typename T> ForwardListIterator<T> &ForwardListIterator<T>::operator++(int) {
    ForwardListIterator<T> temp = *this;
    ++(*this);
    return temp;
}
template <typename T> bool ForwardListIterator<T>::operator!=(const ForwardListIterator<T> &other) {
    return current != other.current;
}
template <typename T> T ForwardListIterator<T>::operator*() {
    return current->data;
}

// ForwardList is a simple linked list
template <typename T> class ForwardList {
  public:
    typedef ForwardListIterator<T> iterator;

  private:
    NodeFL<T> *head;

  public:
    ForwardList() : head(nullptr) {}
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }
    void push_front(T data) {
        NodeFL<T> *newNode = new NodeFL<T>(data);
        newNode->next = head;
        head = newNode;
    }
    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        NodeFL<T> *temp = head;
        T data = head->data;
        head = head->next;
        delete temp;
        return data;
    }
    ~ForwardList() {
        while (head != nullptr) {
            NodeFL<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
#endif
// PERF: O(purr)
/*
⠀ ／l
（ﾟ､ ｡ ７
⠀ l、ﾞ ~ヽ
  じしf_, )ノ ❤️
*/
