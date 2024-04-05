// https://leetcode.com/problems/single-number-ii/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    // nums is not empty
    static int singleNumber(const vector<int>& nums) {
        unordered_map<int, char> cnts;
        for (const int num: nums) {
            auto it = cnts.find(num);
            if (it == cnts.end()) cnts.insert({num, 1});
            else if (it->second == 2) cnts.erase(it);
            else ++(it->second);
        }
        
        return cnts.begin()->first;
    }
};

