// https://leetcode.com/problems/trapping-rain-water/?envType=study-plan-v2&envId=top-interview-150

#include <span>

class Solution {
    static constexpr inline size_t min(size_t a, size_t b) {
        return (a < b) * (a-b) + b;
    }

    static constexpr inline size_t max(size_t a, size_t b) {
        return (a > b) * (a-b) + b;
    }

    static constexpr size_t conditional_gt_diff(size_t a, size_t b) {
        return (a > b) * (a - b);
    }

    static constexpr size_t sum(const span<int> hight_view, const size_t min_max_outer_height) {
        size_t cnt = 0L;
        for (const int current_height: hight_view) {
            cnt += conditional_gt_diff(min_max_outer_height,current_height);
        }
        return cnt;
    };

    static void print(span<int> height) {
        cout<<"("<<height.size()<<")[";for(const auto h: height) cout<<" "<<h;cout<<" ]"<<endl;
    }
   
public:
    /**
        n == height.length
        1 <= n <= 2 * 10^4
        0 <= height[i] <= 10^5
      */
    static constexpr inline size_t trapP(span<int> height) {
        size_t sz = height.size();
        if (sz < 3L) return 0;
        
        const size_t left_height = *height.begin();
        const size_t right_height = *height.rbegin();
        if (sz == 3L) {
            return conditional_gt_diff(min(left_height, right_height), height[1L]);
        }

        // sz > 3

        size_t cnt = 0L;

        size_t left_sz = 0L;
        size_t left_end_max_height = left_height;
        size_t max_sz = 0L;
        size_t max_value = 0L;
        for (auto it = height.begin(); it != height.end(); ++it) {
            ++left_sz;
            if (max_value > *it) continue;

            max_value = *it;
            max_sz = left_sz;

            if (left_height < *it) {
                left_end_max_height = *it;
                break;
            }
        }

        left_sz = left_sz == sz ? max_sz: left_sz;

        cnt += sum(height.subspan(0L, left_sz), min(left_height, left_end_max_height));
        
        height = height.subspan(left_sz - 1L);
        sz = height.size();
        
        size_t right_sz = sz;
        size_t right_start_max_height = *height.rbegin();
        max_sz = right_sz;
        max_value = 0L;
        for (auto it = height.rbegin(); it != height.rend(); ++it) {
            --right_sz;
            if (max_value > *it) continue;
            
            max_value = *it;
            max_sz = right_sz;
            if (right_height < *it) {
                right_start_max_height = *it;
                break;
            }
        }

        right_sz = right_sz ? right_sz: max_sz;

        cnt += sum(height.subspan(right_sz), min(right_height, right_start_max_height));
        height = height.subspan(0L, min(right_sz + 1L, height.size()));
        return cnt + trap(height);
    }

    static constexpr size_t trap(span<int> height) {
        const size_t sz = height.size();
        if (sz < 3) return 0;

        // left trim the span;
        size_t left_index = 0L;
        size_t left_max_height = *height.begin();
        
        for (size_t i = 1L; i != sz && left_max_height <= height[i]; ++i) {
            left_max_height = height[i];
            left_index = i;
        }

        if (left_index + 1L == sz) return 0L;

        // Left trim height
        height = height.subspan(left_index);

        // right trim the span;
        size_t right_sz = height.size();
        auto it = height.rbegin();
        auto next_it = it + 1L;
        for (; next_it != height.rend() && *next_it >= *it; ++next_it) {
            --right_sz;
            it = next_it;
        }
        
        if (right_sz < 3) return 0L;
        return trapP(height.subspan(0L, right_sz));
    }
};

