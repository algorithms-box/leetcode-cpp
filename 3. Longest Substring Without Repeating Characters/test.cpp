/*turn off the assert*/
/* #define NDEBUG */
#include <iostream>
#include <string>
#include <cassert>
#include "longest_substring_without_repeating_characters.h"

int main()
{
    Solution s;
    int result = s.lengthOfLongestSubstring("au");

    /* assert( (&ret ==  &l3)); */
    std::cout << result << std::endl;

    return 0;
}
