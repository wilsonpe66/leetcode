// https://leetcode.com/problems/number-of-1-bits/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    constexpr static int hammingWeight(int n) {
        int result = 0;
        for (; n > 0; n>>=1) result += (n & 1);
        return result;
    }
};
