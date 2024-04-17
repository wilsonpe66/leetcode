// https://leetcode.com/problems/trapping-rain-water/?envType=study-plan-v2&envId=top-interview-150

#include <span>

class Solution {
    static constexpr inline size_t max(size_t a, size_t b) {
        return (a > b) * (a-b) + b;
    }

public:
    /**
        n == height.length
        1 <= n <= 2 * 10^4
        0 <= height[i] <= 10^5
      */
    static constexpr size_t trap(const span<int>& height) {
        if (height.size() < 3L) return 0L;

        size_t left_max_height = height.front();
        size_t right_max_height = height.back(); 

        size_t cnt = 0L;

        size_t left_index = 1L;
        size_t right_index = height.size() - 2L;
        while (left_index <= right_index) {
            
            left_max_height = max(left_max_height, height[left_index]);
            right_max_height = max(right_max_height, height[right_index]);

            if (left_max_height < right_max_height) cnt += left_max_height - height[left_index++];
            else cnt += right_max_height - height[right_index--];
        } 
        return cnt;
    }
};
