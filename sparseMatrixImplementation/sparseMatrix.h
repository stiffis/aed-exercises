#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
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
  private:
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

    int getNumRows() const { return numRows; }
    int getNumCols() const { return numCols; }

    // Sum two sparse matrices
    SparseMatrix<T> &operator+(
        const SparseMatrix<T> &other) const { // PERF: O(n) n: number of
                                              // non-zero elements
                                              // O(n^2) in worst case, because
                                              // both matrices are traversed
        if (numRows != other.numRows || numCols != other.numCols) {
            throw std::invalid_argument("Matrices dimensions do not match");
        }

        SparseMatrix<T> result(numRows, numCols);
        for (int r = 0; r < numRows; ++r) {
            Node<T> *current = rows[r];
            while (current) {
                result.set(r, current->col, current->value);
                current = current->next;
            }
        }

        for (int r = 0; r < other.numRows; ++r) {
            Node<T> *current = other.rows[r];
            while (current) {
                T existingValue = result.get(r, current->col);
                result.set(r, current->col, existingValue + current->value);
                current = current->next;
            }
        }

        return result;
    }
    // subtract
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

#endif // SPARSE_MATRIX_H
