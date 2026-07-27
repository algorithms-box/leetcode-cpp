#include "valid_parentheses.h"

bool Solution::isValid(std::string s) {
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
