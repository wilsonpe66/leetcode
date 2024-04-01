// https://leetcode.com/problems/sqrtx/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    constexpr static int mySqrt(long x) {
        if (x < 1L) return 0;
        long lb = 0L;
        long ub = 46341L;
        while (lb < ub) {
            long mid = (lb + ub)>>1;
            long midsq = mid * mid;
            if (x == midsq ) return mid;
            ++mid;
            midsq = mid * mid;
            if (x == midsq ) return mid;

            if (x < midsq) {
                ub = mid - 1;
            } else {
                lb = mid;
            }
        }
        return lb;
    }
};
