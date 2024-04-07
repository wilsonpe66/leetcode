// https://leetcode.com/problems/valid-anagram/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    constexpr static bool isAnagram(string_view s, string_view t) {
        if (s.size() != t.size()) return false;

        constexpr static char cnts_size = 'a' + 26;
        short s_cnts[cnts_size] = {};
        short t_cnts[cnts_size] = {};

        auto s_it = s.begin();
        for (auto t_it = t.begin(); t_it != t.end(); ++t_it) {
            ++s_cnts[*s_it];
            ++t_cnts[*t_it];
            ++s_it;
        }


        for (char ch = 'a'; ch != cnts_size; ++ch) if (s_cnts[ch] != t_cnts[ch]) return false;
        return true;
    }
};

