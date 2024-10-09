#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int lengthOfLongestSubstring(const std::string &s) {
        std::unordered_set<char> char_set;
        int max_length = 0;
        std::size_t left = 0;

        for (std::size_t right = 0; right < s.length(); ++right) {
            while (char_set.count(s[right])) {
                char_set.erase(s[left]);
                ++left;
            }
            char_set.insert(s[right]);
            max_length =
                std::max(max_length, static_cast<int>(right - left + 1));
        }

        return max_length;
    }
};

void runUnitTests() {
    Solution sol;

    // Test case 1
    assert(sol.lengthOfLongestSubstring("abcabcbb") == 3);

    // Test case 2
    assert(sol.lengthOfLongestSubstring("bbbbb") == 1);

    // Test case 3
    assert(sol.lengthOfLongestSubstring("pwwkew") == 3);

    // Test case 4
    assert(sol.lengthOfLongestSubstring("") == 0);

    // Test case 5
    assert(sol.lengthOfLongestSubstring("dvdf") == 3);

    std::cout << "All unit tests passed!" << std::endl;
}

void runPerformanceTest() {
    Solution sol;
    const int NUM_TESTS = 1000;
    const int STRING_LENGTH = 10000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(
        97, 122); // ASCII values for lowercase letters

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_TESTS; ++i) {
        std::string test_string;
        test_string.reserve(STRING_LENGTH);
        for (int j = 0; j < STRING_LENGTH; ++j) {
            test_string += static_cast<char>(dis(gen));
        }
        sol.lengthOfLongestSubstring(test_string);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test: " << duration.count() / NUM_TESTS
              << "ms average over " << NUM_TESTS
              << " runs with strings of length " << STRING_LENGTH << "."
              << std::endl;
}

int main() {
    runUnitTests();
    runPerformanceTest();
    return 0;
}