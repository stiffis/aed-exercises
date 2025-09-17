// Insertion Sort List - Given the head of a singly linked list, sort the list
// using insertion sort, and return the sorted list's head. The steps of the
// insertion sort algorithm are as follows: Insertion sort iterates, consuming
// one input element each repetition and growing a sorted output list. At each
// iteration, insertion sort removes one element from the input data, finds the
// location it belongs within the sorted list, and inserts it there. It repeats
// until no input elements remain
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode *insertionSortList(ListNode *head) {
    if (!head || !head->next)
        return head;

    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *curr = head->next;
    head->next = nullptr;

    while (curr) {
        ListNode *prev = dummy;
        ListNode *next = curr->next;

        while (prev->next && prev->next->val < curr->val) {
            prev = prev->next;
        }

        curr->next = prev->next;
        prev->next = curr;
        curr = next;
    }

    return dummy->next;
}
