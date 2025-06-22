#include <iostream>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::vector;
using std::stack;



class Solution {
    //树结点
    struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
        TreeNode(int val) : val(val) {
            left = right = NULL;
        }
    };
public:
    //中序遍历，迭代版，用栈模拟递归
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;  //遍历所有结点
        vector<int> result; //记录中序遍历的结果
        TreeNode *cur = root;

        //只要栈不为空或者cur不为空，就持续循环
        while (cur != NULL || !st.empty()) {
            if (cur != NULL) {
                st.push(cur);
                cur = cur->left;    //去到最左边
            }
            else {
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
                cur = cur->right;
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}

