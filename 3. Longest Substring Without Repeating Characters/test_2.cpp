/*turn off the assert*/
/* #define NDEBUG */
#include <iostream>
#include <string>
using std::string;
#include <cassert>
#include "longest_substring_without_repeating_characters_2.h"


int main() {
    Solution s;

    string str = "sdfasdfasdfasdfw";

    int result = s.lengthOfLongestSubstring(str);
    std::cout << std::to_string(result) << std::endl;
    assert( (result ==  5));


    return 0;
}
