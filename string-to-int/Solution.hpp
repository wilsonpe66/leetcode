// https://leetcode.com/problems/string-to-integer-atoi/description/

class Solution {
    static constexpr inline long clamp(long number) {
        if (number < INT_MIN) return INT_MIN;
        if (number > INT_MAX) return INT_MAX;
        return number;
    }
public:

    static constexpr inline int myAtoi(string_view s) {
        if (s.empty()) return 0;
        auto ch = s[0];
        while (!s.empty() && (ch == ' ' || ch == '\t')) {
            s = s.substr(1);
            ch = s[0];
        }

        const long sign = (ch == '-') ? -1 : 1;
        if (!s.empty() && (ch == '-' || ch == '+')) {
            s = s.substr(1);
            ch = s[0];
        }

        while (!s.empty() && s[0] == '0') {
            s = s.substr(1);
        }

        long result = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            const auto ch = s[i];
            if ((ch < '0' || ch > '9') || ch == '-' || ch == '+') break;
            if (result < INT_MIN || result > INT_MAX) return clamp(sign * result);
            result = (10L*result) + ((long)(ch-'0'));
            
        }

        return clamp(sign * result);
    }
};
