// https://leetcode.com/problems/add-binary/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    constexpr static inline size_t min(size_t a, size_t b) {
        const bool test = (a <= b);
        return (test * (a)) + ((!test) * b);
    }

    constexpr static inline char to_char(char d) {
        return d + '0';
    }

public:
    static string addBinary(string_view a, string_view b) {
        if (a.empty()) return string{a};
        if (b.empty()) return string{b};

        const size_t asz = a.size();
        const size_t bsz = b.size();

        string result;
        result.reserve(a.size() + b.size());

        const size_t common_sz = min(asz, bsz);
        char carry  = 0;
        {
            auto ait = a.rbegin();
            auto bit = b.rbegin();
            while (ait != a.rend() && bit != b.rend()) {
                const char sum = (*ait -'0') + (*bit-'0') + carry;
                carry = sum>>1;
                result.push_back(to_char(sum & 1));
                ++ait;
                ++bit;
            }
        }
        

        if (common_sz < asz) {
            {
                auto ait = a.rbegin() + common_sz;
                while (ait != a.rend()) {
                    const char sum = (*ait -'0') + carry;
                    carry = sum>>1;
                    result.push_back(to_char(sum & 1));
                    ++ait;
                }
            }
        } else if (common_sz < bsz) {
            {
                auto bit = b.rbegin() + common_sz;
                while (bit != b.rend()) {
                    const char sum = (*bit -'0') + carry;
                    carry = sum>>1;
                    result.push_back(to_char(sum & 1));
                    ++bit;
                }
            }
        }

        if (carry) result.push_back(to_char(carry));

        std::reverse(result.begin(), result.end());
        return result;
    }
};
