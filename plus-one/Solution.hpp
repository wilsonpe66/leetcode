// https://leetcode.com/problems/plus-one/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    constexpr static vector<int> plusOne(const vector<int>& digits) {
        if (digits.empty()) return digits;
        vector<int> result = digits;

        auto it = result.rbegin();
        int sum = *it + 1;
        int carry = (sum > 9);
        *it = sum - 10 * carry;
        for (++it; it != result.rend(); ++it) {
            int sum = *it + carry;
            carry = (sum > 9);
            *it = sum - 10 * carry;
        }

        if (carry) result.insert(result.begin(), carry);
        return result;
    }
};
