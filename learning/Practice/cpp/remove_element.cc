#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (val != nums[i]) {
                nums[k++] = nums[i];
            }
        }
        return k;
    }
};

int main()
{
    vector<int> nums = {2, 3, 1, 3, 5, 6};
    cout << "移除元素后剩余的个数：" << Solution().removeElement(nums, 3) << endl;
    return 0;
}
