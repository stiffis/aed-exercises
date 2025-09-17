#ifndef DISJOINSET_H
#define DISJOINSET_H

#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T> class DisjointSet {
  private:
    std::vector<T> data;
    std::vector<int> parent;
    std::vector<int> rank;

  public:
    DisjointSet(const std::vector<T> &elements)
        : data(elements), parent(elements.size()), rank(elements.size(), 0) {
        for (size_t i = 0; i < elements.size(); ++i) {
            parent[i] = i;
        }
    }
    void makeSet(T x) {
        if (data.size() >= parent.size()) {
            throw std::out_of_range(
                "Cannot add more elements than initialized");
        }
        data.push_back(x);
        parent.push_back(data.size() - 1);
        rank.push_back(0);
    }
    int find(T x) {
        auto it = std::find(data.begin(), data.end(), x);
        if (it == data.end()) {
            throw std::out_of_range("Element not found in the set");
        }
        int index = std::distance(data.begin(), it);
        if (parent[index] != index) {
            parent[index] = find(data[parent[index]]); // Path compression
        }
        return parent[index];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX < 0 || rootY < 0 ||
            rootX >= static_cast<int>(parent.size()) ||
            rootY >= static_cast<int>(parent.size())) {
            throw std::out_of_range("Index out of range");
        }
        if (rootX == rootY)
            return; // Already in the same set
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) { // Union by rank
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool isConnected(int x, int y) { return find(x) == find(y); }

    bool hasCycle(std::vector<std::vector<int>> &edges) {
        for (const auto &edge : edges) {
            int u = edge[0], v = edge[1];
            if (isConnected(u, v)) {
                return true; // Cycle detected
            }
            unionSets(u, v);
        }
        return false; // No cycle detected
    }

    std::vector<std::vector<int>>
    kruskalMST(std::vector<std::vector<int>> &edges) {
        std::vector<std::vector<int>> mst;
        std::sort(edges.begin(), edges.end(),
                  [](const std::vector<int> &a, const std::vector<int> &b) {
                      return a[2] < b[2]; // Sort by weight
                  });

        for (const auto &edge : edges) {
            int u = edge[0], v = edge[1], weight = edge[2];
            if (!isConnected(u, v)) {
                unionSets(u, v);
                mst.push_back({u, v, weight});
            }
        }
        return mst;
    }
    int setsCount() {
        std::vector<bool> seen(data.size(), false);
        int count = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            int root = find(i);
            if (!seen[root]) {
                seen[root] = true;
                count++;
            }
        }
        return count;
    }
};

#endif // !DISJOINSET_H
