// https://leetcode.com/problems/longest-common-prefix/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    /**
    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] consists of only lowercase English letters.
    **/
    static string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1L) return strs[0L];

        string prefix = strs[0L];
        for (const auto & str: strs) {
            const size_t psz = prefix.size();
            const size_t strsz = str.size();
            size_t min_sz = psz > strsz ? strsz : psz;
            size_t i = 0L;
            for (; i != min_sz && str[i] == prefix[i]; ++i);
            prefix = prefix.substr(0L, i);
            if (!psz) break;
        }
        return string(prefix);
    }
};
