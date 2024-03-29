// https://leetcode.com/problems/add-two-numbers/

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
    constexpr static inline int BASE = 10;

    static constexpr auto getNextRemainder(char value, char & carry) {
        const int sum = value + carry;
        if (sum > 9) {
            carry = 1;
            return sum - 10;
        }
        carry = 0;
        return sum;
    }

    static constexpr inline bool size_compare(const ListNode* l1, const ListNode* l2) {
        while (l1 && l2) {
            l1 = l1->next;
            l2 = l2->next;
        }
        return l2;
    }

public:
    static inline ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        // l1 and l2 are both not nullprt;
        const bool test = size_compare(l1, l2);

        ListNode * const head = test ? l2 : l1;
        const ListNode * other = test ? l1 : l2;
        ListNode * cursor = head;
        char carry = 0;

        cursor->val = getNextRemainder((char)cursor->val + other->val, carry);
        if (!cursor->next) {
            if (carry) cursor->next = new ListNode(carry);
            return head;
        }

        cursor = cursor->next;
        other = other->next;
        // size(cursor) >= size(other) && cursor != null
        while (other && cursor->next) {
            cursor->val = getNextRemainder(cursor->val + other->val, carry);
            cursor = cursor->next;
            other = other->next;
        }

        // size(cursor) >= size(other) && cursor != null and (cursor->next is null or other is null)
        if (other && !cursor->next) {
            cursor->val = getNextRemainder(cursor->val + other->val, carry);
            if (carry) cursor->next = new ListNode(carry);
            return head;
        }

        // size(cursor) >= size(other) && cursor != null and cursor->next != null and other == null
        while (cursor->next) {
            cursor->val = getNextRemainder(cursor->val, carry);
            cursor = cursor->next;
        }

        cursor->val = getNextRemainder(cursor->val, carry);
        if (carry) cursor->next = new ListNode(carry);
        return head;
    }

    static inline ListNode* addTwoNumbersNonDestructiveAdd(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        // l1 and l2 are both not nullprt;

        ListNode * head = nullptr;
        char carry = 0;
        {
            const char sum = l1->val + l2->val + carry;
            carry = sum / BASE;
            head = new ListNode(sum % BASE);
            l1 = l1->next;
            l2 = l2->next;
        }
        auto cursor = head;

        while (l1 && l2) {
            const char sum = l1->val + l2->val + carry;
            carry = sum / BASE;
            cursor->next = new ListNode(sum % BASE);
            cursor = cursor->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        auto & ll = l1 ? l1 : l2;
        while (ll) {
            const char sum = ll->val + carry;
            carry = sum / BASE;

            cursor->next = new ListNode(sum % BASE);
            cursor = cursor->next;
            ll = ll->next;
        }

        if (carry) {
            cursor->next = new ListNode(carry);
        }
        return head;
    }
};
