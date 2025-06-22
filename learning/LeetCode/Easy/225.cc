#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;

class MyStack {
    queue<int> que;
public:

    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        //将n-1个元素出队，在入队，弹出最后一个元素
        if (!que.empty()) {
            int len = que.size() - 1;
            while (len--) {
                que.push(que.front());
                que.pop();
            }
            int result = que.front();
            que.pop();
            return result;
        }
        return -1;
    }

    int top() {
        return que.back();
    }

    bool empty() {
        return que.empty();
    }
};

int main()
{
    return 0;
}

