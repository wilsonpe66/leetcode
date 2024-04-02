// https://leetcode.com/problems/is-subsequence/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr bool isSubsequence(string_view s, string_view t) {
        if (s.empty()) return true;
        if (t.empty() || s.size() > t.size()) return false;

        size_t i = 0L;
        size_t j = 0L;
        while (j != s.size() && i != t.size()) {
            if (s[j] == t[i]) ++j;
            ++i;
        }

        return j == s.size();
    }
};
