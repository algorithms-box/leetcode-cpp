#include <gtest/gtest.h>
#include "../src/valid_parentheses.h"

TEST(ValidParenthesesTest, Example1) {
    Solution solution;
    EXPECT_TRUE(solution.isValid("()"));
}

TEST(ValidParenthesesTest, Example2) {
    Solution solution;
    EXPECT_TRUE(solution.isValid("()[]{}"));
}

TEST(ValidParenthesesTest, Example3) {
    Solution solution;
    EXPECT_FALSE(solution.isValid("(]"));
}

TEST(ValidParenthesesTest, Example4) {
    Solution solution;
    EXPECT_TRUE(solution.isValid("([])"));
}

TEST(ValidParenthesesTest, Example5) {
    Solution solution;
    EXPECT_FALSE(solution.isValid("([)]"));
}

TEST(ValidParenthesesTest, EmptyStackOnClose) {
    Solution solution;
    EXPECT_FALSE(solution.isValid(")"));
    EXPECT_FALSE(solution.isValid("}"));
    EXPECT_FALSE(solution.isValid("]"));
}

TEST(ValidParenthesesTest, UnclosedOpening) {
    Solution solution;
    EXPECT_FALSE(solution.isValid("("));
    EXPECT_FALSE(solution.isValid("({"));
    EXPECT_FALSE(solution.isValid("([]"));
}

TEST(ValidParenthesesTest, NestedValid) {
    Solution solution;
    EXPECT_TRUE(solution.isValid("((()))"));
    EXPECT_TRUE(solution.isValid("{[()]}"));
    EXPECT_TRUE(solution.isValid("{{[[(())]]}}"));
}

TEST(ValidParenthesesTest, MixedValid) {
    Solution solution;
    EXPECT_TRUE(solution.isValid("([]){}"));
    EXPECT_TRUE(solution.isValid("{[()[]]}"));
}
