#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

class MyQueue {
    //用两个栈模拟队列
    stack<int> stIn;
    stack<int> stOut;
public:
    MyQueue() {

    }

    //入队
    void push(int x) {
        stIn.push(x);
    }

    //出队
    int pop() {
        //只有stOut为空时，才从stIn中导入数据
        if (stOut.empty()) {
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    //查看队头元素
    int peek() {
        int result = pop();
        stOut.push(result);
        return result;
    }

    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

int main()
{
    return 0;
}

