#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maximunCount(vector<int>& nums) {
        int n = nums.size();
        int firstNonNegative = findFirstNonNegative(nums);
        int firstPositive = findFirstPostive(nums);
        int negCount = firstNonNegative;
        int posCount = n - firstPositive;
        return max(negCount, posCount);
    }
};

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

