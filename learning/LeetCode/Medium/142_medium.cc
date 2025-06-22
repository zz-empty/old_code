#include <iostream>

using std::cout;
using std::endl;

struct ListNode{
    int val;
    struct ListNode * next;
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;

            //有环，快慢指针相遇
            if (fast == slow) {
                ListNode *index1 = fast;
                ListNode *index2 = head;
                //找到环的入口
                while (index1 && index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2;
            }
        }

        return nullptr;
    }
};

int main()
{
    return 0;
}

