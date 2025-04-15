#ifndef CCIRCULAR_DOUBLY_LINKED_LIST_H
#define CCIRCULAR_DOUBLY_LINKED_LIST_H
template<typename T>
class CCircularDoublyLikedList {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
    };
    // INFO: Attributes
    Node *sentinel = new Node(0); 
    Node *head;
    Node *tail;
    int size;
    
public:
    CCircularDoublyLikedList();
    ~CCircularDoublyLikedList();

};

template<typename T>
CCircularDoublyLikedList<T>::CCircularDoublyLikedList() {
        
}

template<typename T>
CCircularDoublyLikedList<T>::~CCircularDoublyLikedList() {
    
}
#endif // !CCIRCULAR_DOUBLY_LINKED_LIST_H
// PERF: 
/*
⠀ ／l
（ﾟ､ ｡ ７
⠀ l、ﾞ ~ヽ
  じしf_, )ノ ❤️
*/
