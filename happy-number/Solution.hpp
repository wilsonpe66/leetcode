// https://leetcode.com/problems/happy-number/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    // 1 <= n <= 231 - 1
    static bool isHappy(int n) {
        unordered_set<int> s;
        while (n != 1 && !s.contains(n)) {
            s.insert(n);
            int tmp = 0L;
            for (int next_n = n; n; n = next_n) {
                next_n /= 10;
                const int rem = 10 * next_n - n;
                tmp += rem * rem;
            }
            n = tmp;
        }
        return n == 1;
    }
};

