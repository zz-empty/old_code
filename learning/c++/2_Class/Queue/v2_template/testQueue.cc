#include "queue.hpp"
#include <iostream>

using std::cout;
using std::endl;
using namespace wd;

void test0()
{

   Queue<int, 15> que;
   cout << "que.size = " << que.size() << endl;

   cout << endl;
   cout << "---------------test push---------------" << endl;
   for (int idx = 0; idx < 20; ++idx) {
       if (!que.full()) {
           que.push(idx + 2);
           cout << "que.rear = " << que.back() << endl;
       }
       else {
           cout << "the queue is full" << endl;
           break;
       }
   }


   cout << endl;
   cout << "---------------test pop---------------" << endl;
   for (int idx = 0; idx < 20; ++idx) {
       if (!que.empty()) {
           cout << "que.front = " << que.front() << endl;
           que.pop();
       }
       else {
           cout << "the queue is empty" << endl;
           break;
       }
   }
}

void test1()
{

   Queue<double, 15> que;
   cout << "que.size = " << que.size() << endl;

   cout << endl;
   cout << "---------------test push---------------" << endl;
   for (int idx = 0; idx < 20; ++idx) {
       if (!que.full()) {
           que.push(idx + 2.3);
           cout << "que.rear = " << que.back() << endl;
       }
       else {
           cout << "the queue is full" << endl;
           break;
       }
   }


   cout << endl;
   cout << "---------------test pop---------------" << endl;
   for (int idx = 0; idx < 20; ++idx) {
       if (!que.empty()) {
           cout << "que.front = " << que.front() << endl;
           que.pop();
       }
       else {
           cout << "the queue is empty" << endl;
           break;
       }
   }
}

int main()
{
    test1();
    return 0;
}

