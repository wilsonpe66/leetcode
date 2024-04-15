// https://leetcode.com/problems/candy/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    static constexpr inline int max(int a, int b) {
        return (a > b) * (a-b) + b;
    }
public:
    /**
        n == ratings.length
        1 <= n <= 2 * 10^4
        0 <= ratings[i] <= 2 * 10^4
      */
    static int candy(const vector<int> & ratings) {
        size_t sz = ratings.size();
        if (sz < 2) return sz;
        vector<int> candies(sz, 1L);
        
        size_t prev_index = 0L;
        for (size_t current_index = 1L; current_index != sz; ++current_index) {
            const int tmp = 1L + candies[prev_index];
            if (ratings[prev_index] < ratings[current_index] && candies[current_index] < tmp) {
                candies[current_index] = tmp;
            }
            prev_index = current_index;
        }

        prev_index = sz - 1L;
        for (size_t current_index = prev_index - 1L; current_index; --current_index) {
            const int tmp = 1L + candies[prev_index];
            if (ratings[prev_index] < ratings[current_index] && candies[current_index] < tmp) {
                candies[current_index] = tmp;
            }
            prev_index = current_index;
        }
        if (ratings[1L] < ratings[0L]) {
            candies[0L] = max(candies[0L], 1L + candies[1L]);
        }

        size_t total_candies = 0L;
        for (size_t candy: candies) {
            total_candies += candy;
        }
        return total_candies;
    }
};
