#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    int lengthOfLastWord(std::string s) {
        int length = 0;
        int i = s.length() - 1;

        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        // Count the length of the last word
        while (i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }

        return length;
    }
};

// Unit tests
void runTests() {
    Solution sol;

    assert(sol.lengthOfLastWord("Hello World") == 5);
    assert(sol.lengthOfLastWord("   fly me   to   the moon  ") == 4);
    assert(sol.lengthOfLastWord("luffy is still joyboy") == 6);
    assert(sol.lengthOfLastWord("a") == 1);
    assert(sol.lengthOfLastWord(" ") == 0);
    assert(sol.lengthOfLastWord("") == 0);

    std::cout << "All tests passed!" << std::endl;
}

// Performance test
void performanceTest() {
    Solution sol;
    const int NUM_TESTS = 1000000;
    std::vector<std::string> testCases = {
        "Hello World", "   fly me   to   the moon  ", "luffy is still joyboy",
        std::string(1000, 'a') + " " + std::string(1000, 'b')};

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_TESTS; ++i) {
        for (const auto &testCase : testCases) {
            sol.lengthOfLastWord(testCase);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test completed in " << duration.count() << " ms"
              << std::endl;
}

int main() {
    runTests();
    performanceTest();
    return 0;
}
