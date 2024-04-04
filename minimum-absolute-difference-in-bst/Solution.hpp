// https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/?envType=study-plan-v2&envId=top-interview-150

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
    static constexpr inline int min(int a, int b) {
        const bool test = (a <= b);
        return test * a + (!test) * b;
    }
public:
    // All nodes values are distinct
    static constexpr int getMinimumDifference(const TreeNode* root) {
        int min_dist = INT_MAX;
        
        while (root && min_dist > 1) {
            if (root->left) {
                min_dist = min(min_dist, getMinimumDifference(root->left));
                if (min_dist == 1) return 1;

                const TreeNode * cursor = root->left;
                for(;cursor->right; cursor = cursor->right) continue;
                min_dist = min(min_dist, root->val - cursor->val);
            }

            if (root->right) {
                const TreeNode * cursor = root->right;
                for(;cursor->left; cursor = cursor->left) continue;
                min_dist = min(min_dist, cursor->val - root->val);
                
            }

            root = root->right;
        }
        return min_dist;
    }
};
