// https://leetcode.com/problems/count-complete-tree-nodes/?envType=study-plan-v2&envId=top-interview-150

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
    static constexpr size_t get_left_depth(const TreeNode* root) {
        size_t max_depth = 0zu;
        for (;root; root = root->left) ++max_depth;
        return max_depth;
    }

public:
    static constexpr size_t countNodes(const TreeNode* root) {
        if (!root) return 0zu;
        size_t max_depth = get_left_depth(root);
        if (max_depth == 1zu) return 1zu;

        size_t shift = 1zu << (max_depth - 1zu);
        size_t result = shift - 1zu;
        size_t num_leaves = 0zu;
        do {
            --max_depth;
            shift >>= 1zu;
            if (max_depth == get_left_depth(root->right)) { 
                num_leaves |= shift;
                root = root->right;
                continue;
            }
            
            root = root->left;
        } while (max_depth > 1zu);

        // max_depth <= 1
        return result + num_leaves + max_depth;
    }
};
