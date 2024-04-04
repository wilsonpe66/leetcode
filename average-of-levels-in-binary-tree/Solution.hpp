// https://leetcode.com/problems/average-of-levels-in-binary-tree/?envType=study-plan-v2&envId=top-interview-150

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
    static vector<double> averageOfLevels(const TreeNode* root) {
        if (!root) return {};

        vector<double> result;
        result.reserve(10000L);

        size_t last_depth = INT_MAX;
        size_t n = 0L;
        double acc = 0.0;
        queue<pair<const TreeNode*, size_t>> q;
        q.emplace(root, 0L);
        while (!q.empty()) {
            const auto & state = q.front(); // Get and POP at the same time
            const auto & cursor = state.first;
            const auto & depth = state.second;
            const size_t next_depth = depth + 1L;

            if (cursor->left) q.emplace(cursor->left, next_depth);
            if (cursor->right) q.emplace(cursor->right, next_depth);

            if (depth != last_depth) {
                last_depth = depth;
                if (n) result.push_back(acc / n);
                n = 0L;
                acc = 0.0;
            }

            ++n;
            acc += state.first->val;
            q.pop();
        }

        if (n) result.push_back(acc / n);
        return result;
    }
};
