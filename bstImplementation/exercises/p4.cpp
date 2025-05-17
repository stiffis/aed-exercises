#include <queue>
#include <vector>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
  public:
    std::vector<std::vector<int>> levelOrder(TreeNode *root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            std::vector<int> level;
            for (int i = 0; i < levelSize; ++i) {
                TreeNode *current = q.front();
                q.pop();
                level.push_back(current->val);
                if (current->left != nullptr) {
                    q.push(current->left);
                }
                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }
            result.push_back(level);
        }
        return result;
    }
};
