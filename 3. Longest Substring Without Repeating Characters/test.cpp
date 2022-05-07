/*turn off the assert*/
/* #define NDEBUG */
#include <iostream>
#include <cassert>
#include "add_two_numbers.h"

ListNode* create_linkedlist(std::initializer_list<int> lst) {
    auto iter = lst.begin();
    ListNode* head = lst.size() ? new ListNode(*iter++) : NULL;
    for (ListNode* cur = head; iter != lst.end(); cur = cur->next)
        cur->next = new ListNode(*iter++);
    return head;
}

int main() {
    Solution s;

    ListNode *l1 = create_linkedlist({9, 9, 9, 9});
    ListNode *l2 = create_linkedlist({9, 9});
    ListNode *l3 = create_linkedlist({8, 9, 0, 0, 1});

    ListNode *ret = s.addTwoNumber(l1, l2);
    for (ListNode *cur = ret; cur; cur = cur->next)
        std::cout << cur->val << "->";
    std::cout << "\b\b" << std::endl;

    /* assert( (&ret ==  &l3)); */


    return 0;
}
