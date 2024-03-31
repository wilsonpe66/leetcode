// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr inline auto removeDuplicates(vector<int>& nums) {
        size_t sz = nums.size();
        if (sz <= 2L) return sz;

        size_t duplicate = 1L;
        size_t last_value = nums[0];
        for (size_t i = 1L; i < sz; ++i) {
            if (last_value == nums[i]) {
                ++duplicate;
                last_value = nums[i];
                continue;
            }
            last_value = nums[i];
            if (duplicate > 2L) {
                // shif left by duplicate;
                duplicate -= 2L;
                i -= duplicate;
                sz -= duplicate;
                for (size_t j = i; j < sz; ++j) nums[j] = nums[j + duplicate];
            }
            duplicate = 1L;
        }

        return sz - (duplicate > 2L) * (duplicate - 2L);
    }
};
