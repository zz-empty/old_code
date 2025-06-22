#include <iostream>

using std::cout;
using std::endl;

struct ListNode{
    int val;
    struct ListNode *next;
};

class Solution {
public:
    //删除倒数第n个结点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //快指针走n+1步
        //然后快慢指针同时走，直到快指针为空，通过慢指针删除结点
        ListNode *dummy = new ListNode();
        dummy->next = head;
        ListNode *fast = dummy;
        ListNode *slow = dummy;
        n++;
        while (n-- && fast) {
            fast = fast->next;
        }

        //n大于链表长度时
        if (!n) {
            return head;
        }

        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }

        //删除倒数第n个结点
        ListNode *tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;

        head = dummy->next; //head有可能已被删除
        delete dummy;
        return head;
    }
};

int main()
{
    return 0;
}

