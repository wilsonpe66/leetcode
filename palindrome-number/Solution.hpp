// https://leetcode.com/problems/palindrome-number/

class Solution {
    constexpr static long reverse_positive(long x) {
        const long sign = 1L - ((x < 0L)<<1);
        x *= sign;
        long result = 0L;
        while (x) {
            result = (10L*result) + (x%10L);
            x /= 10L;
        }

        return (INT_MAX >= result) * result * sign;
    }

public:
    static constexpr inline bool isPalindrome(long x) {
        return ( x >= 0 ) && reverse_positive(x) == x;
    }
};
