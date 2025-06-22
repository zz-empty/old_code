#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution
{
public:
    int removeElement(vector<int>& nums, int val)
    {
        //快指针遍历原数组，慢指针更新新数组
        int slow = 0;
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != val) {
                if (fast == slow) {
                    slow++;     //如果快慢指针相同，且不是目标，向后
                    continue;
                }
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};

int main()
{
    return 0;
}

