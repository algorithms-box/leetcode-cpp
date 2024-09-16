#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
  public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_map<char, int> charIndexMap;
        int maxLength = 0;
        int start = 0;
        for (int end = 0; end < s.length(); ++end) {
            char currentChar = s[end];
            if (charIndexMap.find(currentChar) != charIndexMap.end()) {
                // 更新开始位置，使得子串不包含重复字符
                start = std::max(start, charIndexMap[currentChar] + 1);
            }
            // 更新当前字符的索引
            charIndexMap[currentChar] = end;
            // 更新最长不重复子串的长度
            maxLength = std::max(maxLength, end - start + 1);
        }
        return maxLength;
    }
};

// 单元测试
void runTests() {
    Solution solution;

    // Test 1
    std::string s1 = "abcabcbb";
    assert(solution.lengthOfLongestSubstring(s1) == 3);
    std::cout << "Test 1 passed." << std::endl;

    // Test 2
    std::string s2 = "bbbbb";
    assert(solution.lengthOfLongestSubstring(s2) == 1);
    std::cout << "Test 2 passed." << std::endl;

    // Test 3
    std::string s3 = "pwwkew";
    assert(solution.lengthOfLongestSubstring(s3) == 3);
    std::cout << "Test 3 passed." << std::endl;

    // Test 4
    std::string s4 = "dvdf";
    assert(solution.lengthOfLongestSubstring(s4) == 3);
    std::cout << "Test 4 passed." << std::endl;

    // Test 5
    std::string s5 = " ";
    assert(solution.lengthOfLongestSubstring(s5) == 1);
    std::cout << "Test 5 passed." << std::endl;

    std::cout << "All tests passed." << std::endl;
}

int main() {
    runTests();
    return 0;
}