#ifndef CHAINHASH_H
#define CHAINHASH_H
#include <forward_list>
#include <ostream>
#include <string>
#include <unordered_map> // Usado para hallar el hash de una cadena
#include <vector>

using namespace std;

const float maxFillfactor = 0.7;
const int maxColision = 4;

template <typename TK, typename TV> class ChainHash {
  private:
    struct Entry {
        TK key;
        TV value;
        Entry(TK k, TV v) {
            key = k;
            value = v;
        }
        friend ostream &operator<<(ostream &os, const Entry &e) {
            os << "[" << e.key << ":" << e.value << "]";
            return os;
        }
    };
    forward_list<Entry> *array; // Array de listas enlazadas, osea de los cubos
    int size;                   // n° de cubos
    int capacity;               // pares totales acumulados
    int bucketCount;            // n° de cubos ocupados

  public:
    ChainHash(int _capacity = 10) {
        array = new forward_list<Entry>[_capacity];
        capacity = _capacity;
        size = 0;
        bucketCount = 0;
    }
    ~ChainHash() { delete[] array; }

    void set(TK key, TV value) {
        if (fillFactor() >=
            maxFillfactor) // Si el factor de llenado es mayor que el máximo,
                           // realiza un rehashing
            rehashing();

        int hashCode = getHashCode(key); // Obtiene el código hash de la clave
        int index =
            hashCode % capacity; // Calcula el índice del bucket en base al hash

        auto &list = array[index]; // Accede a la lista de ese bucket
        for (auto &e :
             list) { // Recorre la lista para verificar si ya existe la clave
            if (e.key == key) {
                e.value = value; // Si la clave ya existe, se actualiza el valor
                return;
            }
        }

        list.push_front(Entry(
            key,
            value)); // Si la clave no existe, se inserta al inicio de la lista
        size++;

        if (list.size() == 1) { // Si la lista estaba vacía, incrementamos el
                                // contador de cubos ocupados
            ++bucketCount;
        }

        if (list.size() > maxColision) { // Si hay demasiadas colisiones en la
                                         // lista, se realiza un rehashing
            rehashing();
        }
    }
    TV get(TK key) {
        int hashCode = getHashCode(key); //[0 - 10000000]
        int index = hashCode % capacity; //[0 - capacity]
        auto &list = array[index];
        for (auto &e : list) {
            if (e.key == key) { // Si la clave ya existe, devuelve el valor
                return e.value;
            }
        }
        return TV(); // Si no se encuentra la clave, devuelve un valor por
                     // defecto (TV())
    }

    bool remove(TK key) {
        int hashCode = getHashCode(key);
        int index = hashCode % capacity;
        auto &list = array[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->key == key) {
                list.erase_after(it); // Elimina el elemento de la lista
                size--;
                if (list.empty())
                    --bucketCount; // Disminuye el contador de cubos ocupados
                return true;
            }
        }
        return false;
    }
    typename forward_list<Entry>::iterator begin(int index) { // O(1)
        // TODO: devolver el iterador al inicio de la lista en el index
        // CODE:
        return array[index].begin();
    }

    typename forward_list<Entry>::iterator end(int index) { // O(1)
        // TODO: devolver el iterador al final de la lista en el index
        // CODE:
        return array[index].end();
    }

    int bucket_size(
        int index) { // O(1), peor caso O(n), n:= n° de elementos el en cubo
        // TODO: devolver el tamaño de la lista en el index
        // bucketsize
        // CODE:
        return count_size(array[index]);
    }

    int bucket_count() { // O(1)
        return bucketCount;
    }

  private:
    double fillFactor() { // O(1)
        return (double)bucketCount / (capacity);
    }

    size_t getHashCode(TK key) {
        std::hash<string> hasher;
        return hasher(key);
    }

    void rehashing() {
        // Duplicar la capacidad
        int newCapacity = capacity * 2;
        forward_list<Entry> *newArray = new forward_list<Entry>[newCapacity];

        // Reinsertar todos los elementos en el nuevo array
        for (int i = 0; i < capacity; ++i) {
            for (auto &entry : array[i]) {
                int newIndex = getHashCode(entry.key) % newCapacity;
                newArray[newIndex].push_front(
                    entry); // Inserta los elementos en la nueva tabla
            }
        }

        // Liberar la memoria de la tabla original
        delete[] array;
        array = newArray; // Reasignar la tabla con la nueva capacidad
        capacity = newCapacity;
    }
    int count_size(const forward_list<Entry> &list) const {
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            ++count;
        }
        return count;
    }
};
#endif // !CHAINHASH_H
