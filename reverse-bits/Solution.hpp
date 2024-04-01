// https://leetcode.com/problems/reverse-bits/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        for (int i = 0; i < 16; ++i) {
            const uint32_t upper_mask = 1<<(31-i);
            const uint32_t lower_mask = 1<<i;

            const uint32_t uval = (upper_mask & n);
            const uint32_t lval = (lower_mask & n);
            if (uval && !lval) {
                n |= lower_mask;
                n &= ~upper_mask;
            } else if (!uval && lval) {
                n |= upper_mask;
                n &= ~lower_mask;
            }
        }
        
        return n;
    }
};
