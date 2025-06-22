#include <iostream>

using std::cout;
using std::endl;

struct ListNode {
    int val;
    struct ListNode *next;
};

class Solution {
public:
    //两两交换
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummy = new ListNode();
        dummy->next = head;
        ListNode *cur = dummy;

        while (cur->next && cur->next->next) {
            ListNode *tmp1 = cur->next;     //sava 1
            ListNode *tmp3 = cur->next->next->next; //save 3

            cur->next = tmp1->next; //0 ---> 2
            cur->next->next = tmp1; //2 ---> 1
            tmp1->next = tmp3;      //1 ---> 3

            cur = cur->next->next;
        }
        return dummy->next;
    }
};

int main()
{
    return 0;
}

