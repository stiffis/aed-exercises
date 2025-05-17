#include <iostream>
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

    int hashFunction(TK key) { return static_cast<int>(key) % capacity; }

  public:
    HashTable(int capacity) {
        this->capacity = capacity;
        table = new Node[capacity];
        size = 0;
    }

    ~HashTable() { delete[] table; }

    void insert(TK key, TV value) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                return;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        size++;
    }

    TV *get(TK key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return &table[index].value;
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

    void printTable() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Indice " << i << ": {" << table[i].key << ": "
                          << table[i].value << "}" << std::endl;
            }
        }
    }

    int getSize() { return size; }
};

class Solution {
  public:
    int firstUniqChar(std::string s) {
        HashTable<char, int> hashTable(s.length());

        for (char c : s) {
            int *current = hashTable.get(c);
            if (current == nullptr) {
                hashTable.insert(c, 1);
            } else {
                (*current)++;
            }
        }

        for (int i = 0; i < s.length(); i++) {
            int *count = hashTable.get(s[i]);
            if (count != nullptr && *count == 1) {
                return i;
            }
        }

        return -1;
    }
};
