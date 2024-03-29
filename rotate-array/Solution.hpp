// https://leetcode.com/problems/rotate-array/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    template<class T>
    static constexpr inline void exchange(T & a, T & b, T c) {
        a = b;
        b = c;
    }

    /* a >= b */
    static constexpr inline auto gcd(size_t a, size_t b) {
        while (b != 0) exchange(a, b, a % b);
        return a;
    }

    /* a < 2b */
    static constexpr inline size_t remainder(size_t a, size_t b) {
        return (a >= b) ? a - b: a;
    }
public:
    static constexpr inline void rotate(vector<int>& nums, size_t k) {
        const size_t sz = nums.size();
        if (sz < 2) return;
        k = k % sz;
        if (k == 0) return;

        const size_t gcd1 = k > 1 ? gcd(sz, k): 1;
        for (size_t offset = 0L; offset < gcd1; ++offset) {
            int value = nums[offset];
            size_t next = remainder(offset + k, sz);
            while (next != offset) {
                exchange(value, nums[next], value);
                next = remainder(next + k, sz);
            }
            nums[next] = value;
        }
    }
};
