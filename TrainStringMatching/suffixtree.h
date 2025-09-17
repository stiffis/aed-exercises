#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/*class SuffixTree {
  public:
    struct Node {
        struct Edge {
            int start, end;
            Node *child;
            Edge(int s, int e, Node *c) : start(s), end(e), child(c) {}
        };
        std::vector<Edge> edges;
        int suffixIndex;
        Node() : suffixIndex(-1) {}
        ~Node() {
            for (auto &edge : edges)
                delete edge.child;
        }
    };

    SuffixTree(const std::string &text) : text(text), root(new Node()) {
        build();
    }

    ~SuffixTree() { delete root; }

    void build() {
        int n = text.size();
        for (int i = 0; i < n; ++i) {
            Node *curr = root;
            int j = i;
            while (j < n) {
                bool found = false;
                for (auto &edge : curr->edges) {
                    int k = edge.start;
                    while (k <= edge.end && j < n && text[k] == text[j]) {
                        ++k;
                        ++j;
                    }
                    if (k > edge.start) {
                        if (k - 1 == edge.end) {
                            curr = edge.child;
                            found = true;
                        } else {
                            Node *split = new Node();
                            split->edges.push_back(
                                Node::Edge(k, edge.end, edge.child));
                            edge.end = k - 1;
                            edge.child = split;
                            curr = split;
                            found = true;
                        }
                        break;
                    }
                }
                if (!found) {
                    Node *leaf = new Node();
                    leaf->suffixIndex = i;
                    curr->edges.push_back(Node::Edge(j, n - 1, leaf));
                    break;
                }
            }
        }
    }

    std::vector<int> search(const std::string &pattern) const {
        const Node *curr = root;
        int i = 0, n = pattern.size();
        while (i < n) {
            bool found = false;
            for (const auto &edge : curr->edges) {
                int len = edge.end - edge.start + 1;
                if (pattern.compare(i, len, text, edge.start, len) == 0) {
                    i += len;
                    curr = edge.child;
                    found = true;
                    break;
                } else if (pattern.compare(i, std::min(n - i, len), text,
                                           edge.start,
                                           std::min(n - i, len)) == 0) {
                    i = n;
                    curr = edge.child;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return {};
            }
        }
        return collectSuffixIndexes(curr);
    }

  private:
    std::string text;
    Node *root;

    std::vector<int> collectSuffixIndexes(const Node *node) const {
        std::vector<int> result;
        if (node->suffixIndex != -1) {
            result.push_back(node->suffixIndex);
        }
        for (const auto &edge : node->edges) {
            auto childResult = collectSuffixIndexes(edge.child);
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
        return result;
    }
};
*/

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class SuffixTree {
  public:
    // Estructura de nodo con las aristas
    struct Node {
        struct Edge {
            int start, end;
            Node *child;
            Edge(int s, int e, Node *c) : start(s), end(e), child(c) {}
        };

        std::vector<Edge> edges;
        int suffixIndex;

        Node() : suffixIndex(-1) {}
        ~Node() {
            for (auto &edge : edges)
                delete edge.child;
        }
    };

    // Constructor
    SuffixTree(const std::string &text) : text(text), root(new Node()) {
        build();
    }

    // Destructor
    ~SuffixTree() { delete root; }

    // Construcción del árbol de sufijos
    void build() {
        int n = text.size();
        for (int i = 0; i < n; ++i) {
            Node *curr = root;
            int j = i;

            // Mientras no hayamos alcanzado el final de la cadena
            while (j < n) {
                bool found = false;

                // Buscar el camino en los nodos actuales
                for (auto &edge : curr->edges) {
                    int k = edge.start;

                    // Comparar el prefijo con el texto
                    while (k <= edge.end && j < n && text[k] == text[j]) {
                        ++k;
                        ++j;
                    }

                    // Si encontramos una coincidencia
                    if (k > edge.start) {
                        if (k - 1 == edge.end) {
                            // Continuar por el nodo hijo
                            curr = edge.child;
                            found = true;
                        } else {
                            // Dividir la arista y crear un nodo intermedio
                            Node *split = new Node();
                            split->edges.push_back(
                                Node::Edge(k, edge.end, edge.child));
                            edge.end = k - 1;
                            edge.child = split;
                            curr = split;
                            found = true;
                        }
                        break;
                    }
                }

                // Si no encontramos ninguna coincidencia, agregamos un nuevo
                // nodo hoja
                if (!found) {
                    Node *leaf = new Node();
                    leaf->suffixIndex = i;
                    curr->edges.push_back(Node::Edge(j, n - 1, leaf));
                    break;
                }
            }
        }
    }

    // Búsqueda de un patrón en el árbol de sufijos
    std::vector<int> search(const std::string &pattern) const {
        const Node *curr = root;
        int i = 0, n = pattern.size();

        // Buscar el patrón en el árbol de sufijos
        while (i < n) {
            bool found = false;
            for (const auto &edge : curr->edges) {
                int len = edge.end - edge.start + 1;

                // Comparar el patrón con las subcadenas en las aristas
                if (pattern.compare(i, len, text, edge.start, len) == 0) {
                    i += len;
                    curr = edge.child;
                    found = true;
                    break;
                } else if (pattern.compare(i, std::min(n - i, len), text,
                                           edge.start,
                                           std::min(n - i, len)) == 0) {
                    // Caso parcial donde el patrón es más corto que la arista
                    i = n;
                    curr = edge.child;
                    found = true;
                    break;
                }
            }

            if (!found) {
                return {}; // No encontrado
            }
        }

        return collectSuffixIndexes(curr);
    }

  private:
    std::string text;
    Node *root;

    // Recoger los índices de sufijo desde el nodo
    std::vector<int> collectSuffixIndexes(const Node *node) const {
        std::vector<int> result;
        if (node->suffixIndex != -1) {
            result.push_back(node->suffixIndex);
        }
        for (const auto &edge : node->edges) {
            auto childResult = collectSuffixIndexes(edge.child);
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
        return result;
    }
};

#endif // SUFFIX_TREE_H
