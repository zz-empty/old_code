#include <iostream>
#include <vector>
#include <unordered_set>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;

class Solution {
public:
    //两个数组的交集, 数据长度不大于1000，数据大小也不大于1000
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int hashtable[1002] = {0};
        unordered_set<int> result;

        //设置哈希表
        for (size_t i = 0; i < nums1.size(); ++i) {
            hashtable[nums1[i]] = 1;
        }

        //找交集
        for (size_t i = 0; i < nums2.size(); ++i) {
            if (hashtable[nums2[i]]) {
                result.insert(nums2[i]);
            }
        }

        return vector<int>(result.begin(), result.end());
    }

    vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        unordered_set<int> result;

        for (auto ptr: nums2) {
            if (nums_set.find(ptr) != nums_set.end()) {
                result.insert(ptr);
            }
        }

        return vector<int>(result.begin(), result.end());
    }
};

int main()
{
    return 0;
}

