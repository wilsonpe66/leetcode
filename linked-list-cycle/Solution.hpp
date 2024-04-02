// https://leetcode.com/problems/linked-list-cycle/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    static constexpr inline bool hasCycle(const ListNode *head) {
        if (!head) return false;

        auto turtle = head;
        auto rabit = head;
        if (!rabit->next || !rabit->next->next) return false;
        

        for (rabit = rabit->next->next; rabit; rabit = rabit->next->next) {
            if (turtle == rabit) return true;
            if (!rabit->next || !rabit->next->next) return false;
            turtle = turtle->next;
        }
        return false;
    }
};
