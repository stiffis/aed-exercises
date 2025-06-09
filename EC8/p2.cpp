#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
  private:
    vector<int> parent, rank;

  public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unionsets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return false;
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

class Solution {
  public:
    vector<int> findRedundantConnection(vector<vector<int>> &edges) {
        int n = edges.size();
        UnionFind uf(n + 1);

        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            if (!uf.unionsets(u, v)) {
                return edge;
            }
        }
        return {};
    }
};
