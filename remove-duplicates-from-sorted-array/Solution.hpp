// https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/1216937583/

class Solution {
public:
    static auto removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2L) return nums.size();

        size_t cursor = 1L;
        for (size_t i = cursor; i < nums.size(); ++i) {
            if (nums[i] > nums[cursor - 1] ) {
                nums[cursor++] = nums[i];
            }
        }
        nums.resize(cursor);
        nums.shrink_to_fit();
        return cursor;
    }
};
