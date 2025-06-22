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

        //根入栈
        if (root) {
            st.push(root);
        }
        while (!st.empty()) {
            TreeNode *node = st.top();  //拿出栈顶元素
            if (node) {
                st.pop();   //先弹出避免重复加入
                //添加 右中左结点
                if (node->right) {
                    st.push(node->right);
                }
                st.push(node);
                st.push(NULL);
                if (node->left) {
                    st.push(node->left);
                }
            } else {
                //当遇到空结点时，才将下一个结点放入结果集
                st.pop();
                result.push_back(st.top()->val);
                st.pop();
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}

