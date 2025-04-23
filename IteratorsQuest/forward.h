#ifndef FORWARD_H
#define FORWARD_H
template <typename T> struct NodeFL {
    T data;
    NodeFL *next;
    NodeFL() : next(nullptr) {}
    NodeFL(T value) : data(value), next(nullptr) {}
};
template <class T> class ForwardListIterator {
  private:
    NodeFL<T> *current;

  public:
    ForwardListIterator() : current(nullptr) {};
    ForwardListIterator(NodeFL<T> *current) : current(current) {};
    ForwardListIterator<T> &operator++();    //++it
    ForwardListIterator<T> &operator++(int); // it++
    bool operator!=(const ForwardListIterator<T> &other);
    T operator*();
};
template <typename T> class ForwardList {
  public:
    typedef ForwardListIterator<T> iterator;

  private:
    NodeFL<T> *head;

  public:
    ForwardList() : head(nullptr) {}
    iterator begin() {
        // TODO
    }
    iterator end() {
        // TODO
    }
    void push_front(T data) {
        // TODO
    }
    T pop_front() {
        // TODO
    }
    ~ForwardList() {
        // TODO
    }
};
#endif
