// Shortest Path in Binary Matrix - Given an n x n binary matrix grid, return
// the length of the shortest clear path in the matrix. If there is no clear
// path, return -1.
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0,
// 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
// All the visited cells of the path are 0.
// All the adjacent cells of the path are 8-directionally connected (i.e., they
// are different and they share an edge or a corner).
// The length of a clear path is the number of visited cells of this path.
/*
　　　　　 /＞    　フ
　　　　　|    _  _ |
　 　　　 /`ミ ＿x ノ
　　 　 /　　　 　|
　　　 /　 ヽ　　ﾉ
　 　 |　　|　|　|
　 /￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)__)
　\__二つ
*/
#include <queue>
#include <utility>
#include <vector>

int shortestPathBinaryMatrix(std::vector<std::vector<int>> &grid) {
    int n = grid.size();
    if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
        return -1;
    std::vector<std::vector<int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    std::queue<std::pair<int, int>> q;
    q.push({0, 0});
    grid[0][0] = 1;
    int pathLength = 1;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();
            if (x == n - 1 && y == n - 1)
                return pathLength;
            for (auto &dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (newX >= 0 && newX < n && newY >= 0 && newY < n &&
                    grid[newX][newY] == 0) {
                    q.push({newX, newY});
                    grid[newX][newY] = 1;
                }
            }
        }
        pathLength++;
    }
    return -1;
}
