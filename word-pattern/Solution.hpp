// https://leetcode.com/problems/word-pattern/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    /*
    1 <= pattern.length <= 300
    pattern contains only lower-case English letters.
    1 <= s.length <= 3000
    s contains only lowercase English letters and spaces ' '.
    s does not contain any leading or trailing spaces.
    All the words in s are separated by a single space.
    */
    static bool wordPattern(string_view pattern, string_view s) {
        size_t pattern_size = pattern.size();
        size_t s_size = s.size();
        if ((pattern_size && !s_size) || (!pattern_size && s_size)) return false;
        // both pattern and s are empty or both pattern and s are not empty
        if (!pattern_size && !s_size) return true;
        // both pattern and s are not empty
        
        vector<string_view> s_words;
        size_t start_index = 0L;
        for (size_t i = 0L; i != s_size; ++i) {
            const auto ch = s[i];
            if (s[i] == ' ') {
                s_words.push_back(s.substr(start_index, i - start_index));
                start_index = i + 1L;
            }
        }

        if (start_index < s_size) {
            s_words.push_back(s.substr(start_index, s_size - start_index));
        }

        if (s_words.size() != pattern_size) return false;

        // Both s_words and pattern have the same size;

        unordered_map<char, string_view> map_p_to_s_word;
        unordered_map<string_view, char> map_s_word_to_p;

        for (size_t i = 0L; i != pattern_size; ++i) {
            const auto & s_word = s_words[i];
            const auto & pch = pattern[i];
            
            auto it = map_p_to_s_word.find(pch);
            if (it == map_p_to_s_word.end()) {
                auto it2 = map_s_word_to_p.find(s_word);
                if (it2 != map_s_word_to_p.end()) return false;
                map_s_word_to_p[s_word] = pch;
                map_p_to_s_word[pch] = s_word;
            }
            else if (it->second != s_word) return false;
        }
        return true;
    }
};
