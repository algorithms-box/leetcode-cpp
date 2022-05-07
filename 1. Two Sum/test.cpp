/*turn off the assert*/
/* #define NDEBUG */
#include <cassert>
#include "two_sum.h"

int main() {
    Solution s;

    std::vector<int> v1{2, 7, 11, 15};
    assert( (s.twoSum(v1, 9) == std::vector<int> {0, 1}) );

    std::vector<int> v2{0, 4, 3, 0};
    assert( (s.twoSum(v2, 0) == std::vector<int> {0, 3}) );

    std::vector<int> v3{-3, 4, 3, 90};
    assert( (s.twoSum(v3, 0) == std::vector<int> {0, 2}) );

    return 0;
}
