#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //用二维数组存储所有的三元组
        //找出一个数组中，a+b+c=0的三元组，a!=b!=c
        vector<vector<int>> result;
        //对nums排序
        std::sort(nums.begin(), nums.end());

        //i : a
        //left : b
        //right : c
        size_t len = nums.size();
        for (int i = 0, left, right; i < int(len); ++i) {
            //剪枝
            if (nums[i] > 0) {
                return result;      //a > 0, 则a + b + c一定大于0
            }

            //去重
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            left = i + 1;
            right = nums.size() - 1;

            //left向右，right向左，找出这个范围内的所有三元组
            while (right > left) {
                if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                }
                else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                }
                else {
                    //找到了 a + b + c = 0
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});

                    //去重
                    while (right > left && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    while (right > left && nums[left] == nums[left + 1]) {
                        left++;
                    }

                    //找下一个三元组
                    right--;
                    left++;
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

