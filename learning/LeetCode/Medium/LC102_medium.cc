#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::queue;

namespace LeetCode
{

//二叉树的层序遍历
class Solution_102 {
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;    
        vector<vector<int>> result;

        if (root) {
            que.push(root);
        }

        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; ++i) {
                TreeNode *node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
            }
            result.push_back(vec);
        }
        return result;
    }
};


}// end of namespace LeetCode

int main()
{
    return 0;
}

