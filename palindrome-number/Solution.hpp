// https://leetcode.com/problems/palindrome-number/

class Solution {
    constexpr static long reverse_positive(long x) {
        const long sign = (x < 0) ? -1L : 1L;
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

public:
    static constexpr inline bool isPalindrome(long x) {
        if ( x < 0 ) return false;
        return reverse_positive(x) == x;
    }
};
