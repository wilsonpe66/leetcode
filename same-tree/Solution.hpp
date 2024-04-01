// https://leetcode.com/problems/same-tree/submissions/1220462190/?envType=study-plan-v2&envId=top-interview-150

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
public:
    constexpr static bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q || p == q) return true;
        if ((p && !q) || (!p && q)) return false;

        // p and q are both not nullptr

        return p->val == q->val
            && isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
};
