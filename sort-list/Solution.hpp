// https://leetcode.com/problems/sort-list/description/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    /**
        The number of nodes in the list is in the range [0, 5 * 104].
        -105 <= Node.val <= 105
     */
    static constexpr ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // both head and head->next is not nullptr and length > 1.

        size_t length = 0L;
        for (const ListNode * cursor = head; cursor; cursor = cursor->next) ++length;
        size_t half_length = (length>>1) - 1;

        ListNode * lower = head;
        ListNode * cursor;
        for (cursor = lower; cursor->next && half_length-- > 0; cursor = cursor->next) continue;
        ListNode * upper = cursor->next;
        cursor->next = nullptr;

        if (!lower) return sortList(upper);
        if (!upper) return sortList(lower);

        // Both lower and uppare are both not empty.

        lower = sortList(lower);
        upper = sortList(upper);

        // Merge sorted list.
        if (lower->val < upper->val) {
            head = lower;
            lower = lower->next;
        } else {
            head = upper;
            upper = upper->next;
        }

        cursor = head;
        while (lower && upper) {
            if (lower->val < upper->val) {
                cursor->next = lower;
                lower = lower->next;
            } else {
                cursor->next = upper;
                upper = upper->next;
            }
            cursor = cursor->next;
        }

        if (lower) cursor->next = lower;
        else cursor->next = upper;

        return head;
    }
};
