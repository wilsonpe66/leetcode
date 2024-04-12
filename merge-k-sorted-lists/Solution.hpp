// https://leetcode.com/problems/merge-k-sorted-lists/description/?envType=study-plan-v2&envId=top-interview-150

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
    static constexpr inline ListNode* mergeLists(ListNode * lower, ListNode * upper) {
        if (!lower || lower == upper) return upper;
        if (!upper) return lower;

        // Both lower and upper are not nullptr and they are not the same list.

        ListNode * head;

        // Merge sorted list.
        if (lower->val < upper->val) {
            head = lower;
            lower = lower->next;
        } else {
            head = upper;
            upper = upper->next;
        }

        ListNode * cursor = head;

        while (lower && upper && lower != upper) {
            
            ListNode ** node = (lower->val < upper->val) ? &lower : &upper;

            cursor->next = *node;
            *node = (*node)->next;
            cursor = cursor->next;
        }

        if (lower) cursor->next = lower;
        else cursor->next = upper;

        return head;
    }

    // start < end
    static constexpr ListNode* mergeKLists(vector<ListNode*>& lists, size_t start, size_t end) {

        const auto size = end - start; // size >= 1
        
        // start < end;
        if (size == 1L) return lists[start];
        if (size == 2L) return mergeLists(lists[start], lists[end - 1L]);

        // size > 2
        const size_t mid = (size >> 1L) + start;

        auto lower = start < mid ? mergeKLists(lists, start, mid) : nullptr;
        auto upper = mid < end ? mergeKLists(lists, mid, end): nullptr;
        return mergeLists(lower, upper);
    }
public:
    /*
        k == lists.length
        0 <= k <= 10^4
        0 <= lists[i].length <= 500
        -10^4 <= lists[i][j] <= 10^4
        lists[i] is sorted in ascending order.
        The sum of lists[i].length will not exceed 10^4.
     */
    static constexpr ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        auto result= mergeKLists(lists, 0L, lists.size());
        return result;
    }
};
