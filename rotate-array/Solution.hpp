// https://leetcode.com/problems/rotate-array/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    template<class T>
    static constexpr inline T exchange(T & b, T c) {
        T ret = b;
        b = c;
        return ret;
    }

    /* a < 2b */
    static constexpr inline size_t remainder (size_t a, size_t b) {
        if (a > (b<<1L)) return a % b;
        return a - (a >= b) * b;
    }

    /* a >= b > 0 */
    static constexpr inline auto gcd(size_t a, size_t b) {
        while (b) a = exchange(b, remainder(a, b));
        return a;
    }


public:
    static constexpr void rotate(vector<int>& nums, size_t k) {
        if (nums.empty()) return;
        const size_t sz = nums.size();
        k = remainder(k, sz);
        if (sz < 2 || !k) return;
        
        size_t gcd1 = 1L;
        if (k != 1L) gcd1 = gcd(sz, k);

        for (size_t offset = 0L; offset != gcd1; ++offset) {
            int value = nums[offset];
            size_t next = remainder(offset + k, sz);
            while (next != offset) {
                value = exchange(nums[next], value);
                next = remainder(next + k, sz);
            }
            nums[next] = value;
        }
    }
};
