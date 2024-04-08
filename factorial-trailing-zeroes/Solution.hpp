// https://leetcode.com/problems/factorial-trailing-zeroes/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr int trailingZeroes(int n) {
        int number_of_5s = 0;
        for (int n5 = n/5; n5; n5/=5) number_of_5s += n5;

        return number_of_5s;
    }
};
