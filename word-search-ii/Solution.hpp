// https://leetcode.com/problems/word-search-ii/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
    class Trie {
        Trie * words[26] = {};
        bool is_word = false;
        char num_of_children = 0;

    public:

        void clear() {
            for (auto & child: words)
                if (child) {
                    delete child;
                    child = nullptr;
                }
            num_of_children = 0;
            is_word = false;
        }

        void print() const {
            if (num_of_children == 0) {
                cout<< this << "is a leaf root.\n";
                return;
            }

            cout<< this <<": ("<< int(num_of_children) << ") [\n";

            int leaf_cnt = 0;
            for (int i = 0; i < 26; ++i) {
                const Trie * child = words[i];
                if (child && child->num_of_children == 0) ++leaf_cnt;
            }

            if (leaf_cnt) {
                cout<<"\tLeaves: [";
                int cnt = 0;
                for (int i = 0; i < 26; ++i) {
                    const Trie * child = words[i];
                    if (child && child->num_of_children == 0) cout<<(cnt++ ? " ,": " ")<<char(i + 'a');
                }
                cout<< " ]\n";
            }

            if (leaf_cnt == num_of_children) return;

            cout<< "\tInternal Nodes: [\n";
            for (int i = 0; i < 26; ++i) {
                const Trie * child = words[i];
                if (child && child->num_of_children > 0) {    
                    cout << "\t\t" << char(i + 'a') << " -> " << child << "\n";
                }
            }
            cout<<"\t]\n]\n";
            
            for (auto child: words) {
                if (child && child->num_of_children > 0) {
                    cout<<"\n";
                    child->print();
                }
            }
        }

        string getCommonPrefix() const {
            if (!num_of_children) return "";

            string result;
            const Trie * cursor = this;
            while (cursor->num_of_children == 1) {
                const Trie * child;
                char found_char;
                for (int i = 0; i < 26; ++i) {
                    child = cursor->words[i];
                    found_char = i + 'a';
                    if (child) break;
                }
                result.push_back(found_char);
                cursor = child;
            }
            return result;
        }

        constexpr ~Trie() {
            for (auto child: words)
                if (child) delete child;
        }

        constexpr void insert(string_view word) {
            Trie * trie = this;
            for (const auto ch: word) {
                Trie * & child = trie->words[ch - 'a'];
                if (!child) {
                    child = new Trie();
                    ++trie->num_of_children;
                }
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

        constexpr void removeStartsWith(string_view prefix) {
            if (prefix.empty()) {
                for (Trie * & child: words) {
                    if(child) delete child;
                    child = nullptr;
                }
                num_of_children = 0;
            }

            Trie * trie = this;
            Trie * parent = trie;
            for (const auto ch: prefix) {
                parent = trie;
                trie = trie->words[ch - 'a'];
                if (!trie) return;
            }

            if (this != trie) {
               parent->words[*prefix.rbegin() - 'a'] = nullptr;
               --parent->num_of_children; 
               delete trie;
            }
        }
    };

    struct Point {
        short row;
        short col;

        constexpr inline Point left() const { return {row, short(col - 1)}; }
        constexpr inline Point right() const { return {row, short(col + 1)}; }
        constexpr inline Point up() const { return {short(row - 1), col}; }
        constexpr inline Point down() const { return {short(row + 1), col}; }

        void print() const {
            cout<<'('<<row<<", "<<col<<')';
        };
    };

    using InvertMap = unordered_map<char, unordered_map<short, unordered_set<short>>>;
    using VisitType = vector<bool>;

    static void print(const InvertMap & char_coords_mapping) {
        for (const auto & [ch, coor_map] : char_coords_mapping) {
            cout<< ch << ": [";
            for (const auto [row, cols]: coor_map) {
                for (const auto col: cols) {
                    Point{row, col}.print();
                }
            }
            cout<<" ]"<<endl;
        }
    }

    static inline bool is_valid_point(const InvertMap & char_coords_mapping, char ch, Point point,
                                        const size_t num_rows, const size_t num_cols) {
        const auto char_coords_mapping_it = char_coords_mapping.find(ch);
        if (char_coords_mapping_it == char_coords_mapping.end()) {
            return false;
        }
        
        const auto coords_mapping_it = char_coords_mapping_it->second.find(point.row);
        if (coords_mapping_it == char_coords_mapping_it->second.end()
            || !coords_mapping_it->second.contains(point.col)) {
            return false;
        }

        return true;
    }

    /**
        word is not empty
        start not end
     */
    static bool is_path(const InvertMap & char_coords_mapping, string_view word, Point start, VisitType visited,
                                const size_t num_rows, const size_t num_cols) {

        while (!word.empty()) {

            const size_t cell_key = 12 * start.row + start.col;
            if (start.row <0 || start.col < 0 || start.row >= num_rows || start.col >= num_cols
                || visited[cell_key]) return false;

            const char ch = word[0L];
            word = word.substr(1L);

            if (!is_valid_point(char_coords_mapping, ch, start, num_rows, num_cols)) return false;
            visited[cell_key] = true;
            
            if (word.empty()) return true;

            // word is not empty
            if (is_path(char_coords_mapping, word, start.left(), visited, num_rows, num_cols)) return true;
            if (is_path(char_coords_mapping, word, start.right(), visited, num_rows, num_cols)) return true;
            if (is_path(char_coords_mapping, word, start.up(), visited, num_rows, num_cols)) return true;

            start = start.down();
        }
        return false;
    }

    /**
        word.lenth is not empty
     */
    static inline bool is_path(const InvertMap & char_coords_mapping, string_view word, const size_t num_rows, const size_t num_cols) {
        const size_t wsz = word.size();
        if (wsz > num_rows * num_cols) return false;

        const auto coords_mapping_it = char_coords_mapping.find(word[0L]);
        if (coords_mapping_it == char_coords_mapping.end()) return false;
        
        for (const auto & [row, cols]: coords_mapping_it->second) {
            for (const auto col: cols) {
                if (wsz == 1L) return true;

                vector<bool> visited;
                visited.assign(144, false);
                if (is_path(char_coords_mapping, word, {row, col}, visited, num_rows, num_cols)) return true;
            }
        }
        return false;
    }

public:
    /**
        m == board.length
        n == board[i].length
        1 <= m, n <= 12
        board[i][j] is a lowercase English letter.
        1 <= words.length <= 3 * 104
        1 <= words[i].length <= 10
        words[i] consists of lowercase English letters.
        All the strings of words are unique.
    */
    static vector<string> findWords(const vector<vector<char>>& board, vector<string> words) {
        const size_t num_cols = board[0L].size();
        const size_t num_rows = board.size();

        InvertMap char_coords_mapping;
        for (size_t col = 0L; col != num_cols; ++col) {
            for (size_t row = 0L; row != num_rows; ++row) {
                const char ch = board[row][col];
                auto it = char_coords_mapping.find(ch);
                if (it == char_coords_mapping.end()) {
                    char_coords_mapping[ch][row].insert(col);
                } else {
                    it->second[row].insert(col);
                }
            }
        }

        auto is_all_char_in_work_on_board = [&char_coords_mapping](string_view word) {
            for (const char ch: word) {
                auto it = char_coords_mapping.find(ch);
                if (char_coords_mapping.find(ch) == char_coords_mapping.end()) return false;
            }
            return true;
        };

        Trie trie;
        for (const auto & word: words) {
            if (is_all_char_in_work_on_board(word)) trie.insert(word);
        }

        // If the longest common prefix is too long reverse the words and rebuild the trie.
        string largest_common_prefix = trie.getCommonPrefix();
        const bool use_reverse = largest_common_prefix.size() > 6L;
        if (use_reverse) {
            trie.clear();
            for (auto & word: words) {
                reverse(word.begin(), word.end());
                if (is_all_char_in_work_on_board(word)) trie.insert(word);
            }
        }

        // Prune out common prefixes that have not solution.
        largest_common_prefix = trie.getCommonPrefix();
        string_view largest_common_prefix_sv = largest_common_prefix;
        while (!largest_common_prefix_sv.empty() && !is_path(char_coords_mapping, largest_common_prefix_sv, num_rows, num_cols)) {
            trie.removeStartsWith(largest_common_prefix_sv);
            largest_common_prefix_sv = largest_common_prefix_sv.substr(0L, largest_common_prefix_sv.size() - 1L);
        }

        vector<string> results;
        results.reserve(words.size());
        for (auto & word: words) {
            if (!trie.startsWith(word)) continue;

            if (is_path(char_coords_mapping, word, num_rows, num_cols)) {
                if (use_reverse) reverse(word.begin(), word.end());

                results.push_back(word);
                continue;
            }

            // Prune out common prefixes that have not solution.
            string_view common_prefix_sv = word;
            while (!common_prefix_sv.empty() && !is_path(char_coords_mapping, common_prefix_sv, num_rows, num_cols)) {
                if (largest_common_prefix_sv.size() >= common_prefix_sv.size()) break;

                trie.removeStartsWith(common_prefix_sv);
                common_prefix_sv = common_prefix_sv.substr(0L, common_prefix_sv.size() - 1L);
            }
        }
        return results;
    }
};
