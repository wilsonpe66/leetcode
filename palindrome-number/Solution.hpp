class Solution {
public:
    static constexpr bool isPalindrome(long in_x) {
        if ( in_x < 0 ) return false;
        long result = 0L;
        long new_x = 0L;
        for (auto x = in_x; x; x = new_x) {
            new_x = x / 10L;
            result = 10L * (result - new_x) + x; 
        }

        return result ==  in_x;
    }
};

