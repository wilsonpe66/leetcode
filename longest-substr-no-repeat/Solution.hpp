// https://leetcode.com/problems/longest-substring-without-repeating-characters/

class Solution {
    static constexpr inline size_t ZERO = 0L;
public:
    constexpr static inline auto max(int a, int b) {
        return (a >= b) ? a: b;
    }

    constexpr static inline int lengthOfLongestSubstring(string_view s) {
        if (s.empty()) return 0;

        size_t l = ZERO;
        size_t r = ZERO;
        int cmax = ZERO;
        const auto sz = s.size();
        for(r = ZERO; r < sz; ++r) {
            const auto ch = s[r];
            for (auto it = s.substr(l, r-l).find(ch); it != string_view::npos; it = s.substr(l, r-l).find(ch)) ++l;
            cmax = max(cmax, r-l+1);
        }
        return cmax;
    }
};
