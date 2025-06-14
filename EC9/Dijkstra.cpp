#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ParVD {
    int vertice;
    double distancia;
    // Para que funcione con priority_queue<ParVD>
    bool operator<(const ParVD &otro) const {
        return distancia > otro.distancia; // Min-heap
    }
};

void mostrarCaminos(vector<int> dist, vector<int> padre) {
    // TODO
}

void dijkstra(const vector<vector<ParVD>> &grafo, int origen) {
    int n = grafo.size();
    vector<int> dist(n, INT_MAX);
    vector<int> padres(n, -1);
    vector<bool> visitado(n, false);

    priority_queue<ParVD> pq;
    dist[origen] = 0;
    pq.push({origen, 0});

    while (!pq.empty()) {
        int u = pq.top().vertice;
        pq.pop();

        if (visitado[u])
            continue;
        visitado[u] = true;

        for (const ParVD &vecino : grafo[u]) {
            int v = vecino.vertice; // Adyacente
            int peso = vecino.distancia;
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                padres[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    // Mostrar resultados
    mostrarCaminos(dist, padres);
}

int main() {
    int n = 5;
    vector<vector<ParVD>> grafo(n);

    // Agregar aristas: grafo[u].push_back({v, peso});
    grafo[0].push_back({1, 10});
    grafo[0].push_back({4, 5});
    grafo[1].push_back({2, 1});
    grafo[1].push_back({4, 2});
    grafo[2].push_back({3, 4});
    grafo[3].push_back({0, 7});
    grafo[3].push_back({2, 6});
    grafo[4].push_back({1, 3});
    grafo[4].push_back({2, 9});
    grafo[4].push_back({3, 2});
    /*
    [,,,,]
    [,,,,]
    [,,,,]
    [,,,,]
    [,,,,]
    */
    dijkstra(grafo, 0);
    return 0;
}
