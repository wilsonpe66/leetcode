// https://leetcode.com/problems/contains-duplicate-ii/description/?envType=study-plan-v2&envId=top-interview-150
class Solution {
public:
    /*
    1 <= nums.length <= 105
    -109 <= nums[i] <= 109
    0 <= k <= 105
    */
    static bool containsNearbyDuplicate(const vector<int>& nums, int k) {
        const size_t nums_sz = nums.size();
        if (!k || nums_sz < 2L) return false;

        // k > 0 and nums has at least 2 numbers

        unordered_map<int, size_t> mapping;
        for (size_t i = 0L; i != nums_sz; ++i) {
            const int num = nums[i];
            auto it = mapping.find(num);
            if (it == mapping.end()) {
                mapping[num] = i;
                continue;
            }

            auto & index = it->second;
            if(i - index <= k) return true;
            index = i;
        }

        return false;
    }
};

