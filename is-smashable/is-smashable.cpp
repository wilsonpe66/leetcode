/**
 * In this exercise, we're going to solve a problem on the whiteboard.
 * Please allow me to explain the problem, then there will be time to ask
 * questions to ensure that you understand the question.  Then there will
 * be a discussion of the programmatic interface to the solution,
 * followed by the implementation.  You can expect follow-on questions
 * after the implementation is complete.
 *
 * We're going to start by defining a trait or characteristic that a word
 * might have.  That characteristic is that the word not only appears in
 * the dictionary, but that there exists some letter than you can remove
 * to get a slightly shorter word.  The shorter word must also be in the
 * dictionary (can't be gibberish) and it must also satisfy the same
 * condition -- that it is possible to remove a letter from the shorter
 * word and again end up with a word found in the dictionary.  This
 * pattern continues until there are no more letters left.  You will be
 * creating software which will answer the question of whether or not a
 * given word satisfies this description.
 *
 * Example of a word that satisfies the definition:
 *
 *   PAINT
 *   PINT  // Removed the A
 *   PIN   // Removed the T
 *   IN    // Removed the P
 *   I     // Removed the N
 *
 * Example of a word that does not satisfy the definition:
 *
 *   SMALL
 *   MALL
 *   ALL
 *   AL  // Not in dictionary
 * has context menu
 *
 **/

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <vector>

namespace code {

using dictionay = std::unordered_set<std::string>;
using cache = std::unordered_map<std::string, bool>;

cache gcache;

constexpr inline size_t char_to_code_word_length(unsigned char fist_code_unit) {
    if (fist_code_unit <= 127) return 1L;
    if (fist_code_unit < 0xE0) return 2L;
    else if (fist_code_unit < 0xF0) return 3L;
    return 4L;
}

/**
 * @param dictionay is the dictionary that will be the source of true for words, where all are lowercase.
 * @param word is a utf8 encoded string that is trimed and lowercase.
*/
bool is_smashable(const dictionay & dict, const std::string & word) {
    auto it = gcache.find(word);
    if (it != gcache.end()) {
        std::cout<<"Using result from cache for '"<<word<<"': "<< it->second<<"\n";
        return it->second;
    }

    // Construct Cache entry
    bool is_found = false;
    if (dict.find(word) != dict.end()) {
        const size_t cw_len = char_to_code_word_length(word[0L]);
        const auto word_sw = word.size();
        if (cw_len == word_sw) {
            is_found = true;
        } else if (cw_len < word_sw) {
            for (size_t i = 0L; i < word_sw;) {
                const size_t code_word_size = char_to_code_word_length(word[i]);
                std::string new_word = word.substr(0L, i);

                i += code_word_size;
                if (i < word_sw) new_word += word.substr(i);
                if (is_smashable(dict, new_word)) {
                    is_found = true;
                    break;
                }
            }
        }
    }

    if (is_found) {
        std::cout<<"FOUND: '"<<word<<"'\n";
    }

    // Set the cache
    gcache[word] = is_found;

    return is_found;
}

/**
 * @param ch is an ascii char.
*/
constexpr inline bool is_white_space(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

/**
 * @param str is a utf8 encoded string.
*/
std::string to_trim_and_lower(std::string_view str) {
    if (str.empty()) return "";

    // L Trimming
    size_t l = 0L;
    while (l < str.size()) {
        const char ch = str[l];
        const size_t len  = char_to_code_word_length(ch);
        if (len > 1 || !is_white_space(ch)) break;
        l += len;
    }
    str = str.substr(l);

    // UTF8 R Trimming
    // because of utf8 encode strings we have to read from left to right only.
    size_t rtrail_sz = str.size();
    for (size_t r = 0L; r < str.size(); ) {
        const char ch = str[r];
        const size_t len  = char_to_code_word_length(ch);
        if (len == 1 && is_white_space(ch)) --rtrail_sz;
        else rtrail_sz = str.size();
        r += len;
    }
    std::string str2(str.substr(0, rtrail_sz));

    // Lowwer casing str2
    for (size_t i = 0L; i < str2.size(); ) {
        char &ch = str2[i];
        const size_t len  = char_to_code_word_length(ch);
        if (len == 1 && ch >= 'A' && ch <= 'Z') ch += ('a' - 'A');
        i += len;
    }
    return str2;
}

void print_dictionary(const dictionay & dict) {
    std::cout<<"DICTIONARY: {\n";
    for (const auto & word: dict) {
        std::cout << " - " << word<<"\n";
    }
    std::cout<<"}\n\n";
}

struct test_case {
    std::string description;
    std::string input_value;
    size_t expected_value;
};

} // namespace code



int main() {
    const code::dictionay dict = {
        "pin", "in", "i", "fin", "dog",

        // utf8 char words
        "😊😊😊", "😊",
        "£", "i£", "in£", "in£m",
        "€", "1€", "10€", "100€", "100€n", "100€nk", "10j0€nk",
        "😊€", "😊€€", "😊€£€", "😊€£€m", "😊€£€m😊",
    };
    code::print_dictionary(dict);

    const std::vector<code::test_case> words = {
        {"Emptry String Test", "", false},
        {"Only white space string", "      \n\t\r ", false},

        {"Ascii test the word I", "I", true},
        {"Ascii test the word i", "i", true},
        {"Ascii test the word i with padding", "  i      ", true},

        {"Ascii test the word  in.", "in", true},
        {"Ascii test the word iN", "iN", true},
        {"Ascii test the word In", "In", true},
        {"Ascii test the word In with padding", " In      ", true},

        {"Ascii test the word DOG", "DOG", false},
        {"Ascii test the word dOg", "dOg", false},
        {"Ascii test the word DOG with padding", " DOG      ", false},

        {"Ascii test the word pin", "pin", true},
        {"Ascii test the word PiN", "PiN", true},
        {"Ascii test the word PiN with padding", "  PiN      ", true},

        {"Ascii test the word FIN", "fin", true},
        {"Ascii test the word ATTTKE", "ATTTKE", false},
        {
            "Ascii test the long word PINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPIN",
            "PINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPIN",
            false
        },
        {
            "Ascii retest the same long word PINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPIN",
            "PINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPINPIN",
            false
        },

        {"Single Smily Face (4 Code word code uft8 char)", "😊", true},
        {"Double Smily Face", "😊😊", false},
        {"Tripple Smily Face", "😊😊😊", false},
        {"Single Smily Face with right padding", "😊     ", true},
        {"Single Smily Face with left padding", "    😊", true},
        {"Single Smily Face with padding on both sides", "  \t  😊\t \t         ", true},

        {"2 Code word code test", "£", true},
        {"Word with 2 Code word code uft8 char in it 1.", "in£", true},
        {"Word with 2 Code word code uft8 char in it 1.", "in£m", true},
        {"Word with 2 Code word code uft8 char in it 2.", "iN£m", true},
        {"Word with 2 Code word code uft8 char in it 3.", "iN£mk", false},
        {"Word with 2 Code word code uft8 char in it 4.", "    iN£nk   ", false},
        {"Word with 2 Code word code uft8 char in it 5.", "iN£n", false},

        {"3 Code word code test", "€", true},
        {"Word with 3 Code word code uft8 char in it 1.", "100€", true},
        {"Word with 3 Code word code uft8 char in it 2.", "100€n", true},
        {"Word with 3 Code word code uft8 char in it 3.", "100€nk", true},
        {"Word with 3 Code word code uft8 char in it 4.", "10j0€nk", true},

        {"Full mix test.", " \n    \t😊€£€m😊     ", true}

    };

    std::vector<code::test_case> failed_tests;
    for (const auto & [description, word, expected_valued]: words) {
        std::cout<<"====================================================\n"
                    <<"Test Description: " << description << "\n"
                    <<"\tChecking: '" << word << "'\n";

       const bool result = code::is_smashable(dict, code::to_trim_and_lower(word));
        const bool test_passed = (result == expected_valued);
        std::cout <<"Actual Result: '"<<word<<"' is " << (result ? "": "NOT ") << "smashable.\n"
                  <<"TEST: "<<(test_passed ? "PASSED": "FAILED") << "\n\n";

        if (!test_passed) {
            failed_tests.push_back({description, word, expected_valued});
        }
    }


    if (failed_tests.size()) {
        std::cout<<"FAILED TESTS:\n\n";
        for (const auto & [description, word, expected_valued]: failed_tests) {
            std::cout<<description<<":::_" << word << "_::::: " << expected_valued << "\n";
        }
    } else {
        std::cout<<"ALL TEST PASSED!!!!\n\n";
    }
    return 0;
}
