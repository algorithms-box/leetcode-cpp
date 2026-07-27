/*
 * Algorithm: Valid Parentheses
 *
 * Approach: Use a stack-based approach to validate parentheses.
 * Push opening brackets onto the stack. When encountering a closing bracket,
 * check if it matches the most recent opening bracket (stack top). If not,
 * the string is invalid. If the stack is empty when a closing bracket appears,
 * it's also invalid. Finally, the stack must be empty for valid parentheses.
 *
 * Time Complexity: O(n) - Each character is processed exactly once
 * Space Complexity: O(n) - In the worst case, all characters are opening brackets
 *
 * Compilation (C++20): g++ -std=c++20 -o valid_parentheses valid_parentheses.cpp
 * Execution: ./valid_parentheses
 *
 * This is a standalone version that can be compiled directly with g++.
 * For CMake project version with vcpkg, see the project folder.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    bool isValid(std::string s) {
        std::vector<char> stack;
        stack.reserve(s.size());

        for (char c : s) {
            switch (c) {
                case '(':
                case '{':
                case '[':
                    stack.push_back(c);
                    break;
                case ')':
                    if (stack.empty() || stack.back() != '(')
                        return false;
                    stack.pop_back();
                    break;
                case '}':
                    if (stack.empty() || stack.back() != '{')
                        return false;
                    stack.pop_back();
                    break;
                case ']':
                    if (stack.empty() || stack.back() != '[')
                        return false;
                    stack.pop_back();
                    break;
                default:
                    return false;
            }
        }

        return stack.empty();
    }
};

void runTests() {
    Solution solution;

    assert(solution.isValid("()") == true);
    assert(solution.isValid("()[]{}") == true);
    assert(solution.isValid("(]") == false);
    assert(solution.isValid("([])") == true);
    assert(solution.isValid("([)]") == false);

    assert(solution.isValid(")") == false);
    assert(solution.isValid("}") == false);
    assert(solution.isValid("]") == false);

    assert(solution.isValid("(") == false);
    assert(solution.isValid("({") == false);
    assert(solution.isValid("([]") == false);

    assert(solution.isValid("((()))") == true);
    assert(solution.isValid("{[()]}") == true);
    assert(solution.isValid("{{[[(())]]}}") == true);

    assert(solution.isValid("([]){}") == true);
    assert(solution.isValid("{[()[]]}") == true);

    std::cout << "All tests passed!" << std::endl;
}

void runExamples() {
    Solution solution;
    std::cout << "Example 1: " << solution.isValid("()") << std::endl;
    std::cout << "Example 2: " << solution.isValid("()[]{}") << std::endl;
    std::cout << "Example 3: " << solution.isValid("(]") << std::endl;
    std::cout << "Example 4: " << solution.isValid("([])") << std::endl;
    std::cout << "Example 5: " << solution.isValid("([)]") << std::endl;
}

int main() {
    runTests();
    runExamples();
    return 0;
}
