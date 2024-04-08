// https://leetcode.com/problems/length-of-last-word/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    /**
        1 <= s.length <= 104
        s consists of only English letters and spaces ' '.
        There will be at least one word in s.
    **/
    static constexpr size_t lengthOfLastWord(string_view str) {
        size_t sz = str.size();
        if (!sz) return 0L;

        size_t i_end = sz - 1L;
        while (i_end >= 1L && str[i_end] == ' ') --i_end;

        size_t i_begin = 0L;
        while (i_begin != sz && str[i_begin] == ' ') ++i_begin;

        sz  = i_end - i_begin + 1L;
        str = str.substr(i_begin, sz);

        if (!sz) return 0L;

        size_t i = sz - 1L;
        while (i >= 1L && str[i] != ' ') --i;

        return sz - (i && str[i] == ' ') * (i + 1L);
    }
};
