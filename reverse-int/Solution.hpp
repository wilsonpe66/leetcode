/* https://leetcode.com/problems/reverse-integer/ */

class Solution {
public:
    constexpr static long reverse(long x) {
        const int sign = (x < 0) ? -1L : 1L;
        x = x * sign;
        long result = 0L;
        while (x) {
            result = (10L*result) + (x%10L);
            x /= 10L;
        }

        result *= sign;
        if (INT_MAX < result || INT_MIN > result) return 0L;
        return result;
    }
};
