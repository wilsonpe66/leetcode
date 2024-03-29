// https://leetcode.com/problems/merge-two-sorted-lists/submissions/1216409553/

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
    static constexpr inline ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == list2) return list1;
        if (!list1) return list2;
        if (!list2) return list1;

        // Both list1 and list2 are not null.
        ListNode * head = nullptr;
        {
            auto & list = (list1->val <= list2->val) ? list1 : list2;
            head = list;
            list = list->next;
        }
        ListNode * cursor = head;
        while (list1 && list2 ) {
            auto & list = (list1->val <= list2->val) ? list1 : list2;
            cursor->next = list;
            list = list->next;
            cursor = cursor->next;
        }

        cursor->next = (!list1) ? list2 : list1;
        return head;
    }
};
