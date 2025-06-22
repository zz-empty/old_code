#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> record;
        int counts = 0;
        for (auto &n1: nums1) {
            for (auto &n2: nums2) {
                record[n1 + n2]++;
            }
        }

        for (auto &n3: nums3) {
            for (auto &n4: nums4) {
                int target = 0 - n3 - n4;
                if (record.find(target) != record.end()) {
                    counts += record[target]; 
                }
            }
        }

        return counts;

    }
};

int main()
{
    return 0;
}

