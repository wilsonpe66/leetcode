// https://leetcode.com/problems/single-number/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static int singleNumber(vector<int>& nums) {
        char cnts[60000] = {};
        int min_value = INT_MAX;
        for (const int num: nums) if (min_value > num) min_value = num;
        for (const int num: nums) ++cnts[num - min_value];
        for (size_t i = 0L; i < 60000; ++i) {
            if (cnts[i] == 1) return i + min_value;
        }
        return 0;
    }
};
