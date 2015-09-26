#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#include <string.h>

// Helpers

struct Matrix {
    int **arr;
    int M, N;

    Matrix(int m, int n) : M(m), N(n) {
        arr = new int*[m];
        for (int r = 0; r < m; ++r) {
            arr[r] = new int[n];
            for (int c = 0; c < n; ++c) {
                arr[r][c] = 1;
            }
        }
    }
};
void print_matrix(Matrix m) {
    for (int r = 0; r < m.M; ++r) {
        for (int c = 0; c < m.N; ++c) {
            printf("%d ", m.arr[r][c]);
        }
        printf("\n");
    }
}

// -------------------------------------------------------------

// 1.1 Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?
bool has_all_unique_chars(const std::string &str) {
    // O(n^2) without additional data structures
    int count;
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        count = 0;
        for (size_t j = 0; j < str.size(); ++j) {
            count += str[j] == c;
            if (count > 1) {
                return false;
            }
        }
    }
    return true;
}

// 1.2 Implement a function `void reverse(char *str)' in C or C++ which
// reverses a null terminated string.
void reverse(char *str) {
    if (!str) return;
    size_t len = strlen(str);
    if (!len) return;
    char *end = len + str-1;
    if (end <= str) return;
    char tmp;
    for (size_t i = 0; i < len / 2; ++i) {
        tmp = *(end-i);
        *(end-i) = str[i];
        str[i] = tmp;
    }
}

// 1.3 Given two strings, write a method to decide if one is a permutation
// of the other. 
bool is_permutation(const std::string &s1, const std::string &s2) {
    if (s1.size() != s2.size())
        return false;

    std::map<char, int> s1_chars, s2_chars;
    for (auto itr = s1.begin(); itr != s1.end(); ++itr) {
        s1_chars[*itr]++;
    }
    for (auto itr = s2.begin(); itr != s2.end(); ++itr) {
        s2_chars[*itr]++;
    }
    
    for (auto itr = s1_chars.begin(); itr != s1_chars.end(); ++itr) {
        if (s2_chars[itr->first] != itr->second)
            return false;
    }
    return true;
}

// 1.4 Write a method to replace all spaces with `%20'. You may assume that
// the string has sufficient space at the end of the string to hold the
// additional characters, and that you are given the "true" length of the
// string.
// Example:
// Input:  "Mr John Smith    "
// Output: "Mr%20John%20Smith"
void replace_space_with_perc_20(char *str) {
    if (!str)
        return;
    int len = strlen(str);
    if (len < 3)
        return;
    char *end = str + len - 1;
    char *tmp = end;
    while (*tmp == ' ')
        --tmp;
    while (tmp >= str) {
        if (*tmp == ' ') {
            *end-- = '0';
            *end-- = '2';
            *end-- = '%';
            --tmp;
            continue;
        }
        *end-- = *tmp--;
    }
}

// 1.5 Implement a method to perform basic string compression using the
// counts of repeated characters. For example, the string 'aabcccccaaa'
// would become a2b1c5a3. If the "compressed" string would not become
// smaller than the original string, your method should return the
// original.
int count_repeats(const std::string &s, int start) {
    int count = 1;
    auto c = s[start++];
    while (s[start++] == c) {
        ++count;
    }
    return count;
}
std::string compress_string(const std::string &s) {
    if (s.size() == 0)
        return s;
    std::stringstream ss;
    size_t i = 0;
    while (i < s.size()) {
        int count = count_repeats(s, i);
        ss << s[i];
        ss << count;
        if (ss.str().size() > s.size())
            return s;
        i += count;
    }
    return ss.str();
}

// 1.6 Given an image represented by an NxN matrix, where each pixel in the
// image is 4 bytes, write a method to rotate the image by 90 degrees. Can
// you do this in place?
void rotate_90_in_place(Matrix &m) {
    if (m.N != m.M)
        return;
    /* TODO: Implement 1.6 */
}

// 1.7 Write an algorithm such that if an element in an MxN matrix is 0, its
// entire row and column are set to 0.
void zero_row_column(Matrix &m, int r, int c) {
    for (int i = 0; i < m.N; ++i) {
        m.arr[r][i] = 0;
    }
    for (int i = 0; i < m.M; ++i) {
        m.arr[i][c] = 0;
    }
}
void zero_row_column_if_zero(Matrix &m) {
    if (!m.arr) return;
    struct Vec2 {
        int r, c;
    };
    std::vector<Vec2> to_zero;
    for (int r = 0; r < m.M; ++r) {
        for (int c = 0; c < m.N; ++c) {
            if (m.arr[r][c] == 0) {
                to_zero.push_back({r, c});
            }
        }
    }
    for (auto itr = to_zero.begin(); itr != to_zero.end(); ++itr) {
        zero_row_column(m, (*itr).r, (*itr).c);
    }
}

// 1.8 Assume you have a method isSubstring which checks if one word is a
// substring of another. Given two strings, s1 and s2, write code to check
// if s2 is a rotation of s1 using only one call to isSubstring
// Example: "waterbottle" is a rotation of "erbottlewat"
bool is_rotation_of(const std::string &s1, const std::string &s2) {
    if (s1.size() != s2.size())
        return false;
    if (s1 == s2)
        return true;
    // the logic behind this is:
    // "erbottlewat" + "erbottlewat" = "erbottlewaterbottle"
    // which contains "waterbottle"
    auto s1s1 = s1 + s1;
    return s1s1.find(s2) != std::string::npos;
}

int main() {
    char *s = strdup("ab");
    printf("pre-reverse: %s\n", s);
    reverse(s);
    printf("post-reverse: %s\n", s);

    printf("true permutation: %d\n", is_permutation("hello", "ohlel"));
    printf("empty permutation: %d\n", is_permutation("", ""));
    printf("false permutation: %d\n", is_permutation("hello", "dohlel"));

    int m = 10, n = 15;
    Matrix matrix(m, n);
    matrix.arr[3][2] = 0;
    matrix.arr[6][12] = 0;
    matrix.arr[9][14] = 0;
    print_matrix(matrix);
    zero_row_column_if_zero(matrix);
    puts("===");
    print_matrix(matrix);

    printf("true unique: %d\n", has_all_unique_chars("abc"));
    printf("empty unique: %d\n", has_all_unique_chars(""));
    printf("false unique: %d\n", has_all_unique_chars("abbc"));

    printf("compressed: %s\n", compress_string("aabcccccaaa").c_str());
    printf("empty: %s\n", compress_string("").c_str());
    printf("original: %s\n", compress_string("abcdefg").c_str());

    printf("true rotation of: %d\n", is_rotation_of("erbottlewat", "waterbottle"));
    printf("empty rotation of: %d\n", is_rotation_of("", ""));
    printf("false rotation of: %d\n", is_rotation_of("erbewat", "waterbottle"));

    s = strdup("Mr John Smith    ");
    printf("pre-replace: %s\n", s);
    replace_space_with_perc_20(s);
    printf("post-replace: %s\n", s);
    
    return 0;
}
