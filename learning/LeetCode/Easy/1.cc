#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //用unorded_map存放遍历过的(元素，下标)
        //遍历时，查找是否有符合要求的两个元素
        unordered_map<int, int> res;
        for (int i = 0; i < nums.size(); ++i) {
            auto p = res.find(target - nums[i]);
            if (p != res.end()) {
                //找到两个元素了
                return {p->second, i};
            }
            //没有在map中找到差值,将当前值加入map
            res.insert(std::pair<int, int>(nums[i], i));
        }
        return {};
    }
};

int main()
{
    return 0;
}

