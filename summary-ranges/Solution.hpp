// https://leetcode.com/problems/summary-ranges/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    /**
    nums is sorted smallest to largest
    0 <= nums.length <= 20
    -231 <= nums[i] <= 231 - 1
    All the values of nums are unique.
    **/
    static vector<string> summaryRanges(const vector<int>& nums) {
        const char nums_sz = nums.size();
        if (!nums_sz) return {};

        // nums is not empty

        array<char, 20> start_indexes;
        start_indexes[0] = 0;
        char start_indexes_sz = 1;
        

        for (auto ch = 1; ch != nums_sz; ++ch) {
            if (nums[ch] != nums[ch - 1] + 1) start_indexes[start_indexes_sz++] = ch;
        }

        vector<string> results;
        results.reserve(start_indexes_sz);
        for (char ch = 0; ch != start_indexes_sz; ++ch) {
            char buff[50] = {};
            const auto start_index = start_indexes[ch];
            const auto next_ch = ch + 1;
            if (next_ch == start_indexes_sz) {
                if (start_indexes[start_indexes_sz - 1] + 1L == nums_sz) {
                    sprintf(buff, "%d", nums[start_index]);
                } else {
                    sprintf(buff, "%d->%d", nums[start_index], *nums.rbegin());
                }
                results.push_back(buff);
                continue;
            }
            
            const auto next_start_index = start_indexes[next_ch];
            if (start_index == next_start_index - 1) {
                sprintf(buff, "%d", nums[start_index]);
            }
            else sprintf(buff, "%d->%d", nums[start_index], nums[next_start_index - 1]);

            results.push_back(buff);
            
        }
        return results;
    }
};
