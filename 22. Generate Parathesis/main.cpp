#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        generateParenthesisRecursive(n, n, "", result);
        return result;
    }

  private:
    void generateParenthesisRecursive(int open, int close, std::string current,
                                      std::vector<std::string> &result) {
        if (open == 0 && close == 0) {
            result.push_back(current);
            return;
        }

        if (open > 0) {
            generateParenthesisRecursive(open - 1, close, current + "(",
                                         result);
        }

        if (close > open) {
            generateParenthesisRecursive(open, close - 1, current + ")",
                                         result);
        }
    }
};

void runUnitTests() {
    Solution sol;

    // Test case 1
    std::vector<std::string> result1 = sol.generateParenthesis(3);
    std::vector<std::string> expected1 = {"((()))", "(()())", "(())()",
                                          "()(())", "()()()"};
    assert(result1 == expected1);

    // Test case 2
    std::vector<std::string> result2 = sol.generateParenthesis(1);
    std::vector<std::string> expected2 = {"()"};
    assert(result2 == expected2);

    // Test case 3
    std::vector<std::string> result3 = sol.generateParenthesis(2);
    std::vector<std::string> expected3 = {"(())", "()()"};
    assert(result3 == expected3);

    std::cout << "All unit tests passed!" << std::endl;
}

void runPerformanceTest() {
    Solution sol;
    const int MAX_N = 14; // Adjust based on your system's capabilities
    const int NUM_RUNS = 5;

    for (int n = 1; n <= MAX_N; ++n) {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_RUNS; ++i) {
            sol.generateParenthesis(n);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "n = " << n << ": " << duration.count() / NUM_RUNS
                  << "ms average over " << NUM_RUNS << " runs" << std::endl;
    }
}

int main() {
    runUnitTests();
    runPerformanceTest();
    return 0;
}