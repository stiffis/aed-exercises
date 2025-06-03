#include "BenchmarkRedBlackTree.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const int maxN = 10000;
    const int step = 500;
    const int runsPerSize = 5;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream outFile("benchmark_results.csv");
    outFile << "Size,Run,Insert_us,SearchExisting_us,SearchMissing_us,Remove_"
               "us,LeftRotate_us,RightRotate_us\n";

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

            // Sumar tiempos inserción
            long long totalInsertTime = 0;
            for (auto &p : tree.getInsertBenchmark()) {
                if (p.second == n)
                    totalInsertTime += p.first;
            }

            // Buscar nodos existentes (medir tiempo en microsegundos)
            auto startSearchExist = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; ++i) {
                auto res = tree.search(values[i]);
                if (!res)
                    std::cerr << "Error: nodo no encontrado!" << std::endl;
            }
            auto endSearchExist = std::chrono::high_resolution_clock::now();
            long long searchExistTime =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    endSearchExist - startSearchExist)
                    .count();

            // Buscar nodos no existentes
            std::vector<int> missingValues;
            for (int i = maxN + 1; i <= maxN + n; ++i)
                missingValues.push_back(i);
            auto startSearchMiss = std::chrono::high_resolution_clock::now();
            for (int val : missingValues) {
                auto res = tree.search(val);
                if (res)
                    std::cerr << "Error: nodo inexistente encontrado!"
                              << std::endl;
            }
            auto endSearchMiss = std::chrono::high_resolution_clock::now();
            long long searchMissingTime =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    endSearchMiss - startSearchMiss)
                    .count();

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

            outFile << n << "," << run << "," << totalInsertTime / n << ","
                    << searchExistTime / n << "," << searchMissingTime / n
                    << "," << removeTime / removeCount << ","
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
