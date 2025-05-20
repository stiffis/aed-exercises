#include <iostream>
#include <vector>
using namespace std;

const int maxColision = 3;

// itera sobre el hashtable manteniendo el orden de insercion
template <typename TK, typename TV> class HashIterator {
  private:
  public:
    HashIterator<TK, TV> &operator=(HashIterator<TK, TV> other);
    bool operator!=(HashIterator<TK, TV> other);
    HashIterator<TK, TV> &operator++(); //++it
    pair<TK, TV> operator*();
};

template <typename TK, typename TV> class HashTable {
  public:
    typedef HashIterator<TK, TV> iterator;
    iterator begin(); // Retorna el inicio del iterador
    iterator end();   // Retorna el final del iterador

  private:
    int capacity; // capacidad del hash table
    int size;     // total de elementos
                  // TODO: completar los demas atributos

  public:
    HashTable(int _cap = 5) : capacity(_cap), size(0) {
        // TODO
    }
    void insert(TK key, TV value);
    void insert(pair<TK, TV> item);
    TV &at(TK key);
    TV &operator[](TK key);
    bool find(TK key);
    bool remove(TK key);
    int getSize();

    /*itera sobre el hashtable manteniendo el orden de insercion*/
    vector<TK> getAllKeys();
    vector<pair<TK, TV>> getAllElements();

  private:
    /*Si una lista colisionada excede maxColision, redimensionar el array*/
    void rehashing();
};
