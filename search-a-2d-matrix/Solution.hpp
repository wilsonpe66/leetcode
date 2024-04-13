// https://leetcode.com/problems/search-a-2d-matrix/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    constexpr static inline bool searchMatrix(const vector<int>& nums, const int target) {
        size_t start = 0L;
        size_t end = nums.size();
        while (start < end) {
            const size_t mid = ((end - start)>>1) + start;
            const auto & val = nums[mid];
            
            if (target < val) end = mid;
            else if (target > val) start = mid + 1L;
            else return true;
        }
        return false;
    }

public:
    /**
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4
      */
    constexpr static bool searchMatrix(const vector<vector<int>>& matrix, const int target) {
        size_t start = 0L;
        size_t end = matrix.size();
        while (start < end) {
            const size_t mid = ((end - start)>>1) + start;
            const auto & row = matrix[mid];

            if (target < *row.begin()) end = mid;
            else if (target > *row.rbegin()) start = mid + 1L;
            else return searchMatrix(row, target);
        }
        return false;
    }
};
