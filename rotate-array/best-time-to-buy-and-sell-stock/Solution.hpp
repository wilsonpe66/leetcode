// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/?envType=study-plan-v2&envId=top-interview-150

static inline bool dummy = [] {
    std::ios_base::sync_with_stdio(false);
    return false;
}();

class Solution {
    constexpr static int min(int a, int b) {
        return (a<=b) * (a-b) + b;
    }

    constexpr static int max(int a, int b) {
        return (a>=b) * (a-b) + b;
    }    

public:
    constexpr static int maxProfit(const vector<int>& prices) {
        size_t sz = prices.size();
        if (sz < 2) return 0;

        int min_val = prices[0L];
        int max_proffit  = max(0, prices[1L] - min_val);
        --sz;
        for (size_t i = 0L; i != sz; ++i) {
            min_val = min(prices[i], min_val);
            max_proffit = max(max_proffit, prices[i + 1L] - min_val);
        }
        return max_proffit;
    }
};
