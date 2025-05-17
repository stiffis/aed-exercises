#include <unordered_map>
#include <unordered_set>
#include <vector>
class Graph {
  private:
    std::unordered_map<int, std::unordered_set<int>> adj_list;

  public:
    void add_edge(int v1, int v2) { adj_list[v1].insert(v2); }

    void remove_edge(int v1, int v2) { adj_list[v1].erase(v2); }

    std::vector<int> get_neighbors(int v) {
        std::vector<int> neighbors(adj_list[v].begin(), adj_list[v].end());
        return neighbors;
    }

    bool has_edge(int v1, int v2) {
        return adj_list[v1].find(v2) != adj_list[v1].end();
    }

    std::vector<int> get_vertices() {
        std::vector<int> vertices;
        for (const auto &pair : adj_list) {
            vertices.push_back(pair.first);
        }
        return vertices;
    }
    bool is_empty() { return adj_list.empty(); }
    void clear() { adj_list.clear(); }
};
