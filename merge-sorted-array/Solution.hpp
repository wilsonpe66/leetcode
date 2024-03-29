// https://leetcode.com/problems/merge-sorted-array/submissions/1217349752/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    static void merge(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
        const size_t nums2Sz = nums2.size();
        if (!nums2Sz) return;

        auto nums1It = nums1.rbegin() + nums2Sz;
        auto nums2It = nums2.rbegin();
        for (auto resultIt = nums1.rbegin(); resultIt != nums1.rend(); ++resultIt) {
            if (nums1It != nums1.rend()) {
                if (nums2It != nums2.rend()) {
                    if (*nums1It >= *nums2It) {
                        *resultIt = *nums1It;
                        ++nums1It;
                        continue;
                    }
                    
                    *resultIt = *nums2It;
                    ++nums2It;
                    continue;
                }

                *resultIt = *nums1It;
                ++nums1It;
                continue;
            }

            *resultIt = *nums2It;
            ++nums2It;
        }
    }
};
