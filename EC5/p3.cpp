#include <functional>
template <typename TK, typename TV> class HashTable {
  private:
    struct Node {
        TK key;
        TV value;
        bool isOccupied;
        Node() : isOccupied(false) {}
    };

    Node *table;
    int capacity;
    int size;

    int hashFunction(TK key) { return std::hash<TK>()(key) % capacity; }

    void resize() {
        int newCapacity = capacity * 2;
        Node *newTable = new Node[newCapacity];

        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                int newIndex = std::hash<TK>()(table[i].key) % newCapacity;
                while (newTable[newIndex].isOccupied) {
                    newIndex = (newIndex + 1) % newCapacity;
                }
                newTable[newIndex] = table[i];
            }
        }

        delete[] table;
        table = newTable;
        capacity = newCapacity;
    }

  public:
    HashTable(int initialCapacity = 16) : capacity(initialCapacity), size(0) {
        table = new Node[capacity];
    }

    ~HashTable() { delete[] table; }

    void insert(TK key, TV value) {
        if (size >= capacity / 2) {
            resize(); // Redimensionamos el HashTable si está a más de la mitad
                      // de su capacidad
        }

        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                return;
            }
        }

        if (!table[index].isOccupied) {
            size++;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    TV get(TK key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }

        return nullptr;
    }

    void remove(TK key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].isOccupied = false;
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }
    }

    int getSize() { return size; }
};

class LRUCache {
  private:
    struct DllNode {
        int key;
        int value;
        DllNode *prev;
        DllNode *next;
        DllNode(int k, int v)
            : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    HashTable<int, DllNode *> cache;
    DllNode *head;
    DllNode *tail;
    int capacity;

    void moveToFront(DllNode *node) {
        if (node == head)
            return;

        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;

        if (node == tail) {
            tail = tail->prev;
            if (tail)
                tail->next = nullptr;
        }

        node->next = head;
        if (head)
            head->prev = node;
        head = node;
        node->prev = nullptr;

        if (!tail)
            tail = node;
    }

    void removeTail() {
        if (!tail)
            return;

        cache.remove(tail->key);

        if (head == tail) {
            head = tail = nullptr;
            return;
        }

        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
    }

  public:
    LRUCache(int capacity)
        : cache(capacity), head(nullptr), tail(nullptr), capacity(capacity) {}

    int get(int key) {
        DllNode *node = cache.get(key);
        if (!node) {
            return -1;
        }
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        DllNode *node = cache.get(key);

        if (node) {
            node->value = value;
            moveToFront(node);
        } else {
            if (cache.getSize() == capacity) {
                removeTail();
            }
            node = new DllNode(key, value);
            cache.insert(key, node);
            node->next = head;
            if (head)
                head->prev = node;
            head = node;
            if (!tail)
                tail = node;
        }
    }
};
