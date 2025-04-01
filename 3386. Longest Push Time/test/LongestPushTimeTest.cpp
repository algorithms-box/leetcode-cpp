#include <gtest/gtest.h>
#include "../src/LongestPushTime.cpp"

TEST(LongestPushTimeTest, Example1) {
    Solution solution;
    std::vector<int> releaseTimes = {9, 29, 49, 50};
    std::string keysPressed = "cbcd";
    EXPECT_EQ(solution.slowestKey(releaseTimes, keysPressed), 'c');
}

TEST(LongestPushTimeTest, Example2) {
    Solution solution;
    std::vector<int> releaseTimes = {12, 23, 36, 46, 62};
    std::string keysPressed = "spuda";
    EXPECT_EQ(solution.slowestKey(releaseTimes, keysPressed), 'a');
}