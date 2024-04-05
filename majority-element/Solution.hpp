// https://leetcode.com/problems/majority-element/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr inline int majorityElement(const vector<int>& nums) {
        if (nums.empty()) return INT_MIN;
        long majority_el = nums[0];
        long count = 1L;
        for (auto it = nums.begin() + 1L; it != nums.end(); ++it) {
            const bool is_count_zero = !count;
            const int diff = *it - majority_el;
            majority_el = is_count_zero * diff + majority_el;
            count -= 1L - ((is_count_zero || !diff)<<1L);
        }
        return majority_el;
    }
};
