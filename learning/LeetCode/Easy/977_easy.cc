#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution
{
public:
    vector<int> sortedSquares(vector<int>& nums) {
        //返回每个数字平方组成的新数组，按递增顺序
        int k = nums.size() - 1;
        vector<int> result(nums.size(), 0);
        for (int left = 0, right = k; left <= right;) {
            if (nums[left] * nums[left] <= nums[right] * nums[right]) {
                result[k--] = nums[right] * nums[right];
                right--;
            }
            else {
                result[k--] = nums[left] * nums[left];
                left++;
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}

