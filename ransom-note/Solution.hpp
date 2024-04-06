// https://leetcode.com/problems/ransom-note/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr bool canConstruct(string_view ransomNote, string_view magazine) {
        if (ransomNote.empty()) return true;
        if (magazine.empty() || ransomNote.size() > magazine.size()) return false;

        size_t cnts[26] = {};
        for (const char ch: magazine) ++cnts[ch - 'a'];

        for (const int ch: ransomNote) {
            auto & cnt = cnts[ch - 'a'];
            if (!cnt) return false;
            --cnt;
        }
        return true;
    }
};
