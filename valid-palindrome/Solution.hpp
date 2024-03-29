// https://leetcode.com/problems/valid-palindrome/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    constexpr static inline bool is_alpha(char ch) {
        return ('a' <= ch && ch <= 'z') || ('0' <= ch && ch <= '9');
    }

    constexpr static inline char to_norm(char ch) {
        ch += ('A' <= ch && ch <= 'Z') * ('a' - 'A');
        return is_alpha(ch) ? ch : ' ';
    }
public:
    static inline bool isPalindrome(string s) {
        if (s.empty()) return true;
        for (auto & ch: s) ch = to_norm(ch);

        size_t lb = 0L, ub = s.size() - 1L;

        while (lb < ub) {
            const char slb = s[lb];
            const char sub = s[ub];
            if (slb == ' ') ++lb;
            else if (sub == ' ') --ub;
            else {
                ++lb;
                --ub;
                if (slb != sub) return false;
            }
        }
        return true;
    }
};
