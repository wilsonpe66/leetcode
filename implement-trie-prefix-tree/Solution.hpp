// https://leetcode.com/problems/implement-trie-prefix-tree/?envType=study-plan-v2&envId=top-interview-150

/**
    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3 * 104 calls in total will be made to insert, search, and startsWith.
*/
class Trie {
    Trie * words[27] = {};
    bool is_word = false;

public:
    constexpr ~Trie() {
        for (auto child: words)
            if (child) delete child;
    }

    constexpr void insert(string_view word) {
        Trie * trie = this;
        for (const auto ch: word) {
            Trie * & child = trie->words[ch - 'a'];
            if (!child) child = new Trie();
            trie = child;
        }

        trie->is_word = true;
    }
    
    constexpr bool search(string_view word) const {
        const Trie * trie = this;
        for (const auto ch: word) {
            trie = trie->words[ch - 'a'];
            if (!trie) return false;
        }
        return trie->is_word;
    }
    
    constexpr bool startsWith(string_view prefix) const {
        const Trie * trie = this;
        for (const auto ch: prefix) {
            trie = trie->words[ch - 'a'];
            if (!trie) return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
