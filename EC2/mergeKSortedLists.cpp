// Merge k Sorted Lists - You are given an array of k linked-lists lists, each
// linked-list is sorted in ascending order. Merge all the linked-lists into one
// sorted linked-list and return it.
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
#include <vector>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    auto compare = [](ListNode *a, ListNode *b) { return a->val > b->val; };
    std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(compare)>
        minHeap(compare);

    for (auto list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }

    ListNode *dummy = new ListNode(0);
    ListNode *tail = dummy;

    while (!minHeap.empty()) {
        ListNode *node = minHeap.top();
        minHeap.pop();
        tail->next = node;
        tail = tail->next;

        if (node->next) {
            minHeap.push(node->next);
        }
    }

    return dummy->next;
}
