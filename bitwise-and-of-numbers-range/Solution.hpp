// https://leetcode.com/problems/bitwise-and-of-numbers-range/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    // 0 <= left <= right <= 2^31 - 1
    static constexpr int rangeBitwiseAnd(int left, int right) {
        if (left == right || !right) return right;
        if (left + 1 == right) return left & right;
        
        // left + 1 < right

        size_t largest_p2 = 1L;
        for (;right >= largest_p2<<1L; largest_p2 <<=1L);
        if (left < largest_p2) return 0;
        if (left == largest_p2) return largest_p2;

        // largest_p2 < left <= right
        return largest_p2 | rangeBitwiseAnd(left - largest_p2, right - largest_p2);
    }
};

static inline bool dummy = [] {
    std::ios_base::sync_with_stdio(false);
    return false;
}();
