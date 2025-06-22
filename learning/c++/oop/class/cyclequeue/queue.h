#ifndef __QUEUE_H__
#define __QUEUE_H__

class Queue
{
public:
    Queue(int sz = 10);
    ~Queue();

    bool empty() const;
    bool full() const;
    void enQueue(const int &value);
    void deQueue();
    int getFront() const;//得到队头指针
    int getRear() const;//得到队尾指针
    int front() const;//得到队头元素
    int rear() const;//得到队尾元素

    void print();
private:
    int _size;
    int _front;//队头下标
    int _rear;//队尾下标
    int *_data;
};

#endif
