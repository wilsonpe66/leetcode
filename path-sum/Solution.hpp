// https://leetcode.com/problems/path-sum/?envType=study-plan-v2&envId=top-interview-150

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
    // root is not nullptr 
    static constexpr inline bool hasPathSumPrivate(const TreeNode* root, int targetSum) {
        for (targetSum -= root->val; root->left || root->right; targetSum -= root->val) {
            // root is not a leaf.
            if (root->left && root->right) {
                if (hasPathSumPrivate(root->left, targetSum)) return true;
                root = root->right;
                continue;
            }
            // root->left or root->right is not nullptr
            root = root->left ? root->left : root->right;

            // root is not nullptr
        }

        // root is a leaf.
        return !targetSum;
    }
public:
    static constexpr bool hasPathSum(const TreeNode* root, int targetSum) {
        return root && hasPathSumPrivate(root, targetSum);
    }
};
