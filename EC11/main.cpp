#include <iostream>
#include <stdexcept>
#include <vector>

template <class T> class Node {
  public:
    int row, col;
    T value;
    Node *next;

    Node(int r, int c, T val) : row(r), col(c), value(val), next(nullptr) {}
};

template <class T> class SparseMatrix {
  public:
    std::vector<Node<T> *> rows, cols;
    int numRows, numCols;

  public:
    SparseMatrix(int r, int c) : numRows(r), numCols(c) {
        rows.resize(r, nullptr);
        cols.resize(c, nullptr);
    }

    ~SparseMatrix() {
        for (int i = 0; i < numRows; ++i) {
            Node<T> *current = rows[i];
            while (current) {
                Node<T> *toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    T get(int r, int c) const { // PERF: O(log(min(r, c))) on average
                                // O(n) in worst case
        if (r < 0 || r >= numRows || c < 0 || c >= numCols)
            return T();

        Node<T> *current = rows[r];
        while (current) {
            if (current->col == c)
                return current->value;
            if (current->col > c)
                break; // No value at this position
            current = current->next;
        }
        return T();
    }
    void set(int r, int c, T value) { // PERF: O(log(min(r, c))) on average
                                      // O(n) in worst case, n: number of
                                      // non-zero elements
        if (r < 0 || r >= numRows || c < 0 || c >= numCols)
            return;

        Node<T> *newNode = new Node<T>(r, c, value);
        if (!rows[r]) {
            rows[r] = newNode;
        } else {
            Node<T> *current = rows[r];
            while (current->next && current->next->col < c) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        if (!cols[c]) {
            cols[c] = newNode;
        } else {
            Node<T> *currentCol = cols[c];
            while (currentCol->next && currentCol->next->row < r) {
                currentCol = currentCol->next;
            }
            newNode->next = currentCol->next;
            currentCol->next = newNode;
        }
    }
    // Función para restar dos matrices dispersas A y B y generar la matriz C
    SparseMatrix<T> subtract(const SparseMatrix<T> &other) {
        if (this->numRows != other.numRows || this->numCols != other.numCols) {
            throw std::invalid_argument(
                "Las matrices deben tener el mismo tamaño.");
        }

        SparseMatrix<T> result(this->numRows, this->numCols);

        for (int r = 0; r < numRows; ++r) {
            Node<T> *currentA = rows[r];
            Node<T> *currentB = other.rows[r];

            while (currentA != nullptr || currentB != nullptr) {
                if (currentA == nullptr) {
                    // Inserción directamente en la matriz resultado
                    Node<T> *newNode = new Node<T>(currentB->row, currentB->col,
                                                   -currentB->value);
                    newNode->next = result.rows[currentB->row];
                    result.rows[currentB->row] = newNode;

                    currentB = currentB->next;
                } else if (currentB == nullptr) {
                    // Inserción directamente en la matriz resultado
                    Node<T> *newNode = new Node<T>(currentA->row, currentA->col,
                                                   currentA->value);
                    newNode->next = result.rows[currentA->row];
                    result.rows[currentA->row] = newNode;

                    currentA = currentA->next;
                } else if (currentA->col < currentB->col) {
                    // Inserción directamente en la matriz resultado
                    Node<T> *newNode = new Node<T>(currentA->row, currentA->col,
                                                   currentA->value);
                    newNode->next = result.rows[currentA->row];
                    result.rows[currentA->row] = newNode;

                    currentA = currentA->next;
                } else if (currentB->col < currentA->col) {
                    // Inserción directamente en la matriz resultado
                    Node<T> *newNode = new Node<T>(currentB->row, currentB->col,
                                                   -currentB->value);
                    newNode->next = result.rows[currentB->row];
                    result.rows[currentB->row] = newNode;

                    currentB = currentB->next;
                } else {
                    // Restar y agregar a la matriz resultado
                    Node<T> *newNode =
                        new Node<T>(currentA->row, currentA->col,
                                    currentA->value - currentB->value);
                    newNode->next = result.rows[currentA->row];
                    result.rows[currentA->row] = newNode;

                    currentA = currentA->next;
                    currentB = currentB->next;
                }
            }
        }

        return result;
    }

    // Verificar si la matriz es diagonal
    bool isDiagonal() const {
        for (int i = 0; i < numRows; ++i) {
            Node<T> *current = rows[i];
            if (current != nullptr) {
                if (current->col != i) {
                    return false;
                }
                current = current->next;
                while (current != nullptr) {
                    if (current->col != i) {
                        return false;
                    }
                    current = current->next;
                }
            }
        }
        return true;
    }
};

void test1() {
    SparseMatrix<int> matrix(3, 3);
    matrix.set(0, 0, 1);
    matrix.set(0, 1, 4);
    matrix.set(1, 1, 3);
    matrix.set(2, 2, 3);

    SparseMatrix<int> matrix2(3, 3);
    matrix2.set(0, 0, 4);
    matrix2.set(1, 0, 7);
    matrix2.set(1, 1, 2);
    matrix2.set(2, 2, 3);

    SparseMatrix<int> result = matrix.subtract(matrix2);
    std::cout << "Elemento en (0,0): " << result.get(0, 0)
              << std::endl; // Debería ser -3
    std::cout << "Elemento en (0,1): " << result.get(0, 1)
              << std::endl; // Debería ser 4
    std::cout << "Elemento en (1,0): " << result.get(1, 0)
              << std::endl; // Debería ser -7
    std::cout << "Elemento en (1,1): " << result.get(1, 1)
              << std::endl; // Debería ser 1
    std::cout << "Elemento en (2,2): " << result.get(2, 2)
              << std::endl; // Elemento no encontrado (se eliminó por que se
                            // hizo cero)
    std::cout << "Es diagonal: " << (result.isDiagonal() ? "Si" : "No")
              << std::endl; // Debería ser No
}

void test2() {
    SparseMatrix<int> matrix(5, 5);
    matrix.set(0, 0, 1);
    matrix.set(1, 1, 2);
    matrix.set(2, 2, 3);
    matrix.set(3, 3, 4);
    matrix.set(4, 4, 5);
    std::cout << "Es diagonal: " << (matrix.isDiagonal() ? "Si" : "No")
              << std::endl; // Debería ser Sí
}

void test3() {
    SparseMatrix<int> matrix(5, 5);
    matrix.set(0, 0, 1);
    matrix.set(1, 1, 2);
    matrix.set(2, 2, 3);
    matrix.set(3, 4, 4);
    matrix.set(4, 4, 5);
    std::cout << "Es diagonal: " << (matrix.isDiagonal() ? "Si" : "No")
              << std::endl; // Debería ser No
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}
