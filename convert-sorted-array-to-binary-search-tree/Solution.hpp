// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/?envType=study-plan-v2&envId=top-interview-150

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
    // nums is not empty();
    // end < nums.size();
    static TreeNode* BinaryInsert(const vector<int>& nums, size_t start, size_t end)
    {
        if (start > end) return nullptr;

        const size_t mid = (start + end)>>1L;
        TreeNode * const root = new TreeNode(nums[mid], mid ? BinaryInsert(nums, start, mid - 1L) : nullptr, nullptr);
        
        TreeNode * cursor = root;
        start = mid + 1L;
        while (start <= end) {
            const size_t mid = (start + end)>>1L;
            cursor->right = new TreeNode(nums[mid], mid ? BinaryInsert(nums, start, mid - 1L) : nullptr, nullptr);

            cursor = cursor->right;
            start = mid + 1L;
        }
        return root;
    }

public:
    static inline TreeNode* sortedArrayToBST(const vector<int>& nums) 
    {
        if (nums.empty()) return nullptr;
        return BinaryInsert(nums, 0L, nums.size() - 1L);
    }
};
