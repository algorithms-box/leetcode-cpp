#include <cassert>
#include <iostream>
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
            int x = l1 != nullptr ? l1->val : 0;
            int y = l2 != nullptr ? l2->val : 0;
            int sum = x + y + carry;
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
            if (l1 != nullptr)
                l1 = l1->next;
            if (l2 != nullptr)
                l2 = l2->next;
        }
        return dummy.next;
    }
};

// Helper function to create a linked list from an array
ListNode *createList(const std::vector<int> &values) {
    ListNode dummy(0);
    ListNode *current = &dummy;
    for (int val : values) {
        current->next = new ListNode(val);
        current = current->next;
    }
    return dummy.next;
}

// Helper function to print a linked list
void printList(ListNode *head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr)
            std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Helper function to delete a linked list and prevent memory leaks
void deleteList(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Unit tests with assertions
void runTests() {
    Solution solution;

    // Test 1: Add two numbers (2 -> 4 -> 3) and (5 -> 6 -> 4)
    ListNode *l1 = createList({2, 4, 3});
    ListNode *l2 = createList({5, 6, 4});
    ListNode *result = solution.addTwoNumbers(l1, l2);
    assert(result->val == 7 && result->next->val == 0 &&
           result->next->next->val == 8);
    deleteList(result);
    deleteList(l1);
    deleteList(l2);

    // Test 2: Edge cases
    // ...
    // Add more tests as needed

    std::cout << "All tests passed." << std::endl;
}

int main() {
    runTests();
    return 0;
}