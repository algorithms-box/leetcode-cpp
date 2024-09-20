#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    void generateParenthesisUtil(std::string &current, int open, int close,
                                 int n, std::vector<std::string> &result) {
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        if (open < n) {
            current.push_back('(');
            generateParenthesisUtil(current, open + 1, close, n, result);
            current.pop_back();
        }

        if (close < open) {
            current.push_back(')');
            generateParenthesisUtil(current, open, close + 1, n, result);
            current.pop_back();
        }
    }

    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        std::string current;
        generateParenthesisUtil(current, 0, 0, n, result);
        return result;
    }
};

// 单元测试
void test() {
    Solution solution;
    std::vector<std::string> result = solution.generateParenthesis(3);
    assert(result.size() == 5);
    assert(result[0] == "((()))");
    assert(result[1] == "(()())");
    assert(result[2] == "(())()");
    assert(result[3] == "()(())");
    assert(result[4] == "()()()");
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    Solution solution;
    std::vector<std::string> result = solution.generateParenthesis(3);
    for (const std::string &s : result) {
        std::cout << s << std::endl;
    }
    test();
    return 0;
}