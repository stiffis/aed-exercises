#ifndef DOUBLE_H
#define DOUBLE_H
template <typename T> struct NodeDL {
    T data;
    NodeDL *next;
    NodeDL *prev;
    NodeDL() : next(nullptr), prev(nullptr) {}
    NodeDL(T value) : data(value), next(nullptr), prev(nullptr) {}
};
template <typename T> class DoubleListIterator {
  public:
    DoubleListIterator() {};
    DoubleListIterator(NodeDL<T> *current) {};
    DoubleListIterator<T> &operator++();    //++it
    DoubleListIterator<T> &operator++(int); // it++
    DoubleListIterator<T> &operator--();    //--it
    bool operator!=(const DoubleListIterator<T> &other);
    T operator*();
};
template <typename T> class DoubleList {
  public:
    typedef DoubleListIterator<T> iterator;

  private:
    NodeDL<T> *head;
    NodeDL<T> *tail;

  public:
    DoubleList() {
        // TODO
    }
    /* new functions */
    iterator begin() {
        // TODO
    }
    iterator end() {
        // TODO
    }
    void push_back(T data) {
        // TODO
    }
    T pop_back() {
        // TODO
    }
    ~DoubleList() {
        // TODO
    }
};
#endif
