#include "queue.h"
#include <iostream>

using std::cout;
using std::endl;

void test();

int main()
{
    test();
    return 0;
}

void test()
{
    Queue queue;
    cout << "front elem = " << queue.front() << endl;
    cout << "rear elem = " << queue.rear() << endl;

    cout << endl;
    cout << "------insert queue-----" << endl;
    int idx = 0;
    for (idx = 2; idx <= 50; idx += 5) {
        queue.enQueue(idx);
    }
    queue.print();

    cout << endl;
    cout << "-------deQueue--------" << endl;
    while (!queue.empty()) {
        queue.deQueue();
        queue.print();
    }
}
