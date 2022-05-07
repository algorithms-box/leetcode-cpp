struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next): val(x), next(next) {}
};


class Solution {
  public:
    ListNode* addTwoNumber(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* current = head;
        int n1 = 0;
        int n2 = 0;
        int carry = 0;

        /* DO NOT forget add carry != 0, the last carry */
        while (l1 || l2 || carry) {
            if (l1) {
                n1 = l1->val;
                l1 = l1->next;
            } else {
                n1 = 0;
            }

            if (l2) {
                n2 = l2->val;
                l2 = l2->next;
            } else {
                n2 = 0;
            }

            current->next = new ListNode((n1 + n2 + carry) % 10);
            current = current->next;
            carry = (n1 + n2 + carry) / 10;

        }

        return head->next;
    }
};
