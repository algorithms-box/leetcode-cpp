#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> num_map;
        for (std::size_t i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (num_map.count(complement)) {
                return {num_map[complement],
                        static_cast<int>(i)}; // 显式类型转换
            }
            num_map[nums[i]] = static_cast<int>(i); // 显式类型转换
        }
        return {};
    }
};

// 单元测试
void test() {
    Solution solution;
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    std::vector<int> result1 = solution.twoSum(nums1, target1);
    assert(result1.size() == 2 && result1[0] == 0 && result1[1] == 1);

    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    std::vector<int> result2 = solution.twoSum(nums2, target2);
    assert((result2.size() == 2 && ((result2[0] == 1 && result2[1] == 2) ||
                                    (result2[0] == 2 && result2[1] == 1))));

    std::cout << "All tests passed!" << std::endl;
}

// 性能测试
void performanceTest() {
    Solution solution;
    std::vector<int> nums(100000);
    int target = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        nums[i] = i;
        target += i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = solution.twoSum(nums, target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Performance test completed in " << elapsed.count() << " ms"
              << std::endl;
}

int main() {
    test();            // 运行单元测试
    performanceTest(); // 运行性能测试
    return 0;
}