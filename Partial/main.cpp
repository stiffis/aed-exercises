#include <iostream>
#include <string>
using namespace std;
struct ListNode {
    string val;
    ListNode *prev;
    ListNode *next;
    ListNode(string v) : val(v), prev(nullptr), next(nullptr) {}
};
struct TreeNode {
    string val;
    ListNode *chronoNode;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string v, ListNode *chrono)
        : val(v), chronoNode(chrono), left(nullptr), right(nullptr) {}
};
class SearchHistory {
  private:
    TreeNode *root;
    ListNode *head;
    ListNode *tail;

  public:
    SearchHistory() : root(nullptr), head(nullptr), tail(nullptr) {}
    //(O(log n))
    void add(const string &term) {
        if (!findBST(root, term)) {
            ListNode *newNode = new ListNode(term);
            appendList(newNode);
            root = insertBST(root, term, newNode);
        }
    }
    // O(n)
    void showChronological() {
        cout << "[";
        ListNode *current = head;
        bool first = true;
        while (current) {
            if (!first)
                cout << ", ";
            cout << "\"" << current->val << "\"";
            first = false;
            current = current->next;
        }
        cout << "]\n";
    }
    // O(n)
    void showAlphabetical() {
        cout << "[";
        bool first = true;
        inorderBST(root, first);
        cout << "]\n";
    }
    //(O(log n))
    void remove(const string &term) {
        TreeNode *node = findBST(root, term);
        if (!node)
            return;
        removeList(node->chronoNode);
        root = removeBST(root, term);
    }

  private:
    void appendList(ListNode *node) {
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    void removeList(ListNode *node) {
        if (!node)
            return;
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;
        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;
        delete node;
    }
    TreeNode *insertBST(TreeNode *node, const string &term,
                        ListNode *chronoNode) {
        if (!node)
            return new TreeNode(term, chronoNode);
        if (term < node->val)
            node->left = insertBST(node->left, term, chronoNode);
        else if (term > node->val)
            node->right = insertBST(node->right, term, chronoNode);
        return node;
    }
    TreeNode *findBST(TreeNode *node, const string &term) {
        if (!node)
            return nullptr;
        if (term == node->val)
            return node;
        if (term < node->val)
            return findBST(node->left, term);
        else
            return findBST(node->right, term);
    }
    void inorderBST(TreeNode *node, bool &first) {
        if (!node)
            return;
        inorderBST(node->left, first);
        if (!first)
            cout << ", ";
        cout << "\"" << node->val << "\"";
        first = false;
        inorderBST(node->right, first);
    }
    TreeNode *findMinBST(TreeNode *node) {
        while (node && node->left)
            node = node->left;
        return node;
    }
    TreeNode *removeBST(TreeNode *node, const string &term) {
        if (!node)
            return nullptr;
        if (term < node->val)
            node->left = removeBST(node->left, term);
        else if (term > node->val)
            node->right = removeBST(node->right, term);
        else {
            if (!node->left) {
                TreeNode *rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                TreeNode *leftChild = node->left;
                delete node;
                return leftChild;
            }
            TreeNode *minNode = findMinBST(node->right);
            node->val = minNode->val;
            node->chronoNode = minNode->chronoNode;
            node->right = removeBST(node->right, minNode->val);
        }
        return node;
    }
};
int main() {
    SearchHistory history;
    history.add("cpp");
    history.add("estructura");
    history.add("arbol");
    history.add("codigo");
    history.add("cpp");
    history.add("datos");
    history.showChronological();
    history.showAlphabetical();
    history.remove("codigo");
    history.showChronological();
    history.showAlphabetical();
    return 0;
}
/*
 */
