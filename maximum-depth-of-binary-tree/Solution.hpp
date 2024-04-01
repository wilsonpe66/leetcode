// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150

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
    static constexpr inline int max(int a, int b) {
        return (a<=b) * b + (a>b) * a;
    }
public:
    static constexpr int maxDepth(const TreeNode* root) {
        int max_depth = 0;
        int depth = 0;
        for (;root; root = root->left) max_depth = max(max_depth, (++depth) + maxDepth(root->right));
        return max(max_depth, depth);
    }
};
