// https://leetcode.com/problems/two-sum/?envType=study-plan-v2&envId=top-interview-150

class Solution {

public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::multimap<int, int> s;
        {
            size_t index = 0;
            for (const int num : nums) s.insert(decltype(s)::value_type(num,index++));
        }

        for (auto [num, index]: s) {
            if (auto it = s.find(target-num); s.end() != it) {
                if (index != it->second)
                return {index, it->second};
            }
        }
        return {};
    }
};
