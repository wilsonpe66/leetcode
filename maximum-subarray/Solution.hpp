// https://leetcode.com/problems/maximum-subarray/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    template<typename T>
    inline constexpr static auto max(T a, T b) { 
        return (a < b) * (b-a) + a;
    }

    inline constexpr static int maxSubArray(const vector<int>& nums) {
        long partial_max = INT_MIN;
        long max_upto_here = 0;

        for (const long num : nums) {
            max_upto_here += num;
            partial_max = max(partial_max, max_upto_here);
            max_upto_here = max(max_upto_here, 0L);
        }
        return partial_max;
    }
};

