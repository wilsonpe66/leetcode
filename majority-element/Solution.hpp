// https://leetcode.com/problems/majority-element/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static int majorityElement(vector<int>& nums) {
        unordered_map<int, size_t> m;
        m.reserve(50000);
        for (const int num: nums) ++m[num];

        const size_t maj = (nums.size() / 2) + 1;
        for (const auto [val, cnt]: m) {
            if (maj <= cnt) return val;
        }
        return 0;
    }
};
