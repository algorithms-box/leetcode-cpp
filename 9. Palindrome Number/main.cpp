#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Solution {
  public:
    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            return false;
        }

        int reversed = 0;
        while (x > reversed) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        return (x == reversed || x == reversed / 10);
    }
};

void runUnitTest() {
    Solution s;
    assert(s.isPalindrome(121) == true);
    assert(s.isPalindrome(-121) == false);
    assert(s.isPalindrome(10) == false);
    assert(s.isPalindrome(153423651) == true);
    assert(s.isPalindrome(123321) == true);
    assert(s.isPalindrome(123) == false);
    assert(s.isPalindrome(1000000001) == false);
    std::cout << "All tests passed." << std::endl;
}

void runPerformanceTest() {
    Solution sol;
    const int NUM_TESTS = 1000000;
    std::vector<int> testNumbers(NUM_TESTS);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000000000, 1000000000);

    for (int i = 0; i < NUM_TESTS; ++i) {
        testNumbers[i] = dis(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int num : testNumbers) {
        sol.isPalindrome(num);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Performance test: " << diff.count() << " seconds for "
              << NUM_TESTS << " tests" << std::endl;
}

int main() {
    runUnitTest();
    runPerformanceTest();
    return 0;
}