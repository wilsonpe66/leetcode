// https://leetcode.com/problems/symmetric-tree/?envType=study-plan-v2&envId=top-interview-150

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
    constexpr static bool isSymetric(const TreeNode* p, const TreeNode* q, bool flipLeftP) {
        while(true) {
            if (!p && !q || p == q) return true;
            if ((p && !q) || (!p && q)) return false;

            // p and q are both not nullptr
            if (p->val != q->val || !isSymetric(p->left, q->right, flipLeftP)) return false;
            
            p = p->right;
            q = q->left;
        }
    }


public:
    bool isSymmetric(const TreeNode* root) {
        if (!root) return true;
        return isSymetric(root->left, root->right, true);
    }
};
