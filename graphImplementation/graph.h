// Implementar una class Graph que represente un grafo dirigido
// y que contenga los siguientes métodos:
// - add_edge(v1, v2): Agrega una arista dirigida desde v1 a v2.
// - remove_edge(v1, v2): Elimina la arista dirigida desde v1 a v2.
// - get_neighbors(v): Devuelve una lista de los vecinos de v.
// - has_edge(v1, v2): Devuelve True si existe una arista dirigida desde v1 a
// v2, False en caso contrario.
// - get_vertices(): Devuelve una lista de todos los vértices del grafo.
// - is_empty(): Devuelve True si el grafo está vacío, False en caso contrario.
// - clear(): Elimina todas las aristas y vértices del grafo.
// - en C++
#include <unordered_map>
#include <unordered_set>
#include <vector>
class Graph {
  private:
    std::unordered_map<int, std::unordered_set<int>> adj_list;

  public:
    // Agrega una arista dirigida desde v1 a v2
    void add_edge(int v1, int v2) { adj_list[v1].insert(v2); }

    // Elimina la arista dirigida desde v1 a v2
    void remove_edge(int v1, int v2) { adj_list[v1].erase(v2); }

    // Devuelve una lista de los vecinos de v
    std::vector<int> get_neighbors(int v) {
        std::vector<int> neighbors(adj_list[v].begin(), adj_list[v].end());
        return neighbors;
    }

    // Devuelve True si existe una arista dirigida desde v1 a v2
    bool has_edge(int v1, int v2) {
        return adj_list[v1].find(v2) != adj_list[v1].end();
    }

    // Devuelve una lista de todos los vértices del grafo
    std::vector<int> get_vertices() {
        std::vector<int> vertices;
        for (const auto &pair : adj_list) {
            vertices.push_back(pair.first);
        }
        return vertices;
    }
    // Devuelve True si el grafo está vacío
    bool is_empty() { return adj_list.empty(); }
    // Elimina todas las aristas y vértices del grafo
    void clear() { adj_list.clear(); }
};
