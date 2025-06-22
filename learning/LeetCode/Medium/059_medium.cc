#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int start_x = 0, start_y = 0;   //每次循环开始的坐标
        int offset = 1;     //每次循环的偏移量
        int counts = 1;     //计数
        int loop = n / 2;
        vector<vector<int>> nums(n, vector<int>(n, 0));

        //循环n/2次，使用左闭右开处理每个边界
        int i = 0, j = 0;
        while (loop--) {
            i = start_x;
            j = start_y;
            //北边
            for (; j < n - offset; ++j) {
                nums[i][j] = counts++;
            }
            //东边
            for (; i < n - offset; ++i) {
                nums[i][j] = counts++;
            }
            //南边
            for (; j > start_y; --j) {
                nums[i][j] = counts++;
            }
            //西边
            for (; i > start_x; --i) {
                nums[i][j] = counts++;
            }
            start_x++;
            start_y++;
            offset++;
        }

        //如果n是奇数，设置最后一个元素
        if (n % 2 == 1) {
            nums[n / 2][n / 2] = counts;
        }
        return nums;
    }
};

int main()
{

    std::vector<std::vector<int>> matrix = Solution().generateMatrix(3);

    // 遍历二维vector
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

