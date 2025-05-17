struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    int getSize(ListNode *head) {
        int size = 0;
        while (head != nullptr) {
            size++;
            head = head->next;
        }
        return size;
    }

    TreeNode *sortedListToBSTHelper(ListNode *&head, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;

        TreeNode *left = sortedListToBSTHelper(head, start, mid - 1);

        TreeNode *root = new TreeNode(head->val);

        head = head->next;

        root->left = left;
        root->right = sortedListToBSTHelper(head, mid + 1, end);

        return root;
    }

    TreeNode *sortedListToBST(ListNode *head) {
        int size = getSize(head);
        return sortedListToBSTHelper(head, 0, size - 1);
    }
};
