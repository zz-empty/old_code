#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::pair;
using std::priority_queue;

class mycomparision{
public:
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        return lhs.second > rhs.second;
    }
};

class Solution {
public:
    
    //前K个高频元素
    //先用map存储key和value，再用小根堆存放前K个高频元素
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //用map统计元素出现的频率
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            m[nums[i]]++;
        }

        //用小根堆排序map, 维持k的规模
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparision> pq;
        for (auto it = m.begin(); it != m.end(); ++it) {
            pq.push(*it);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        //用vector记录前k个高频元素
        vector<int> result(k);
        for (int i = k - 1; i >= 0; --i) {
            result[i] = pq.top().first;
            pq.pop();
        }
        return result;
    }
};

int main()
{
    return 0;
}

