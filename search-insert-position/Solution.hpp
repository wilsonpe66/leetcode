// https://leetcode.com/problems/search-insert-position/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr size_t searchInsert(const vector<int>& nums, const int target) {
        if (nums.empty()) return 0L;

        size_t lb = 0L;
        size_t ub = nums.size();

        size_t mid = (ub + lb)>>1L;
        while (lb < ub && nums[mid] != target) {
            const size_t test = (nums[mid] < target);
            const size_t ntest = !test;
            lb = test * (mid + 1L) + ntest * lb;
            ub = test * ub + ntest * mid ;
            mid = (ub + lb)>>1L;
        }
        return mid;
    }
};
