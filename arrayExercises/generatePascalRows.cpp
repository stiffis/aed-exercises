#include <vector>
class Solution {
  public:
    std::vector<std::vector<int>> generate(int numRows) {
        std::vector<std::vector<int>> inicio = {{1}};
        if (numRows == 0) {
            return {};
        }
        for (int i = 1; i < numRows; ++i) {
            std::vector<int> temp;
            const std::vector<int> &prevRow = inicio[i - 1];
            temp.push_back(1);
            for (int j = 1; j < i; j += 1) {
                temp.push_back(prevRow[j - 1] + prevRow[j]);
            }
            temp.push_back(1);
            inicio.push_back(temp);
        }
        return inicio;
    }
    std::vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return {1};
        }
        std::vector<int> row = {1};
        for (int i = 1; i <= rowIndex; ++i) {
            row.push_back(static_cast<long long>(row[i - 1]) *
                          (rowIndex - i + 1) / i);
        }
        return row;
    }
    std::vector<int> getRow2(int rowIndex) {
        int numRows = rowIndex + 1;
        std::vector<std::vector<int>> inicio = {{1}};
        if (numRows == 0) {
            return {};
        }
        for (int i = 1; i < numRows; ++i) {
            std::vector<int> temp;
            const std::vector<int> &prevRow = inicio[i - 1];
            temp.push_back(1);
            for (int j = 1; j < i; j += 1) {
                temp.push_back(prevRow[j - 1] + prevRow[j]);
            }
            temp.push_back(1);
            inicio.push_back(temp);
        }
        return inicio[rowIndex];
    }
};
