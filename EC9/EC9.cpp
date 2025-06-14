#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

namespace std {
template <> struct hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
} // namespace std

const int DIRECTIONS[8][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                              {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

class Maze {
  private:
    std::vector<std::vector<int>> grid;
    int rows, cols;

  public:
    // INFO: 0 represents an empty cell, 1 represents an obstacle
    Maze(int r, int c) : rows(r), cols(c) {
        grid.resize(rows, std::vector<int>(cols, 0));
    }

    void setCell(int r, int c, int value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            grid[r][c] = value;
        }
    }

    int getCell(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return grid[r][c];
        }
        return -1;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Maze(std::vector<std::vector<int>> g)
        : grid(g), rows(g.size()), cols(g[0].size()) {}

    static double heuristic(int x1, int y1, int x2, int y2) {
        return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    void printMaze() const {
        for (const auto &row : grid) {
            for (int cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }
};

class PathfindingAlgorithm {
  protected:
    Maze &maze;
    std::pair<int, int> start, goal;

  public:
    PathfindingAlgorithm(Maze &m, std::pair<int, int> s, std::pair<int, int> g)
        : maze(m), start(s), goal(g) {}

    virtual void findPath() = 0;

    void printPath(const std::vector<std::pair<int, int>> &path) {
        if (path.empty()) {
            std::cout << "No path found!" << std::endl;
            return;
        }

        std::unordered_set<std::pair<int, int>> pathSet(path.begin(),
                                                        path.end());

        std::cout << "Maze with path:" << std::endl;
        for (int i = 0; i < maze.getRows(); ++i) {
            for (int j = 0; j < maze.getCols(); ++j) {
                if (pathSet.find({i, j}) != pathSet.end()) {
                    std::cout << "* "; // Path cell
                } else {
                    std::cout << maze.getCell(i, j) << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

class Dijkstra : public PathfindingAlgorithm {
  public:
    Dijkstra(Maze &maze, std::pair<int, int> start, std::pair<int, int> goal)
        : PathfindingAlgorithm(maze, start, goal) {}

    void findPath() override {
        auto start_time = std::chrono::high_resolution_clock::now();

        int rows = maze.getRows();
        int cols = maze.getCols();
        std::vector<std::vector<double>> dist(
            rows,
            std::vector<double>(cols, std::numeric_limits<double>::infinity()));

        std::vector<std::vector<std::pair<int, int>>> parent(
            rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

        std::priority_queue<std::pair<double, std::pair<int, int>>,
                            std::vector<std::pair<double, std::pair<int, int>>>,
                            std::greater<>>
            pq;

        dist[start.first][start.second] = 0.0;
        pq.push({0.0, start});

        while (!pq.empty()) {
            auto [currentDist, current] = pq.top();
            pq.pop();
            int x = current.first;
            int y = current.second;

            if (current == goal) {
                break;
            }

            for (const auto &dir : DIRECTIONS) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    double weight = maze.getCell(newX, newY);
                    if (weight >= 0 &&
                        currentDist + weight < dist[newX][newY]) {
                        dist[newX][newY] = currentDist + weight;
                        parent[newX][newY] = {x, y};
                        pq.push({dist[newX][newY], {newX, newY}});
                    }
                }
            }
        }

        std::vector<std::pair<int, int>> path;
        for (std::pair<int, int> at = goal; at != start;
             at = parent[at.first][at.second]) {
            path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::cout << "DIJKSTRA'S PATH:" << std::endl;
        std::cout << "================" << std::endl;
        printPath(path);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration =
            end_time - start_time;
        std::cout << "Execution time: " << duration.count() << " ms"
                  << std::endl
                  << std::endl;
    }
};

class GreedyBFS : public PathfindingAlgorithm {
  public:
    GreedyBFS(Maze &maze, std::pair<int, int> start, std::pair<int, int> goal)
        : PathfindingAlgorithm(maze, start, goal) {}

    void findPath() override {
        auto start_time = std::chrono::high_resolution_clock::now();

        int rows = maze.getRows();
        int cols = maze.getCols();
        std::vector<std::vector<bool>> visited(rows,
                                               std::vector<bool>(cols, false));
        std::priority_queue<std::pair<double, std::pair<int, int>>,
                            std::vector<std::pair<double, std::pair<int, int>>>,
                            std::greater<>>
            pq;

        pq.push({0.0, start});

        while (!pq.empty()) {
            auto [currentHeuristic, current] = pq.top();
            pq.pop();
            int x = current.first;
            int y = current.second;

            if (visited[x][y])
                continue;
            visited[x][y] = true;

            if (current == goal) {
                break;
            }

            for (const auto &dir : DIRECTIONS) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                    !visited[newX][newY]) {
                    double h =
                        Maze::heuristic(newX, newY, goal.first, goal.second);
                    pq.push({h, {newX, newY}});
                }
            }
        }

        std::vector<std::pair<int, int>> path;
        for (std::pair<int, int> at = goal; at != start;) {
            path.push_back(at);
            bool found = false;
            for (const auto &dir : DIRECTIONS) {
                int newX = at.first + dir[0];
                int newY = at.second + dir[1];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                    visited[newX][newY]) {
                    at = {newX, newY};
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::cout << "GREEDY BFS PATH:" << std::endl;
        std::cout << "================" << std::endl;
        printPath(path);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration =
            end_time - start_time;
        std::cout << "Execution time: " << duration.count() << " ms"
                  << std::endl
                  << std::endl;
    }
};

class AStar : public PathfindingAlgorithm {
  public:
    AStar(Maze &maze, std::pair<int, int> start, std::pair<int, int> goal)
        : PathfindingAlgorithm(maze, start, goal) {}

    void findPath() override {
        auto start_time = std::chrono::high_resolution_clock::now();

        int rows = maze.getRows();
        int cols = maze.getCols();

        std::vector<std::vector<double>> gScore(
            rows,
            std::vector<double>(cols, std::numeric_limits<double>::infinity()));

        std::vector<std::vector<double>> fScore(
            rows,
            std::vector<double>(cols, std::numeric_limits<double>::infinity()));

        std::vector<std::vector<std::pair<int, int>>> parent(
            rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

        gScore[start.first][start.second] = 0.0;
        fScore[start.first][start.second] =
            Maze::heuristic(start.first, start.second, goal.first, goal.second);

        std::priority_queue<std::pair<double, std::pair<int, int>>,
                            std::vector<std::pair<double, std::pair<int, int>>>,
                            std::greater<>>
            openSet;

        openSet.push({fScore[start.first][start.second], start});

        while (!openSet.empty()) {
            auto [currentFScore, current] = openSet.top();
            openSet.pop();
            int x = current.first;
            int y = current.second;

            if (current == goal) {
                break;
            }

            for (const auto &dir : DIRECTIONS) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    double weight = maze.getCell(newX, newY);
                    if (weight >= 0) {
                        double tentativeGScore = gScore[x][y] + weight;
                        if (tentativeGScore < gScore[newX][newY]) {
                            parent[newX][newY] = {x, y};
                            gScore[newX][newY] = tentativeGScore;
                            fScore[newX][newY] =
                                gScore[newX][newY] +
                                Maze::heuristic(newX, newY, goal.first,
                                                goal.second);
                            openSet.push({fScore[newX][newY], {newX, newY}});
                        }
                    }
                }
            }
        }

        std::vector<std::pair<int, int>> path;
        for (std::pair<int, int> at = goal; at != start;
             at = parent[at.first][at.second]) {
            path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::cout << "A* PATH:" << std::endl;
        std::cout << "========" << std::endl;
        printPath(path);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration =
            end_time - start_time;
        std::cout << "Execution time: " << duration.count() << " ms"
                  << std::endl
                  << std::endl;
    }
};

void demonstratePathfinding2() {
    const int N = 1000;
    Maze maze(N, N);

    for (int i = 0; i < N; ++i) {
        maze.setCell(i, i, 1);
    }
    maze.setCell(0, 0, 0);
    maze.setCell(N - 1, N - 1, 0);

    for (int i = 0; i < N; ++i) {
        if (i != N / 2)
            maze.setCell(i, N / 2, 1);
    }

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> goal = {N - 1, N - 1};

    std::cout << "Maze of size " << N << "x" << N << " created.\n";
    // maze.printMaze();

    Dijkstra dijkstra(maze, start, goal);
    dijkstra.findPath();

    GreedyBFS greedyBFS(maze, start, goal);
    greedyBFS.findPath();

    AStar aStar(maze, start, goal);
    aStar.findPath();
}
int main() {
    demonstratePathfinding2();
    return 0;
}
