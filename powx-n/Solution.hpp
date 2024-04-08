// https://leetcode.com/problems/powx-n/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr double myPow(double x, long n) {
        if (x == 0) return 0.0;
        if (x == 1.0) return 1.0;

        // x is not 0.0 or 1.0

        if (n < 0) {
            n = 0 - n;
            x = 1 / x;
        }
        double base = x;
        double result = 1.0;
        for (;n; n >>= 1L) {
            if (n & 1) result *= base;
            base *= base;
        }

        return result;
    }
};
