// https://leetcode.com/problems/sum-root-to-leaf-numbers/?envType=study-plan-v2&envId=top-interview-150

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    struct S {
        size_t result;
        size_t multiplier = 0;
    };

    static constexpr inline size_t max(size_t a, size_t b) {
        return (a > b) * (a-b) + b;
    }

    // root is not nullptr
   static constexpr inline S sumNumbers_private(const TreeNode* root) {
        if (!root) return {0, 0L};

        if (!root->left && !root->right) return {(size_t)root->val, 1L};

        const S sl = sumNumbers_private(root->left);
        const S sr = sumNumbers_private(root->right);
        
        const size_t multiplier = (sl.multiplier + sr.multiplier) * 10L;
        return {multiplier * root->val + sl.result + sr.result, multiplier};
   }

public:
    static constexpr int sumNumbers(const TreeNode* root) {
        return sumNumbers_private(root).result;
    }
};

