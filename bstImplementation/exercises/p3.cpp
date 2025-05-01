
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  public:
    TreeNode *lowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node == p || node == q) {
            return node;
        }
        TreeNode *leftLCA = lowestCommonAncestor(node->left, p, q);
        TreeNode *rightLCA = lowestCommonAncestor(node->right, p, q);
        if (leftLCA && rightLCA) {
            return node;
        }
        return leftLCA ? leftLCA : rightLCA;
    }
};
