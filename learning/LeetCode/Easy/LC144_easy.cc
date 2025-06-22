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
    //前序遍历，迭代版，用栈模拟递归
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;  //遍历所有结点
        vector<int> result; //记录前序遍历的结果

        if (root == nullptr) {
            return result;
        }
        st.push(root);  //将结点入栈
        //只要栈不为空，就持续循环
        while (!st.empty()) {
            //出栈，加入结果集
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur->val);
            //先加入右节点，再加入左节点
            if (cur->right) {
                st.push(cur->right);
            }
            if (cur->left) {
                st.push(cur->left);
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}

