# Codigo
```cpp
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
```

## Explicación de la solución
La solución implementa una deque circular utilizando un arreglo dinámico. La clase `MyCircularDeque` tiene métodos para insertar y eliminar elementos tanto al frente como al final de la deque, así como métodos para obtener los elementos en el frente y el final, y para verificar si la deque está vacía o llena.
La deque circular se implementa utilizando un arreglo de tamaño `k`, donde `k` es la capacidad máxima de la deque. Los índices `front` y `rear` se utilizan para rastrear las posiciones del frente y el final de la deque, respectivamente. El tamaño actual de la deque se mantiene en la variable `size`. La operación de inserción y eliminación se realiza en tiempo constante O(1) utilizando operaciones de módulo para manejar el comportamiento circular del arreglo.
El método `insertFront` inserta un elemento al frente de la deque, moviendo el índice `front` hacia atrás y almacenando el valor en la nueva posición. El método `insertLast` inserta un elemento al final de la deque, moviendo el índice `rear` hacia adelante y almacenando el valor en la nueva posición. Los métodos `deleteFront` y `deleteLast` eliminan elementos del frente y del final de la deque, respectivamente, moviendo los índices correspondientes y decrementando el tamaño.
El método `insertLast` verifica si la deque está llena antes de insertar un elemento, y si está llena, devuelve `false`. De manera similar, los métodos `deleteFront` y `deleteLast` verifican si la deque está vacía antes de eliminar un elemento, y si está vacía, devuelven `false`. Los métodos `getFront` y `getRear` devuelven el valor en el frente y el final de la deque, respectivamente, o -1 si la deque está vacía.
El método `deleteFront` mueve el índice `front` hacia adelante y decrementa el tamaño de la deque. El método `deleteLast` mueve el índice `rear` hacia atrás y decrementa el tamaño de la deque. Ambos métodos devuelven `true` si la operación se realiza con éxito y `false` si no se puede realizar la operación (por ejemplo, si la deque está vacía).
El método `getFront` devuelve el valor en la posición del índice `front`, y el método `getRear` devuelve el valor en la posición del índice `rear`. Ambos métodos devuelven -1 si la deque está vacía.
El método `isEmpty` verifica si el tamaño de la deque es cero y devuelve `true` si está vacía, y `false` en caso contrario. El método `isFull` verifica si el tamaño de la deque es igual a su capacidad máxima y devuelve `true` si está llena, y `false` en caso contrario.
El método `getRear` devuelve el valor en la posición del índice `rear`, y el método `getFront` devuelve el valor en la posición del índice `front`. Ambos métodos devuelven -1 si la deque está vacía.
El método `isFull` verifica si el tamaño de la deque es igual a su capacidad máxima y devuelve `true` si está llena, y `false` en caso contrario. El método `isEmpty` verifica si el tamaño de la deque es cero y devuelve `true` si está vacía, y `false` en caso contrario.
La clase también incluye un destructor para liberar la memoria asignada dinámicamente al arreglo `data` cuando la instancia de la clase se destruye.

## Complejidad
La complejidad de tiempo para todas las operaciones (insertar al frente, insertar al final, eliminar del frente, eliminar del final, obtener el frente, obtener el final) es O(1) porque todas las operaciones se realizan en tiempo constante. Osea que no importa el tamaño de la deque, el tiempo que toma cada operación es constante. Ya que no hay bucles que dependan del tamaño de la deque.
La complejidad de espacio es O(k), donde k es la capacidad máxima de la deque, ya que se utiliza un arreglo de tamaño k para almacenar los elementos de la deque. Esto significa que el espacio utilizado por la deque es proporcional a su capacidad máxima.

## Gráfico explicativo de como funciona la estructura de datos
Se debe realizar un dibujo o grafico que explique como funciona la estructura de datos, como se comporta al insertar y eliminar elementos, y como se comporta al llegar a su capacidad maxima. No debe ser un flujo sino el mismo dibujo de la estructura en este caso dibujar el deque
### Dibujo
