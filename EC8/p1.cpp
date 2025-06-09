#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<int> findOrder(int numCourses,
                               std::vector<std::vector<int>> &prerequisites) {

        std::unordered_map<int, std::vector<int>> adj;

        std::vector<int> inDegree(numCourses, 0);

        for (const auto &prereq : prerequisites) {
            int course = prereq[0];
            int pre = prereq[1];
            adj[pre].push_back(course);
            inDegree[course]++;
        }

        std::queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> result;

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            result.push_back(course);

            for (int nextCourse : adj[course]) {
                inDegree[nextCourse]--;
                if (inDegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        if (result.size() == numCourses) {
            return result;
        } else {
            return {};
        }
    }
};
