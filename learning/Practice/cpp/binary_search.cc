#include <iostream>
#include <vector>

using namespace std;
using std::cout;
using std::vector;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    // 已知nums是有序的
    // 使用左闭右开区间

    int left = 0;
    int right = nums.size();
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (target < nums[mid]) {
        // 去左区间，修改右边界
        right = mid;
      } else if (target > nums[mid]) {
        // 去右区间，修改左边界
        left = mid + 1;
      } else {
        // 中间值就是目标值，返回下标
        return mid;
      }
    }
    return -1; // 没找到的情况
  }
};

int main() {
  vector<int> a = {2, 3, 5, 9, 12, 15, 18};
  int target = 9;
  cout << "the pos is " << Solution().search(a, target) << endl;
  return 0;
}
