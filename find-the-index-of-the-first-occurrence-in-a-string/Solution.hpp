// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static constexpr int strStr(string_view haystack, string_view needle) {
        if (needle.empty()) return -(!haystack.empty());

        const size_t needle_sz = needle.size();
        const size_t haystack_sz = haystack.size();
        for (size_t i = 0L; i != haystack_sz; ++i) {
            if (haystack[i] != needle[0L] || i + needle_sz > haystack_sz) continue;
            
            // needle is not empty
            // haystack[i] == needle[0L] and i + needle_sz <= haystack_sz
            size_t j = 1L;
            size_t i2 = i + 1L;
            while (j != needle_sz && haystack[i2] == needle[j]) {
                ++i2;
                ++j;
            }

            if (j == needle_sz) return i;
        }
        return -1;
    }
};
