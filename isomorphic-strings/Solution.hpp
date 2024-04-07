// https://leetcode.com/problems/isomorphic-strings/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    constexpr static inline short unassigned = 0XFF;
public:
    static constexpr bool isIsomorphic(string_view s, string_view t) {
        const size_t sz = s.size();
        if (sz != t.size()) return false;

        // s and t have the same size;
        unsigned short map_s_to_t[256];
        unsigned short map_t_to_s[256];
        for (int i = 0; i != 256; ++i) map_s_to_t[i] = map_t_to_s[i] = unassigned;

        for (size_t i = 0L; i != sz; ++i) {
            const auto & sch = s[i];
            const auto & tch = t[i];
            auto & s_mapped_to_t_char = map_s_to_t[sch];

            if (s_mapped_to_t_char == unassigned) {
                auto & t_mapped_to_s_char = map_t_to_s[tch];
                if (t_mapped_to_s_char != unassigned) return false;
                s_mapped_to_t_char = tch;
                t_mapped_to_s_char = sch;
            }
            else if (s_mapped_to_t_char != tch) return false;
        }
        return true;
    }
};
