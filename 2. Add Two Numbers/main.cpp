#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(0);
        ListNode *current = &dummy;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }

        return dummy.next;
    }
};

// Helper function to create a linked list from a vector
ListNode *createList(const std::vector<int> &nums) {
    ListNode dummy(0);
    ListNode *current = &dummy;
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    return dummy.next;
}

// Helper function to compare two linked lists
bool compareLists(ListNode *l1, ListNode *l2) {
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val != l2->val)
            return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == nullptr && l2 == nullptr;
}

// Helper function to delete a linked list
void deleteList(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

void runUnitTests() {
    Solution sol;

    // Test case 1
    ListNode *l1 = createList({2, 4, 3});
    ListNode *l2 = createList({5, 6, 4});
    ListNode *result = sol.addTwoNumbers(l1, l2);
    assert(compareLists(result, createList({7, 0, 8})));
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    // Test case 2
    l1 = createList({0});
    l2 = createList({0});
    result = sol.addTwoNumbers(l1, l2);
    assert(compareLists(result, createList({0})));
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    // Test case 3
    l1 = createList({9, 9, 9, 9, 9, 9, 9});
    l2 = createList({9, 9, 9, 9});
    result = sol.addTwoNumbers(l1, l2);
    assert(compareLists(result, createList({8, 9, 9, 9, 0, 0, 0, 1})));
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    std::cout << "All unit tests passed!" << std::endl;
}

void runPerformanceTest() {
    Solution sol;
    const int SIZE = 10000;
    const int NUM_TESTS = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_TESTS; ++i) {
        std::vector<int> nums1(SIZE), nums2(SIZE);
        for (int j = 0; j < SIZE; ++j) {
            nums1[j] = dis(gen);
            nums2[j] = dis(gen);
        }

        ListNode *l1 = createList(nums1);
        ListNode *l2 = createList(nums2);

        ListNode *result = sol.addTwoNumbers(l1, l2);

        deleteList(l1);
        deleteList(l2);
        deleteList(result);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test: " << duration.count() / NUM_TESTS
              << "ms average over " << NUM_TESTS << " runs with " << SIZE
              << " digits per number." << std::endl;
}

int main() {
    runUnitTests();
    runPerformanceTest();
    return 0;
}