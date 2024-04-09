// https://leetcode.com/problems/longest-consecutive-sequence/?envType=study-plan-v2&envId=top-interview-150
class Solution {
    static constexpr inline size_t max(size_t a, size_t b) {
        return (a > b) * (a-b) + b;
    }

    static inline size_t longestConsecutive(const set<int>& nums) {
        if (nums.size() < 2L) return nums.size();

        size_t max_consec_seq_length = 1L;
        const auto end_it = nums.end();
        for (auto it = nums.begin(); it != end_it; ++it) {
            size_t local_max_length_seq = 1L;
            auto next = it;
            for (++next; next != end_it && *it + 1L == *next; it = next++) {
                ++local_max_length_seq;
            }
            max_consec_seq_length = max(max_consec_seq_length, local_max_length_seq);
        }

        return max_consec_seq_length;
    }
public:
    /*
    0 <= nums.length <= 105
    -109 <= nums[i] <= 109
     */
    static size_t longestConsecutive(const vector<int>& nums) {
        if (nums.empty()) return 0L;

        set<int> m;
        for (const auto num: nums) m.insert(num);
        return longestConsecutive(m);
    }
};

