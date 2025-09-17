#ifndef HASH_SPARSE_MATRIX_H
#define HASH_SPARSE_MATRIX_H
#include <unordered_map>
template <class T> class HashSparseMatrix {
  private:
    std::unordered_map<int, T> data;
    int numRows, numCols;

  public:
    HashSparseMatrix(int r, int c) : numRows(r), numCols(c) {}

    T get(int r, int c) const {
        if (r < 0 || r >= numRows || c < 0 || c >= numCols)
            return T();
        auto it = data.find(r * numCols + c);
        if (it != data.end())
            return it->second;
        return T();
    }

    void set(int r, int c, T value) {
        if (r < 0 || r >= numRows || c < 0 || c >= numCols)
            return;
        if (value != T()) {
            data[r * numCols + c] = value;
        } else {
            data.erase(r * numCols + c);
        }
    }

    int rows() const { return numRows; }
    int cols() const { return numCols; }
};

#endif // !HASH_SPARSE_MATRIX_H
