#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    std::unordered_map<int, int> num_map;
    for (int i = 0; i < numsSize; ++i) {
        int complement = target - nums[i];
        if (num_map.find(complement) != num_map.end()) {
            int *result = new int[2];
            result[0] = num_map[complement];
            result[1] = i;
            *returnSize = 2;
            return result;
        }
        num_map[nums[i]] = i;
    }
    return nullptr; // 不应该发生，因为题目保证有解
}

// 单元测试
void runTests() {
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1 = 0;
    int *result1 = twoSum(nums1, 4, target1, &returnSize1);
    assert(result1 != nullptr && result1[0] == 0 && result1[1] == 1);
    delete[] result1;

    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2 = 0;
    int *result2 = twoSum(nums2, 3, target2, &returnSize2);
    assert(result2 != nullptr && ((result2[0] == 1 && result2[1] == 2) ||
                                  (result2[0] == 2 && result2[1] == 1)));
    delete[] result2;

    int nums3[] = {3, 3};
    int target3 = 6;
    int returnSize3 = 0;
    int *result3 = twoSum(nums3, 2, target3, &returnSize3);
    assert(result3 != nullptr && result3[0] == 0 && result3[1] == 1);
    delete[] result3;

    std::cout << "All tests passed." << std::endl;
}

int main() {
    runTests();
    return 0;
}