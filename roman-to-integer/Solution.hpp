// https://leetcode.com/problems/roman-to-integer/

class Solution {
    static constexpr inline int map_value(char ch) {
        switch(ch) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return 0;
    }

    static constexpr inline int getResult(int result, int mapped_value, int next_mapped_value) {
        return  (mapped_value < next_mapped_value) ? 
            result - mapped_value :
            result + mapped_value;
    }
public:
    constexpr inline int romanToInt(string_view s) {
        if (s.empty()) return 0;
        if (s.size() == 1L) return map_value(s[0]);

        // s.size() >= 2
        
        int mapped_value = map_value(s[0]);
        int next_mapped_value = map_value(s[1]);
        int result = getResult(0, mapped_value, next_mapped_value);
        for (size_t i = 2L; i < s.size(); ++i) {
            mapped_value = next_mapped_value;
            next_mapped_value = map_value(s[i]);
            result = getResult(result, mapped_value, next_mapped_value);
        }
        
        return result + next_mapped_value;
    }
};
