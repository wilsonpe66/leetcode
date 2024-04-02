// https://leetcode.com/problems/climbing-stairs/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    static constexpr size_t SIZE= 46L;
    using TableType = std::array<std::array<size_t, SIZE>, SIZE>;
        
    static constexpr TableType make_choose_list() {
        TableType ret {{}};
        
        for (std::size_t i = 0; i < SIZE; ++i) {
            auto & arr = ret[i];
            arr[0] = 1;
            arr[1] = i;
        }

        for (std::size_t i = 1L; i < SIZE; ++i) {
            const auto & arr_sm = ret[i - 1];
            auto & arr_rs = ret[i];
            for (std::size_t j = 1L; j <= i; ++j) {
                arr_rs[i] = arr_sm[j] + arr_sm[j - 1L];
                arr_rs[i - j] = arr_rs[i];
            }
        }
        return ret;
    };

    static inline TableType climbed_stars = make_choose_list();

public:
    static constexpr int climbStairs(int n) {
        if (n < 0 || n >= SIZE) return -1;
        
        int result = 0;
        for (std::size_t i = 0; i <= n; i += 2L) {
            int num_of_2s = i>>1;
            const int num_of_1s = n - i;
            const int k = num_of_1s + num_of_2s;
            num_of_2s = k < (num_of_2s<<1) ? k - num_of_2s: num_of_2s;
            result += climbed_stars[k][num_of_2s];
        }
        return result;

    }
};

