// https://leetcode.com/problems/longest-consecutive-sequence/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    static constexpr inline size_t max(size_t a, size_t b) {
        return (a > b) * (a-b) + b;
    }

public:
    /*
    0 <= nums_in.length <= 105
    -109 <= nums_in[i] <= 109
     */
    static size_t longestConsecutive(const vector<int>& nums_in) {
        if (nums_in.empty()) return 0L;

        unordered_set<int> nums;
        for (const auto num: nums_in) nums.insert(num);
        if (nums.size() < 2L) return nums.size();

        size_t max_consec_seq_length = 1L;
       
        int current_min_value_in_sequence = *nums.begin();
        int current_max_value_in_sequence = current_min_value_in_sequence;

        while (!nums.empty()) {
            // // Find the start of the sequence
            // for (auto it = nums.find(current_min_value_in_sequence); 
            //         it != nums.end();
            //         it = nums.find(--current_min_value_in_sequence)
            // ) nums.erase(it);
            // ++current_min_value_in_sequence;

            // // Find the end of the sequence
            // ++current_max_value_in_sequence;
            // for (auto it = nums.find(current_max_value_in_sequence);
            //     it != nums.end();
            //     it = nums.find(++current_max_value_in_sequence)
            // ) nums.erase(it);
            // --current_max_value_in_sequence;

            // Find the start of the sequence
            for (auto it = nums.find(current_min_value_in_sequence);
                    it != nums.end();
                    it = nums.find(--current_min_value_in_sequence)
            ) continue;
            ++current_min_value_in_sequence;

            // Find the end of the sequence
            for (auto it = nums.find(++current_max_value_in_sequence);
                it != nums.end();
                it = nums.find(++current_max_value_in_sequence)
            ) continue;
            --current_max_value_in_sequence;

            // Remove sequence from nums
            for (int num = current_min_value_in_sequence;
                num <= current_max_value_in_sequence;
                ++num
            ) nums.erase(nums.find(num));

            // Recompute the max_consec_seq_length
            max_consec_seq_length = max(max_consec_seq_length, current_max_value_in_sequence - current_min_value_in_sequence + 1);

            // Resetting variables
            current_max_value_in_sequence = current_min_value_in_sequence = (!nums.empty()) * *nums.begin();
        }

        return max_consec_seq_length;
    }

    /*
    0 <= nums_in.length <= 105
    -109 <= nums_in[i] <= 109
     */
    static size_t longestConsecutiveUsingOrderSet(const vector<int>& nums_in) {
        if (nums_in.empty()) return 0L;

        set<int> nums;
        for (const auto num: nums_in) nums.insert(num);
        
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
};
