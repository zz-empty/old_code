#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        //找到长度最小的子数组
        int sum = 0;
        int result = INT32_MAX; //最终的长度
        for (int j = 0, i = 0; j < nums.size(); ++j) {
            sum += nums[j];
            while (sum >= target) {
                int subL = j - i + 1; //满足子数组的和大于target时，子数组的长度
                result = result > subL ? subL : result; //判断最小长度是否变化
                //移动起始位置, 缩小窗口，再去判断
                sum -= nums[i++];
            }
        }
        return result == INT32_MAX ? 0 : result;  //返回满足要求的子数组的最小长度
    }
};

int main()
{
    return 0;
}

