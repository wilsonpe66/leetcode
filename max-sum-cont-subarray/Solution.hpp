class Solution {
public:
    template<typename T>
    inline constexpr static auto max(T a, T b) { 
        return (b <= a) ? a: b;
    }

    inline constexpr static int maxSubArray(const vector<int>& nums) {
        int partial_max = INT_MIN;
        int max_upto_here = 0;

        for (const int num : nums) {
            max_upto_here += num;
            partial_max = max(partial_max, max_upto_here);
            max_upto_here = max(max_upto_here, 0);
        }
        return partial_max;
    }
};


