#include <algorithm>
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
    int minCostConnectPoints(vector<vector<int>> &points) {
        int n = points.size();
        UnionFind uf(n);

        vector<pair<int, pair<int, int>>> edges;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = abs(points[i][0] - points[j][0]) +
                           abs(points[i][1] - points[j][1]);
                edges.push_back({dist, {i, j}});
            }
        }

        sort(edges.begin(), edges.end());

        int mst_cost = 0;
        int edges_used = 0;

        for (const auto &edge : edges) {
            int cost = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            if (uf.unionsets(u, v)) {
                mst_cost += cost;
                edges_used++;
                if (edges_used == n - 1)
                    break;
            }
        }

        return mst_cost;
    }
};
