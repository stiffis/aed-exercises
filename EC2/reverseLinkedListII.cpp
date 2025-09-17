// Reverse Linked List II - Given the head of a singly linked list and two
// integers left and right where left <= right, reverse the nodes of the list
// from position left to position right, and return the reversed list.
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
ListNode *reverseBetween(ListNode *head, int left, int right) {
    if (!head || left == right)
        return head;

    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;

    for (int i = 1; i < left; ++i) {
        prev = prev->next;
    }

    ListNode *curr = prev->next;
    ListNode *next = nullptr;

    for (int i = 0; i < right - left; ++i) {
        next = curr->next;
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }

    return dummy->next;
}
