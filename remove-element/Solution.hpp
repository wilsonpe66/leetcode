// https://leetcode.com/problems/remove-element/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    int removeElement(vector<int>& nums, const int val) {
        size_t sz = nums.size();
        if (!sz) return sz;

        size_t result = 0L;
        size_t duplicates = 0L;
        for (size_t i = 0L; i < sz; ++i) {
            if (nums[i] == val) {
                ++duplicates;
                continue;
            }
            ++result;

            if (duplicates) i -= duplicates;

            sz -= duplicates;
            for (size_t j = i; j < sz; ++j) {
                nums[j] = nums[j + duplicates];
            }
            duplicates = 0L;
        }
        return result;
    }
};
