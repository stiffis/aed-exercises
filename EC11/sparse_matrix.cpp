#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> struct Node {
    T data;
    int posX;
    int posY;
    Node<T> *next; // row
    Node<T> *down; // column
    Node() : data(T()), posX(0), posY(0), next(nullptr), down(nullptr) {}
};

template <class T> class ListSparseMatrix {
  private:
    size_t rows;
    size_t columns;
    std::vector<Node<T> *> head_rows;
    std::vector<Node<T> *> head_cols;

    void insertInRow(Node<T> *newNode) {
        Node<T> *&head = head_rows[newNode->posX];
        Node<T> *prev = nullptr;
        Node<T> *curr = head;
        while (curr != nullptr && curr->posY < newNode->posY) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        } else {
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }
    void insertInCol(Node<T> *newNode) {
        Node<T> *&head = head_cols[newNode->posY];
        Node<T> *prev = nullptr;
        Node<T> *curr = head;
        while (curr != nullptr && curr->posX < newNode->posX) {
            prev = curr;
            curr = curr->down;
        }
        if (prev == nullptr) {
            newNode->down = head;
            head = newNode;
        } else {
            newNode->down = prev->down;
            prev->down = newNode;
        }
    }

  public:
    ListSparseMatrix(size_t rows, size_t columns)
        : rows(rows), columns(columns), head_rows(rows, nullptr),
          head_cols(columns, nullptr) {}

    ListSparseMatrix(const ListSparseMatrix<T> &other)
        : rows(other.rows), columns(other.columns),
          head_rows(other.rows, nullptr), head_cols(other.columns, nullptr) {
        for (size_t i = 0; i < rows; ++i) {
            Node<T> *curr = other.head_rows[i];
            while (curr) {
                set(curr->posX, curr->posY, curr->data);
                curr = curr->next;
            }
        }
    }

    T get(unsigned posX, unsigned posY) const {
        if (posX >= rows || posY >= columns) {
            return T();
        }
        Node<T> *current = head_rows[posX];
        while (current != nullptr) {
            if (current->posY == posY) {
                return current->data;
            }
            if (current->posY > posY)
                break;
            current = current->next;
        }
        return T();
    }

    bool set(unsigned posX, unsigned posY, T data) {
        if (posX >= rows || posY >= columns) {
            return false;
        }
        Node<T> *curr = head_rows[posX];
        Node<T> *prev = nullptr;
        while (curr != nullptr && curr->posY < posY) {
            prev = curr;
            curr = curr->next;
        }
        if (curr != nullptr && curr->posY == posY) {
            if (data == T()) {
                if (prev == nullptr)
                    head_rows[posX] = curr->next;
                else
                    prev->next = curr->next;
                Node<T> *cprev = nullptr;
                Node<T> *cnode = head_cols[posY];
                while (cnode && cnode != curr) {
                    cprev = cnode;
                    cnode = cnode->down;
                }
                if (cprev == nullptr)
                    head_cols[posY] = curr->down;
                else
                    cprev->down = curr->down;
                delete curr;
            } else {
                curr->data = data;
            }
            return true;
        }
        if (data == T())
            return true;
        Node<T> *newNode = new Node<T>();
        newNode->data = data;
        newNode->posX = posX;
        newNode->posY = posY;
        insertInRow(newNode);
        insertInCol(newNode);
        return true;
    }

    ListSparseMatrix<T> operator-(const ListSparseMatrix<T> &other) const {
        if (rows != other.rows || columns != other.columns) {
            throw std::invalid_argument(
                "Las matrices deben tener el mismo tamaño.");
        }
        ListSparseMatrix<T> result(rows, columns);

        std::vector<Node<T> *> last_in_col(columns, nullptr);

        for (size_t i = 0; i < rows; ++i) {
            Node<T> *a = head_rows[i];
            Node<T> *b = other.head_rows[i];
            Node<T> *last_in_row = nullptr;
            while (a != nullptr || b != nullptr) {
                unsigned x, y;
                T val;
                if (a && (!b || a->posY < b->posY)) {
                    x = a->posX;
                    y = a->posY;
                    val = a->data;
                    a = a->next;
                } else if (b && (!a || b->posY < a->posY)) {
                    x = b->posX;
                    y = b->posY;
                    val = -b->data;
                    b = b->next;
                } else {
                    x = a->posX;
                    y = a->posY;
                    val = a->data - b->data;
                    a = a->next;
                    b = b->next;
                }
                if (val != T()) {
                    Node<T> *newNode = new Node<T>();
                    newNode->data = val;
                    newNode->posX = x;
                    newNode->posY = y;
                    newNode->next = nullptr;
                    newNode->down = nullptr;

                    if (last_in_row == nullptr) {
                        result.head_rows[x] = newNode;
                    } else {
                        last_in_row->next = newNode;
                    }
                    last_in_row = newNode;

                    if (last_in_col[y] == nullptr) {
                        result.head_cols[y] = newNode;
                    } else {
                        last_in_col[y]->down = newNode;
                    }
                    last_in_col[y] = newNode;
                }
            }
        }
        return result;
    }

    bool isDiagonal() const {
        for (size_t i = 0; i < rows; ++i) {
            Node<T> *curr = head_rows[i];
            while (curr) {
                if (curr->posX != curr->posY)
                    return false;
                curr = curr->next;
            }
        }
        return true;
    }

    void clear() {
        for (size_t i = 0; i < rows; ++i) {
            Node<T> *curr = head_rows[i];
            while (curr) {
                Node<T> *toDelete = curr;
                curr = curr->next;
                delete toDelete;
            }
            head_rows[i] = nullptr;
        }
        for (size_t i = 0; i < columns; ++i) {
            head_cols[i] = nullptr;
        }
    }

    ~ListSparseMatrix() { clear(); }
};

void test1() {
    ListSparseMatrix<int> matrix(3, 3);
    matrix.set(0, 0, 1);
    matrix.set(0, 1, 4);
    matrix.set(1, 1, 3);
    matrix.set(2, 2, 3);

    ListSparseMatrix<int> matrix2(3, 3);
    matrix2.set(0, 0, 4);
    matrix2.set(1, 0, 7);
    matrix2.set(1, 1, 2);
    matrix2.set(2, 2, 3);

    ListSparseMatrix<int> result = matrix - matrix2;
    std::cout << "Elemento en (0,0): " << result.get(0, 0) << std::endl; // -3
    std::cout << "Elemento en (0,1): " << result.get(0, 1) << std::endl; // 4
    std::cout << "Elemento en (1,0): " << result.get(1, 0) << std::endl; // -7
    std::cout << "Elemento en (1,1): " << result.get(1, 1) << std::endl; // 1
    std::cout << "Elemento en (2,2): " << result.get(2, 2)
              << std::endl; // 0 (no hay nodo)
    std::cout << "Es diagonal: " << (result.isDiagonal() ? "Si" : "No")
              << std::endl; // No
}

void test2() {
    ListSparseMatrix<int> matrix(5, 5);
    matrix.set(0, 0, 1);
    matrix.set(1, 1, 2);
    matrix.set(2, 2, 3);
    matrix.set(3, 3, 4);
    matrix.set(4, 4, 5);
    std::cout << "Es diagonal: " << (matrix.isDiagonal() ? "Si" : "No")
              << std::endl; // Si
}

void test3() {
    ListSparseMatrix<int> matrix(5, 5);
    matrix.set(0, 0, 1);
    matrix.set(1, 1, 2);
    matrix.set(2, 2, 3);
    matrix.set(3, 4, 4);
    matrix.set(4, 4, 5);
    std::cout << "Es diagonal: " << (matrix.isDiagonal() ? "Si" : "No")
              << std::endl; // No
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}
