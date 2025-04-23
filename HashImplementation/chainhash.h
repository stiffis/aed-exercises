#include <forward_list>
#include <string>
#include <unordered_map>
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
    };
    forward_list<Entry> *array;
    int size;
    int capacity;
    int bucketCount;

  public:
    ChainHash(int _capacity = 10) {
        array = new forward_list<Entry>[_capacity];
        capacity = _capacity;
        size = 0;
        bucketCount = 0;
    }

    void set(TK key, TV value) {
        if (fillFactor() >= maxFillfactor)
            rehashing();
        int hashCode = getHashCode(key); //[0 - 10000000]
        int index = hashCode % capacity; //[0 - capacity]
        // TODO: - Insertar el Entry(key, value) en index, manejando colisiones.
        //       - Si el index no tiene elementos, incrementar bucketCount.
        //       - Si la colision es mayor a maxColision, rehashing()
    }

    TV get(TK key) {
        int hashCode = getHashCode(key);
        int index = hashCode % capacity;
        // TODO: buscar el Entry(key, value) en index y devolver el value
    }

    bool remove(TK key) {
        // TODO: eliminar el Entry(key, value) en index y
        //       devolver true si lo encontro, false si no lo encontro
    }

    typename forward_list<Entry>::iterator begin(int index) { // O(1)
        // TODO: devolver el iterador al inicio de la lista en el index
    }

    int bucket_size(int index) { // O(1)
        // TODO: devolver el tamaño de la lista en el index
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
        // TODO: crear un nuevo array de forward_list<Entry> con el doble de
        // capacidad
        //       y volver a insertar todos los elementos en el nuevo array
    }
};
