#include <iostream>

using std::cout;
using std::endl;

class Solution {
    struct ListNode{
        int _val;
        struct ListNode *next;
    };

public:
    ListNode *reverse(ListNode *cur, ListNode *pre) {
        if (cur == NULL) {
            return pre;
        }
        ListNode *tmp = cur->next;
        cur->next = pre;
        reverse(tmp, cur);
    }

    ListNode* reverseList(ListNode* head) {
        return reverse(head, NULL);
    }
};

int main()
{
    return 0;
}

