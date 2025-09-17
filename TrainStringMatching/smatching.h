// string mathing intutivo
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> inocente(const std::string &text, const std::string &pattern) {
    std::vector<int> result;
    int n = text.size();
    int m = pattern.size();
    for (int j = 0; j <= n - m; ++j) {
        int i = 0;
        while (i < m && pattern[i] == text[i + j]) {
            ++i;
        }
        if (i == m) {
            result.push_back(j);
        }
    }
    return result;
}

int *buildPositions(const std::string &pattern) {
    int *array = new int[256];
    for (int i = 0; i < 256; ++i) {
        array[i] = -1;
    }
    for (int i = 0; i < pattern.size(); ++i) {
        array[pattern[i]] = i;
    }
    return array;
}

std::vector<int> boyerMoore(const std::string &text,
                            const std::string &pattern) {
    std::vector<int> result;
    int n = text.size();
    int m = pattern.size();
    if (m == 0 || n < m)
        return result;
    int *positions = buildPositions(pattern);
    int j = 0;
    while (j <= n - m) {
        int i = m - 1;
        while (i >= 0 && pattern[i] == text[j + i]) {
            --i;
        }
        if (i < 0) {
            result.push_back(j);
            j += (j + m < n) ? m - positions[(int)text[j + m]] : 1;
        } else {
            int salto = i - positions[(int)text[j + i]];
            j += std::max(1, salto);
        }
    }
    return result;
}
