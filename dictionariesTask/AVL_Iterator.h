#include "AVL_Node.h"

/*Forward Iterator for the AVL*/
template <typename T> class AVLIterator {
  public:
    enum Type { PreOrder, InOrder, PostOrder, BFS };

  private:
    NodeAVL<T> *current;
    Type type;

  public:
    AVLIterator() : current(nullptr), type(InOrder) {};
    AVLIterator(NodeAVL<T> *current, Type type = InOrder) : type(type) {
        // TODO
    }
    AVLIterator<T> &operator=(AVLIterator<T> other);
    bool operator!=(AVLIterator<T> other);
    AVLIterator<T> &operator++(); //++it
    T operator*();
};
