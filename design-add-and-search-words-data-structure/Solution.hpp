// https://leetcode.com/problems/design-add-and-search-words-data-structure/description/?envType=study-plan-v2&envId=top-interview-150

/**
    1 <= word.length <= 25
    word in addWord consists of lowercase English letters.
    word in search consist of '.' or lowercase English letters.
    There will be at most 2 dots in word for search queries.
    At most 104 calls will be made to addWord and search.
 **/

class WordDictionary {
    WordDictionary * words[26] = {};
    bool is_word = false;
    char sz = 0;

    constexpr static inline unsigned char hash(char ch) {
        return ch - 'a';
    }
public:
    constexpr ~WordDictionary() {
        for (auto child: words)
            if (child) delete child;
    }
    
    constexpr void addWord(string_view word) {
        WordDictionary * trie = this;
        for (const auto ch: word) {
            WordDictionary * & child = trie->words[hash(ch)];
            if (!child) {
                child = new WordDictionary();
                ++trie->sz;
            }
            trie = child;
        }

        trie->is_word = true;
    }
    
    constexpr bool search(string_view word) const {
        auto trie = this;
        while (trie && trie->sz && !word.empty()) {
            const char ch = word[0L];

            if (ch != '.') {
                trie = trie->words[hash(ch)];
                if (!trie) return false;
                word = word.substr(1L);
                continue;
            }

            word = word.substr(1L);
            
            for (size_t i = 0; i != 25; ++i) {
                const auto child_trie = trie->words[i];
                if (child_trie && child_trie->search(word)) return true;
            }
            trie = trie->words[25];
        }

        // either child_trie is nullptr or word is empty but not both.
        return (trie && trie->is_word) && word.empty();
    }
};

