// https://leetcode.com/problems/valid-parentheses/description/

class Solution {
public:
    static constexpr inline bool isValid(string_view s) {
        char buff[4000] = {};
        size_t sz = 0;
        if (s.empty()) return true;

        for (const char ch: s) {
            switch (ch) {
                case '[':
                case '(':
                case '{': {
                    buff[sz++] = ch;
                    break;
                }
                case '}': {
                    if (!sz || buff[sz-1] != '{') return false;
                    --sz;
                    break;
                }
                case ']': {
                    if (!sz || buff[sz-1] != '[') return false;
                    --sz;
                    break;
                }
                case ')': {
                    if (!sz || buff[sz-1] != '(') return false;
                    --sz;
                    break;
                }
            }
        }
        return sz == 0;
    }
};
