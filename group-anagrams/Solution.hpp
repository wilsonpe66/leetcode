// https://leetcode.com/problems/group-anagrams/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    static inline string hash(string_view str) {
        char key[27] = {};


        for (auto &ch: key) ch = 1;
        key[26] = 0;

        char larest_char = 0;
        for (auto ch: str) {
            ch -= 'a';
            ++key[ch];
            larest_char = (ch > larest_char) * (ch - larest_char) + larest_char;
        }
        key[larest_char + 1] = 0;
        return key;
    }

public:
    /**
    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters.
    */
    static vector<vector<string>> groupAnagrams(const vector<string>& strs) {
        unordered_map<string, vector<string>> mapping;
        for (const auto & str: strs) mapping[hash(str)].push_back(str);

        vector<vector<string>> result;
        result.reserve(mapping.size());
        for (auto & [_, anagram_group]: mapping) result.push_back(std::move(anagram_group));

        return result;
    }
};
