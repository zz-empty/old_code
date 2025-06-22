#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;


class Solution {
public:
    //四数之和
    //用双指针法，时间复杂度减少一个数量级
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;     //存储所有满足条件的四元组
        std::sort(nums.begin(), nums.end());

        //寻找 a + b + c + d = target  且 a != b != c != d
        for (int k = 0, i, left, right; k < nums.size(); ++k) {
            //剪枝
            if (nums[k] > target && nums[k] >= 0) {
                break;
            }
            //去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }

            for (i = k + 1; i < nums.size(); ++i) {
                //剪枝
                if (nums[k] + nums[i] > target && (nums[k] + nums[i] >= 0)) {
                    break;
                }
                //去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }

                left = i + 1;
                right = nums.size() - 1;

                while (left < right) {
                    if ((long)nums[k] + nums[i] + nums[left] + nums[right] > target) {
                        right--;
                    }
                    else if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target) {
                        left++;
                    }
                    else {
                        //找到了符合要求的四元组，加入result
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        //去重
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        } 
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }

                        //寻找下一个四元组
                        right--;
                        left++;
                    }
                }
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}

