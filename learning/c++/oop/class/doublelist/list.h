#ifndef __LIST_H__
#define __LIST_H__

typedef struct Node
{
    Node(int data = 0);
    ~Node();
    Node(const Node &rhs);
    Node &operator=(const Node &rhs);
    
    int _data;
    Node *_pPre;
    Node *_pNext;
}Node, *pNode_t;

#if 1
class List
{
public:
    List();
    ~List();

    bool empty() const;
    void display() const;
    int getsize() const;

    //insert node
    void push_front(int value);
    void push_back(int data);
    void insert(int pos, int data);

    //delete node
    void pop_front();
    void pop_back();
    void erase(int data);
    bool deleteNode(const int &pos); //按位删除

    //query node
    Node *find(int data); //按值查找
    Node *location(const int pos);

    //erase all node
    void destory();
private:
    Node *_pHead;
    Node *_pTail;
    int _size;
};
#endif

#endif
