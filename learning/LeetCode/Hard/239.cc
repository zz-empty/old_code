#include <iostream>
#include <vector>
#include <deque>

using std::cout;
using std::endl;
using std::vector;
using std::deque;

class Solution {
private:
    //单调队列：递减
    class MyQueue {
    public:
        deque<int> que;

        void pop(int val) {
            if (!que.empty() && val == que.front()) {
                que.pop_front();
            }
        }

        void push(int val) {
            while (!que.empty() && val > que.back()) {
                que.pop_back();
            }
            que.push_back(val);
        }

        int front() {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        MyQueue que;
        //将前k个元素，加入单调队列
        for (int i = 0; i < k; ++i) {
            que.push(nums[i]);
        }
        //将前k个元素的最大值加入result
        result.push_back(que.front());

        //滑动，直到nums的末尾
        for (int i = k; i < nums.size(); ++i) {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }

        return result;
    }
};

int main()
{
    return 0;
}

