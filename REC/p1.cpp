#include <iostream>
using namespace std;

class LinkedList {
  private:
    struct Node {
        int value;
        Node *next;
        Node(int val) : value(val), next(nullptr) {}
    };
    Node *head;
    Node *tail;
    int count;

  public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    void push_back(int val) {
        Node *newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    int pop_front() {
        if (head == nullptr)
            return -1;
        Node *temp = head;
        int val = temp->value;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        delete temp;
        count--;
        return val;
    }

    int size() const {
        return count;
    }
};

class TemperaturaBuffer {
    LinkedList lista;
    int capacidad;
    double suma;

public:
    TemperaturaBuffer(int k) : capacidad(k), suma(0) {}

    void agregarTemperatura(int temp) {
        if (lista.size() == capacidad) {
            int eliminado = lista.pop_front();
            suma -= eliminado;
        }
        lista.push_back(temp);
        suma += temp;
    }

    double calcularPromedio() const {
        if (lista.size() == 0) return 0.0;
        return suma / lista.size();
    }
};

int main() {
    int K;
    cout << "Ingrese K: ";
    cin >> K;

    TemperaturaBuffer buffer(K);

    while (true) {
        int temp;
        cout << "Ingrese temperatura: ";
        cin >> temp;
        if (temp == -1) {
            cout << "FIN";
            break;
        }

        buffer.agregarTemperatura(temp);
        cout << "Promedio: " << buffer.calcularPromedio() << "\n";
    }

    return 0;
}
