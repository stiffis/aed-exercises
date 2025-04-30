#include <iostream>
using namespace std;

class MyCircularDeque {
private:
    int* data;       
    int front;       
    int rear;        
    int size;        
    int capacity;    

public:
    
    MyCircularDeque(int k) : front(0), rear(k - 1), size(0), capacity(k) {
        data = new int[k]; 
    }

    // Inserta un valor en el frente de la deque
    bool insertFront(int value) {
        if (isFull()) return false; // No se puede insertar si está llena
        front = (front - 1 + capacity) % capacity; // Mueve el frente hacia atrás
        data[front] = value; // Inserta el valor en la nueva posición del frente
        size++; // Incrementa el tamaño
        return true;
    }

    // Inserta un valor en el final de la deque
    bool insertLast(int value) {
        if (isFull()) return false; // No se puede insertar si está llena
        rear = (rear + 1) % capacity; // Mueve el final hacia adelante
        data[rear] = value; // Inserta el valor en la nueva posición del final
        size++; // Incrementa el tamaño
        return true;
    }

    // Elimina un elemento del frente de la deque
    bool deleteFront() {
        if (isEmpty()) return false; // No se puede eliminar si está vacía
        front = (front + 1) % capacity; // Mueve el frente hacia adelante
        size--; // Decrementa el tamaño
        return true;
    }

    // Elimina un elemento del final de la deque
    bool deleteLast() {
        if (isEmpty()) return false; // No se puede eliminar si está vacía
        rear = (rear - 1 + capacity) % capacity; // Mueve el final hacia atrás
        size--; // Decrementa el tamaño
        return true;
    }

    // Obtiene el elemento en el frente de la deque
    int getFront() {
        if (isEmpty()) return -1; // Devuelve -1 si está vacía
        return data[front]; // Devuelve el valor en el frente
    }

    // Obtiene el elemento en el final de la deque
    int getRear() {
        if (isEmpty()) return -1; // Devuelve -1 si está vacía
        return data[rear]; // Devuelve el valor en el final
    }

    // Verifica si la deque está vacía
    bool isEmpty() {
        return size == 0;
    }

    // Verifica si la deque está llena
    bool isFull() {
        return size == capacity;
    }

    // Destructor: libera la memoria asignada dinámicamente
    ~MyCircularDeque() {
        delete[] data;
    }
};
