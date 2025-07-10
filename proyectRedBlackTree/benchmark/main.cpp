#include "BenchmarkRedBlackTree.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const int maxN = 30000;
    const int step = 500;
    const int runsPerSize = 5;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream outFile("benchmark_results.csv");
    outFile << "Size,Run,Insert_ns,Search_ns,Remove_ns,LeftRotate_ns,RightRotate_ns\n";

    for (int n = step; n <= maxN; n += step) {
        for (int run = 1; run <= runsPerSize; ++run) {
            // Generar datos aleatorios únicos
            std::vector<int> values(maxN);
            for (int i = 0; i < maxN; ++i)
                values[i] = i + 1;
            std::shuffle(values.begin(), values.end(), gen);

            RedBlackTree tree;

            // Insertar n nodos (los primeros n valores)
            for (int i = 0; i < n; ++i) {
                tree.insert(values[i]);
            }

            // Calcular tiempo promedio de inserción (últimas n inserciones)
            long long totalInsertTime = 0;
            auto insertData = tree.getInsertBenchmark();
            int insertCount = std::min(n, (int)insertData.size());
            
            if (insertCount > 0) {
                // Tomar las últimas insertCount inserciones
                for (int i = insertData.size() - insertCount; i < (int)insertData.size(); ++i) {
                    totalInsertTime += insertData[i].first;
                }
            }

            // Buscar nodos existentes (ahora usa timing interno)
            for (int i = 0; i < n; ++i) {
                auto res = tree.search(values[i]);
                if (!res)
                    std::cerr << "Error: nodo no encontrado!" << std::endl;
            }

            // Buscar nodos no existentes (ahora usa timing interno)
            std::vector<int> missingValues;
            for (int i = maxN + 1; i <= maxN + n; ++i)
                missingValues.push_back(i);
            for (int val : missingValues) {
                auto res = tree.search(val);
                if (res)
                    std::cerr << "Error: nodo inexistente encontrado!"
                              << std::endl;
            }

            // Calcular tiempo promedio de búsqueda (todas las búsquedas realizadas)
            long long avgSearchTime = 0;
            auto searchData = tree.getSearchBenchmark();
            
            if (!searchData.empty()) {
                long long totalSearchTime = 0;
                for (auto &p : searchData) {
                    totalSearchTime += p.first;
                }
                avgSearchTime = totalSearchTime / searchData.size();
            }

            // Eliminar 10% aleatorio de nodos insertados
            int removeCount = n / 10;
            if (removeCount == 0)
                removeCount = 1;
            std::shuffle(values.begin(), values.begin() + n, gen);
            auto startRemove = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < removeCount; ++i) {
                tree.remove(values[i]);
            }
            auto endRemove = std::chrono::high_resolution_clock::now();
            long long removeTime =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    endRemove - startRemove)
                    .count();

            // Sumar tiempos rotaciones
            long long totalLeftRotateTime = 0;
            for (auto &p : tree.getLeftRotateBenchmark()) {
                if (p.second <= n)
                    totalLeftRotateTime += p.first;
            }
            long long totalRightRotateTime = 0;
            for (auto &p : tree.getRightRotateBenchmark()) {
                if (p.second <= n)
                    totalRightRotateTime += p.first;
            }

            long long avgInsertTime = (insertCount > 0) ? totalInsertTime / insertCount : 0;
            
            outFile << n << "," << run << "," << avgInsertTime << ","
                    << avgSearchTime << "," << removeTime / removeCount << ","
                    << (removeCount > 0 ? totalLeftRotateTime / removeCount : 0)
                    << ","
                    << (removeCount > 0 ? totalRightRotateTime / removeCount
                                        : 0)
                    << "\n";

            std::cout << "Tamaño " << n << " ejecución " << run
                      << " completada.\n";
        }
    }
    outFile.close();
    std::cout << "Benchmark finalizado.\n";
    return 0;
}
