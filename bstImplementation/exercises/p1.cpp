#include <algorithm>
#include <cstdlib>
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
    int checkBalance(TreeNode *head) {
        if (head == nullptr)
            return 0;

        int leftHeight = checkBalance(head->left);
        if (leftHeight == -1)
            return -1;

        int rightHeight = checkBalance(head->right);
        if (rightHeight == -1)
            return -1;

        if (abs(leftHeight - rightHeight) > 1)
            return -1;

        return std::max(leftHeight, rightHeight) + 1;
    }

    bool isBalanced(TreeNode *head) { return checkBalance(head) != -1; }
};
